

#include "mcc_generated_files/system/system.h"
#include "fader.h"
#include "cplex.h"
#include "jsf8.h"
#include "led6_app.h"
#include "ledcc.h"

#define NUM_LEVELS (64)

typedef uint8_t ledLevel_t;
typedef uint8_t ledBits_t;

enum brightness
{
    LED_OFF = 0,
    LED_DIM = 7,
    LED_LOW = 15,
    LED_MED = 31,
    LED_MED_HIGH = 47,
    LED_HIGH = 55,
    LED_ON = 63,
};

static const uint8_t g_DutyFromLevel[NUM_LEVELS] = {
    0, 0, 0, 1, 1, 2, 2, 3,
    4, 5, 6, 8, 9, 11, 13, 14,
    16, 19, 21, 23, 26, 28, 31, 34,
    37, 40, 43, 47, 50, 54, 58, 62,
    66, 70, 74, 79, 83, 88, 93, 98,
    103, 108, 113, 119, 124, 130, 136, 142,
    148, 154, 161, 167, 174, 180, 187, 194,
    201, 209, 216, 224, 231, 239, 247, 255
};

typedef enum
{
    INIT,
    WAIT,
    QUIT,
    CH_CW_NEXT,
    CH_CW_FINISH,
    CH_CCW_NEXT,
    CH_CCW_FINISH,
    PULSE_FADE_IN,
    PULSE_HOLD,
    PULSE_FADE_OUT,
    PULSE_LOOP,
    BEAT_START,
    BEAT_ON,
    BEAT_OFF,
    BEAT_LOOP1,
    BEAT_LOOP2,
    GRAY_LOOP,
    GRAY_END,
    ELEV_LOOP1,
    ELEV_LOOP2,
    WCH_LOOP1,
    WCH_LOOP2,
    TWINKLE_LOOP1,
    STAGGER_LOOP1,
} State;

typedef bool (*Task_t)(void);

typedef struct
{
    int8_t state;
    int8_t nextState;
    int16_t ticks_remaining;
    const Task_t *task;
    int8_t ledCursor;
    Fader fader[NUM_LEDS];
    union
    {
        struct
        {
            int8_t led;
            int8_t remaining_loops;
        } chase;
        struct
        {
            int8_t remaining_loops;
        } pulse;
        struct
        {
            int8_t remaining_beats;
            int8_t remaining_loops;
        } beat;
        struct
        {
            int8_t index;
        } gray;
        struct
        {
            int8_t remaining_loops;
            int8_t step_index;
        } elevator;
        struct
        {
            int8_t remaining_loops;
            int8_t step_index;
        } waitChase;
        struct
        {
            int16_t remaining_loops;
        } twinkle;
        struct
        {
            int16_t remaining_loops;
            int8_t index;
        } stagger;
    } sdata;
} AppFramework;

static AppFramework App;

static void DelayTask(void)
{
    if (App.ticks_remaining <= 0)
    {
        LedCC_SetWaitState(0);
        App.state = App.nextState;
    }
    else
    {
        LedCC_SetWaitState(1);
        // TODO: SLEEP right here
    }
}

inline static void DelayInit(int8_t nextState, int16_t ticks)
{
    App.state = WAIT;
    App.nextState = nextState;
    App.ticks_remaining = ticks;
}

static inline ledLevel_t bool2bright(bool isOn)
{
    return (isOn ? LED_HIGH : LED_OFF);
}

static void led6_SetTarget(int8_t led, int16_t steps, ledLevel_t value)
{
    di();
    Fader_SetTarget(&App.fader[led], value, steps);
    ei();
}

static void led6_SetTargetBits(ledBits_t bits, int16_t steps, ledLevel_t high, ledLevel_t low)
{
    ledBits_t mask = 0b100000;
    for (int8_t i = LED1; i < NUM_LEDS; ++i)
    {
        Fader_SetTarget(&App.fader[i], ( ((bits & mask) != 0) ? high : low ), steps );
        mask >>= 1;
    }
}

static void led6_SetValue(int8_t led, ledLevel_t value)
{
    di();
    Fader_SetValue(&App.fader[led], value);
    ei();
}

