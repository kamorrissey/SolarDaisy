#include <stdint.h>
#include "mcc_generated_files/system/system.h"
#include "ledcc.h"

struct
{
    uint8_t display_state:1;
    uint8_t isr_state:1;
    uint8_t wait_state:1;
    uint8_t shutdown_state:1;
    uint8_t :4; // reserved
    ledcc_usage_t mode;
} LedCC_conf;

void LedCC_Initialize(void)
{
    LedCC_conf.display_state = 0;
    LedCC_conf.wait_state = 0;
    LedCC_conf.isr_state = 0;
    LedCC_conf.shutdown_state = 0;
    LedCC_conf.mode = LEDCC_DISPLAY;
}

void LedCC_SetWaitState(bool state)
{
    LedCC_conf.wait_state = state;
    if (LedCC_conf.mode == LEDCC_WAIT)
    {
        LEDCC_LAT = LedCC_conf.wait_state;
    }
}

void LedCC_SetIsrState(bool state)
{
    LedCC_conf.isr_state = state;
    if (LedCC_conf.mode == LEDCC_ISR)
    {
        LEDCC_LAT = LedCC_conf.isr_state;
    }
}

void LedCC_SetDisplayState(bool state)
{
    LedCC_conf.display_state = state;
    if (LedCC_conf.mode == LEDCC_DISPLAY)
    {
        LEDCC_LAT = LedCC_conf.display_state;
    }
}

void LedCC_SetShutdownState(bool state)
{
    LedCC_conf.shutdown_state = state;
    if (LedCC_conf.mode == LEDCC_SHUTDOWN)
    {
        LEDCC_LAT = LedCC_conf.shutdown_state;
    }
}


void LedCC_SetMode(ledcc_usage_t mode)
{
    LedCC_conf.mode = mode;
    if (mode == LEDCC_DISPLAY)
    {
        LEDCC_LAT = LedCC_conf.display_state;
    }
    else if (mode == LEDCC_WAIT)
    {
        LEDCC_LAT = LedCC_conf.wait_state;
    }
    else if (mode == LEDCC_ISR)
    {
        LEDCC_LAT = LedCC_conf.isr_state;
    }
    else if (mode == LEDCC_SHUTDOWN)
    {
        LEDCC_LAT = LedCC_conf.shutdown_state;
    }
}
