
#include "mcc_generated_files/system/system.h"
#include "cplex.h"

// #define DISABLE_PWM // uncomment this line for debugging

static bool duty2bool(uint16_t duty)
{
    return (duty < 127);
}

static void CP1_toOutput(void)
{
    CP1_SetHigh();
    CP1_SetDigitalOutput();

#ifndef DISABLE_PWM
    RA5PPS = PWM1OUTPPS;
#endif
}

static void CP2_toOutput(void)
{
    CP2_SetHigh();
    CP2_SetDigitalOutput();

#ifndef DISABLE_PWM
    RA4PPS = PWM1OUTPPS;
#endif
}

static void CP3_toOutput(void)
{
    CP3_SetHigh();
    CP3_SetDigitalOutput();

#ifndef DISABLE_PWM
    RA2PPS = PWM1OUTPPS;
#endif
}

void CP_reset(void)
{
    CP1_SetDigitalInput();
    CP2_SetDigitalInput();
    CP3_SetDigitalInput();
    RA5PPS = 0;
    RA4PPS = 0;
    RA2PPS = 0;
}


void CP_setLed(int8_t led_num, uint16_t duty)
{    
    CP_reset();
    PWM1_LoadDutyValue(duty);
        
    switch (led_num) {
    default:
        break;
    case LED1:
        CP2_SetLow();
        CP2_SetDigitalOutput();
        CP1_toOutput();
        break;
    case LED2:
        CP1_SetLow();
        CP1_SetDigitalOutput();
        CP2_toOutput();
        break;
    case LED3:
        CP3_SetLow();
        CP3_SetDigitalOutput();
        CP2_toOutput();
        break;
    case LED4:
        CP2_SetLow();
        CP2_SetDigitalOutput();
        CP3_toOutput();
        break;
    case LED5:
        CP3_SetLow();
        CP3_SetDigitalOutput();
        CP1_toOutput();
        break;
    case LED6:
        CP1_SetLow();
        CP1_SetDigitalOutput();
        CP3_toOutput();
        break;
    }
}