static void led6_SetBits(ledBits_t bits, ledLevel_t high, ledLevel_t low)
{
    ledBits_t mask = 0b100000;
    for (int8_t i = LED1; i < NUM_LEDS; ++i)
    {
        led6_SetValue(i, ( ((bits & mask) != 0) ? high : low ) );
        mask >>= 1;
    }
}


static bool ChaseCwTask(void)
{
    static const int8_t NUM_LOOPS = 12;
    static const int16_t FADE_TIME = 100;
    static const int16_t WAIT_TIME = 101;
    switch (App.state)
    {
    default:
        break;
    case INIT:
        App.sdata.chase.led = LED1;
        App.sdata.chase.remaining_loops = NUM_LOOPS;
        led6_SetTarget(App.sdata.chase.led, FADE_TIME, LED_MED_HIGH);
        DelayInit(CH_CW_NEXT, WAIT_TIME);
        break;
    case QUIT:
        return true;
    case WAIT:
        DelayTask();
        break;
    case CH_CW_NEXT:
        if (App.sdata.chase.remaining_loops <= 0)
        {
            App.state = CH_CW_FINISH;
            break;
        }
        --App.sdata.chase.remaining_loops;
        led6_SetTarget(App.sdata.chase.led, FADE_TIME, LED_OFF);
        int8_t led_b = App.sdata.chase.led;
        ++led_b;
        if (led_b > LED6)
        {
            led_b = LED1;
        }
        App.sdata.chase.led = led_b;
        led6_SetTarget(led_b, FADE_TIME, LED_HIGH);
        DelayInit(CH_CW_NEXT, WAIT_TIME);
        break;
    case CH_CW_FINISH:
        led6_SetTarget(App.sdata.chase.led, FADE_TIME, LED_OFF);
        DelayInit(QUIT, WAIT_TIME);
        break;
    }
    return false;
}

static bool ChaseCcwTask(void)
{
    static const int8_t NUM_LOOPS = 12;
    static const int16_t FADE_TIME = 100;
    static const int16_t WAIT_TIME = 101;
    switch (App.state)
    {
    default:
        break;
    case INIT:
        App.sdata.chase.led = LED1;
        App.sdata.chase.remaining_loops = NUM_LOOPS;
        led6_SetTarget(App.sdata.chase.led, FADE_TIME, LED_HIGH);
        DelayInit(CH_CCW_NEXT, WAIT_TIME);
        break;
    case QUIT:
        return true;
    case WAIT:
        DelayTask();
        break;
    case CH_CCW_NEXT:
        if (App.sdata.chase.remaining_loops <= 0)
        {
            App.state = CH_CCW_FINISH;
            break;
        }
        --App.sdata.chase.remaining_loops;
        led6_SetTarget(App.sdata.chase.led, FADE_TIME, LED_OFF);
        int8_t led_b = App.sdata.chase.led;
        --led_b;
        if (led_b < LED1)
        {
            led_b = LED6;
        }
        App.sdata.chase.led = led_b;
        led6_SetTarget(led_b, 100, LED_HIGH);
        DelayInit(CH_CCW_NEXT, WAIT_TIME);
        break;
    case CH_CCW_FINISH:
        led6_SetTarget(App.sdata.chase.led, FADE_TIME, LED_OFF);
        DelayInit(QUIT, WAIT_TIME);
        break;
    }
    return false;
}

static bool PulseTask(void)
{
    static const int8_t NUM_LOOPS = 6;
    static const int16_t FADE_TIME = 800;
    static const int16_t WAIT_IN_TIME = 1000;
    static const int16_t WAIT_OUT_TIME = 500;
    switch (App.state)
    {
    default:
        break;
    case INIT:
        App.state = PULSE_FADE_IN;
        App.sdata.pulse.remaining_loops = NUM_LOOPS;
        break;
    case QUIT:
        return true;
    case WAIT:
        DelayTask();
        break;
    case PULSE_FADE_IN:
        led6_SetTargetBits(0b111111, 100, LED_MED_HIGH, LED_OFF);
        DelayInit(PULSE_FADE_OUT, 200);
        break;
    case PULSE_FADE_OUT:
        led6_SetTargetBits(0b000000, 100, LED_MED_HIGH, LED_OFF);
        DelayInit(PULSE_LOOP, 150);
        break;
    case PULSE_LOOP:
        if (App.sdata.pulse.remaining_loops > 0)
        {
            --App.sdata.pulse.remaining_loops;
            App.state = PULSE_FADE_IN;
        }
        else
        {
            App.state = QUIT;
        }
        break;
    }
    return false;
}

