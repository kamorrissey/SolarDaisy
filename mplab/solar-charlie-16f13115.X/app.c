// #define BATTERY_CHECK

#include <stdbool.h>
#include "mcc_generated_files/system/system.h"

#include "app.h"
#include "battery.h"
#include "fsm.h"
#include "jsf8.h"
#include "ledcc.h"
#include "led6_app.h"
#include "solar.h"

static FSM_t FSM;

static void State_Init_Enter(void);
static void State_Init_Handle(void);
static const State_t State_Init = {
    .on_entry = State_Init_Enter, 
    .handler = State_Init_Handle,
    .on_exit = NULL,
};

static void State_Charging_Enter(void);
static void State_Charging_Handle(void);
static void State_Charging_Exit(void);
static const State_t State_Charging = {
    .on_entry = State_Charging_Enter,
    .handler = State_Charging_Handle,
    .on_exit = State_Charging_Exit,
};

static void State_Active_Enter(void);
static void State_Active_Handle(void);
static void State_Active_Exit(void);
static const State_t State_Active = {
    .on_entry = State_Active_Enter,
    .handler = State_Active_Handle,
    .on_exit = State_Active_Exit,
};

static void Timer1_ISR(void)
{
    // needed to avoid uncalled function
    led6_timer_interrupt_handler();
}

static void Blink(int32_t duration)
{
    LedCC_SetDisplayState(1);
    for(int32_t i = 0; i < duration; ++i);
    LedCC_SetDisplayState(0);
    for(int32_t i = 0; i < duration; ++i);
}

static void BlinkLighting(void)
{
    Blink((CMP1_GetOutputStatus() ? 10000L : 100000L));
}

static bool App_ShouldSleep(void)
{
    // return (Battery_IsBelowLowerThreshold() || !Solar_IsDark());
    return (!Solar_IsDark());
}

static bool App_ShouldRun(void)
{
    // return (Battery_IsAboveUpperThreshold() && Solar_IsDark());
    return (Solar_IsDark());
}

static void State_Init_Enter(void)
{
    while (!FVR_IsOutputReady())
    {
        // Spin until FVR stable
    }
    // DAC1_SetOutput(SOL_THRESHOLD);
    LedCC_Initialize();
    CM1CON1 = 0x03;         // interrupt CMP1OUT leading & trailing
    PIR5bits.CM1IF = 0;     // discard edge from power-up settling
    PIE5bits.CM1IE = 1;     // enable CMP1 rising/falling-edge interrupt    Timer1_OverflowCallbackRegister(led6_timer_interrupt_handler);
    Timer1_OverflowCallbackRegister(Timer1_ISR);
#ifdef BATTERY_CHECK
    Timer0_OverflowCallbackRegister(Battery_ISR);
#endif
    jsf8_seed(1);
}

static void State_Init_Handle(void)
{
#ifdef BATTERY_CHECK
    Battery_FetchReading();
#endif
    FSM_Set_Next_State(
        &FSM,
        (App_ShouldSleep() ? &State_Charging : &State_Active)
    );
}

static void Diag_Report(void)
{
    // Group 1: comparator. 3 fast = dark, 1 slow = light
    if (Solar_IsDark()) { Blink(10000L); Blink(10000L); Blink(10000L); }
    else                { Blink(100000L); }

    for (int32_t i = 0; i < 300000L; ++i);          // gap

    // Group 2: battery, one blink per 50 counts (600 ? 12 blinks)
    int16_t mvolts = Battery_FetchReading();
    for ( ; mvolts > 0; mvolts -= 50) Blink(100000L);
}

static void State_Charging_Enter(void)
{
#ifdef BATTERY_CHECK
    Timer0_Start();
#endif
}

static void State_Charging_Handle(void)
{
    // Diag_Report();
    if ( App_ShouldRun())
    {
        FSM_Set_Next_State(&FSM, &State_Active);
        return;
    }
    SLEEP();
    NOP();
}

static void State_Charging_Exit(void)
{
#ifdef BATTERY_CHECK
    Timer0_Stop();
#endif
}

static void State_Active_Enter(void)
{
    LedCC_SetDisplayState(1);
    led6_init();
#ifdef BATTERY_CHECK
    Battery_Initialize();
#endif
    Timer2_PeriodSet(0x3F);
    Timer2_Start();
    Timer1_Start();
#ifdef BATTERY_CHECK
    Timer0_Start();
#endif
}

static void State_Active_Handle(void)
{
    if (App_ShouldSleep())
    {
        FSM_Set_Next_State(&FSM, &State_Charging);
        return;
    }
    led6_animate();
}

static void State_Active_Exit(void)
{
    LedCC_SetDisplayState(0);
    Timer2_Stop();
    Timer1_Stop();
#ifdef BATTERY_CHECK
    Timer0_Stop();
#endif
    led6_off();
}


void APP_Initialize(void)
{
    FSM_Initialize(&FSM, &State_Init);
}

void APP_Run(void)
{
#ifdef BATTERY_CHECK
    Battery_Task();
#endif
    FSM_Dispatch(&FSM);
}
