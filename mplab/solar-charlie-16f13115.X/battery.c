#include <stdbool.h>
#include <stdint.h>
#include "mcc_generated_files/system/system.h"

#include "battery.h"

#define BATT_UTH 625
#define BATT_LTH 500

static volatile bool Battery_timer_flag = false;
static volatile int16_t Battery_voltage = 0;

void Battery_Initialize(void)
{
    Battery_timer_flag = false;
    Battery_voltage = 0;
}

void Battery_ISR(void)
{
    Battery_timer_flag = true;
}

void Battery_Task(void)
{
    di();
    if ( Battery_timer_flag )
    {
        Battery_timer_flag = false;
        ei();
        Battery_FetchReading();
    }
    else
    {
        ei();
    }
}

int16_t Battery_FetchReading(void)
{
    // Turn port around to analog input
    TRISAbits.TRISA0 = INPUT; 
    ANSELAbits.ANSA0 = ANALOG;
    
    // Wake ADC and take reading
    ADC_ChannelSelect(0x00); // ANA0 first
    ADC_Enable();
    __delay_ms(5);
    Battery_voltage = ADC_ChannelSelectAndConvert(0x0);
    ADC_Disable();
    
    // Resume digital output
    ANSELAbits.ANSA0 = DIGITAL;
    TRISAbits.TRISA0 = OUTPUT;
    
    return Battery_voltage;
}

bool Battery_IsAboveUpperThreshold(void)
{
    return (Battery_voltage > BATT_UTH);
}

bool Battery_IsBelowLowerThreshold(void)
{
    return (Battery_voltage < BATT_LTH);
}