static bool BeatTask(void)
{
    static const int8_t NUM_LOOPS = 12;
    static const int8_t NUM_BEATS = 2;
    switch (App.state)
    {
    default:
        break;
    case INIT:
        App.sdata.beat.remaining_loops = NUM_LOOPS;
        App.state = BEAT_START;
        break;
    case WAIT:
        DelayTask();
        break;
    case QUIT:
        return true;
    case BEAT_START:
        App.sdata.beat.remaining_beats = NUM_BEATS;
        App.state = BEAT_LOOP1;
        break;
    case BEAT_ON:
        led6_SetBits(0b111111, LED_MED_HIGH, LED_LOW);
        DelayInit(BEAT_OFF, 25);
        break;
    case BEAT_OFF:
        led6_SetBits(0b000000, LED_MED_HIGH, LED_LOW);
        DelayInit(BEAT_LOOP1, 25);
        break;
    case BEAT_LOOP1:
        if (App.sdata.beat.remaining_beats > 0)
        {
            --App.sdata.beat.remaining_beats;
            App.state = BEAT_ON;
        }
        else
        {
            App.state = BEAT_LOOP2;
        }
        break;
    case BEAT_LOOP2:
        if (App.sdata.beat.remaining_loops > 0)
        {
            --App.sdata.beat.remaining_loops;
            DelayInit(BEAT_START, 200);
        }
        else
        {
            led6_SetBits(0b000000, LED_MED_HIGH, LED_DIM);
            DelayInit(QUIT, 200);
        }
        break;
    }
    return false;
}

static bool GrayTask(void)
{
    static const int8_t NUM_VALUES = 64;
    static const int16_t FADE_TICKS = 13;
    static const int16_t WAIT_TICKS = 14;
    switch (App.state)
    {
    default:
        break;
    case INIT:
        App.sdata.gray.index = 0;
        App.state = GRAY_LOOP;
        break;
    case WAIT:
        DelayTask();
        break;
    case QUIT:
        return true;
    case GRAY_LOOP:
        if (App.sdata.gray.index < NUM_VALUES)
        {
            uint8_t i = (uint8_t)App.sdata.gray.index;
            uint8_t gray = i ^ (i >> 1);
            led6_SetTargetBits(gray, FADE_TICKS, LED_HIGH, LED_LOW);
            DelayInit(GRAY_LOOP, WAIT_TICKS);
            ++App.sdata.gray.index;
        }
        else
        {
            App.state = GRAY_END;
        }
        break;
    case GRAY_END:
        led6_SetTargetBits(0b000000, FADE_TICKS, LED_MED_HIGH, LED_OFF);
        DelayInit(QUIT, WAIT_TICKS);
        break;
    }
    return false;
}

static bool ElevatorTask(void)
{
    static const int8_t NUM_LOOPS = 10;
    static const int16_t FADE_TICKS = 100;
    static const int16_t WAIT_TICKS = 150;
    static const uint8_t steps[] =
    {
        0b000100, 0b001110, 0b011111, 0b111111,
        0b111011, 0b110001, 0b100000, 0b000000,
    };
    switch (App.state)
    {
    default:
        break;
    case INIT:
        App.sdata.elevator.remaining_loops = NUM_LOOPS;
        App.state = ELEV_LOOP1;
        break;
    case WAIT:
        DelayTask();
        break;
    case QUIT:
        return true;
    case ELEV_LOOP1:
        if (App.sdata.elevator.remaining_loops > 0)
        {
            --App.sdata.elevator.remaining_loops;
            App.sdata.elevator.step_index = 0;
            App.state = ELEV_LOOP2;
        }
        else
        {
            App.state = QUIT;
        }
        break;
    case ELEV_LOOP2:
        if (App.sdata.elevator.step_index < ( sizeof (steps)/sizeof (steps[0])))
        {
            led6_SetTargetBits(steps[App.sdata.elevator.step_index++], FADE_TICKS, LED_MED_HIGH, LED_OFF);
            DelayInit(ELEV_LOOP2, WAIT_TICKS);
        }
        else
        {
            App.state = ELEV_LOOP1;
        }
        break;
    }
    return false;
}

static bool WaitChaseTask(void)
{
    static const int8_t NUM_LOOPS = 10;
    static const int16_t STEP_TICKS = 25;
    static const int16_t WAIT_TICKS = 100;
    static const uint8_t steps[] =
    {
        0b000100, 0b000110, 0b000111,
        0b100111, 0b110111, 0b111111,
        0b111111, 0b111111, 0b111111,
        0b111101, 0b111100, 0b011100,
        0b001100, 0b000100, 0b000000,
    };
    switch (App.state)
    {
    case INIT:
        App.sdata.waitChase.remaining_loops = NUM_LOOPS;
        App.state = WCH_LOOP1;
        break;
    case QUIT:
        return true;
    case WAIT:
        DelayTask();
        break;
    case WCH_LOOP1:
        if (App.sdata.waitChase.remaining_loops > 0)
        {
            --App.sdata.waitChase.remaining_loops;
            App.sdata.waitChase.step_index = 0;
            App.state = WCH_LOOP2;
        }
        else
        {
            DelayInit(QUIT, WAIT_TICKS);
        }
        break;
    case WCH_LOOP2:
        if (App.sdata.waitChase.step_index < ( sizeof (steps)/sizeof (steps[0])))
        {
            led6_SetBits(steps[App.sdata.waitChase.step_index++], LED_MED_HIGH, LED_OFF);
            DelayInit(WCH_LOOP2, STEP_TICKS);
        }
        else
        {
            DelayInit(WCH_LOOP1, WAIT_TICKS);
        }
        break;
    }
    return false;
}

static bool TwinkleTask(void)
{
    const uint8_t THRESHOLD = 245;
    const int16_t LONG_WAIT_TICKS = 50;
    const int16_t SHORT_WAIT_TICKS = 10;
    const int16_t NUM_LOOPS = 1000;
    switch (App.state)
    {
    case INIT:
        App.state = TWINKLE_LOOP1;
        App.sdata.twinkle.remaining_loops = NUM_LOOPS;
        led6_SetBits(0b111111, LED_LOW, LED_OFF);
        break;
    case QUIT:
        return true;
    case WAIT:
        DelayTask();
        break;
    case TWINKLE_LOOP1:
        if (App.sdata.twinkle.remaining_loops <= 0)
        {
            led6_SetBits(0b000000, LED_ON, LED_OFF);
            App.state = QUIT;
            break;
        }
        --App.sdata.twinkle.remaining_loops;
        for (int8_t i = 0; i < NUM_LEDS; ++i)
        {
            if (jsf8() >= THRESHOLD)
            {
                led6_SetValue(i, LED_ON);
                led6_SetTarget(i, LONG_WAIT_TICKS, LED_LOW);
            }
        }
        DelayInit(TWINKLE_LOOP1, SHORT_WAIT_TICKS);
        break;
    }
    return false;
}

static bool StaggerTask(void)
{
    const uint8_t THRESHOLD_L = 63;
    const uint8_t THRESHOLD_R = 127;
    const int16_t FADE_TICKS = 100;
    const int16_t NUM_LOOPS = 100;
    switch (App.state)
    {
    case INIT:
        App.state = STAGGER_LOOP1;
        App.sdata.stagger.remaining_loops = NUM_LOOPS;
        App.sdata.stagger.index = 0;
        led6_SetBits(0b000000, LED_ON, LED_OFF);
        break;
    case QUIT:
        return true;
    case WAIT:
        DelayTask();
        break;
    case STAGGER_LOOP1:
        if (App.sdata.stagger.remaining_loops <= 0)
        {
            led6_SetBits(0b000000, LED_ON, LED_OFF);
            App.state = QUIT;
            break;
        }
        --App.sdata.stagger.remaining_loops;
        uint8_t rand = jsf8();
        int8_t target_led = App.sdata.stagger.index + NUM_LEDS/2;
        if (rand <= THRESHOLD_L)
        {
            --target_led;
        }
        else if (rand <= THRESHOLD_R)
        {
            ++target_led;
        }
        else
        {
            ;
        }
        if (target_led >= NUM_LEDS)
        {
            target_led -= NUM_LEDS;
        }
        led6_SetTarget(target_led, FADE_TICKS, LED_ON);
        led6_SetTarget(App.sdata.stagger.index, FADE_TICKS, LED_OFF);
        App.sdata.stagger.index = target_led;
        DelayInit(STAGGER_LOOP1, FADE_TICKS);
        break;
    }
    return false;
}

#if 1
static const Task_t TASKS[] =
    {
        GrayTask,
        ChaseCwTask,
        ChaseCcwTask,
        GrayTask,
        PulseTask,
        BeatTask,
        GrayTask,
        ElevatorTask,
        GrayTask,
        WaitChaseTask,
        GrayTask,
        TwinkleTask,
        GrayTask,
        StaggerTask,
        NULL,
    };
#else
static const Task_t TASKS[] = { TwinkleTask, GrayTask, NULL };
#endif

static uint16_t bright2duty(ledLevel_t bright)
{
    if ( bright >= NUM_LEVELS )
    {
        bright = NUM_LEVELS - 1;
    }
    return g_DutyFromLevel[bright];
}

static void led6_shift_right(ledLevel_t state)
{
    di();
    for (int i = LED6; i > LED1; --i)
    {
        App.fader[i] = App.fader[i-1];
    }
    Fader_SetValue(&App.fader[LED1], state);
    ei();
}

static void led6_shift_left(ledLevel_t state)
{
    di();
    for (int8_t i = LED1; i < LED6; ++i)
    {
        App.fader[i] = App.fader[i+1];
    }
    Fader_SetValue(&App.fader[LED6], state);
    ei();
}

static void led6_rotate_right(void)
{
    di();
    Fader end;
    end = App.fader[LED6];
    
    for (int8_t i = LED6; i > LED1; --i)
    {
        App.fader[i] = App.fader[i-1];
    }
    App.fader[LED1] = end;
    ei();
}

static void led6_rotate_left(void)
{
    di();
    Fader end;
    end = App.fader[LED1];
    for (int8_t i = LED1; i < LED6; ++i)
    {
        App.fader[i] = App.fader[i+1];
    }
    App.fader[LED6] = end;
    ei();
}

void led6_init()
{
    for (int8_t i = LED1; i <= LED6; ++i)
    {
        led6_SetValue(i, LED_OFF);
    }
    App.state = INIT;
    App.task = &TASKS[0];
    App.ledCursor = NUM_LEDS;
}

void led6_off(void)
{
    di();
    CP_reset();
    ei();
}

void led6_animate(void)
{
    if (*App.task == NULL)
    {
        App.task = &TASKS[0];
        App.state = INIT;
    }
    if ((*App.task)())
    {
        ++App.task;
        App.state = INIT;
    }
}


void led6_timer_interrupt_handler(void)
{
    // Set LEDCC high while in ISR, for testing
    LedCC_SetIsrState(1);
    if (App.ledCursor > LED6)
    {
        App.ledCursor = LED1;
        if (App.ticks_remaining > 0)
        {
            --App.ticks_remaining;
        }
    }
    
    ledLevel_t level = (ledLevel_t)Fader_GetValue(&App.fader[App.ledCursor]);
    CP_setLed(App.ledCursor, bright2duty(level));
    Fader_Step(&App.fader[App.ledCursor]);
    
    ++App.ledCursor;
    LedCC_SetIsrState(0);
}
