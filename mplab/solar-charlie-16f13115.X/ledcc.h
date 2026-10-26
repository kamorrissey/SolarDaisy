/* 
 * File:   ledcc.h
 * Author: kamor
 *
 * Created on January 20, 2026, 12:10 PM
 */

#ifndef LEDCC_H
#define	LEDCC_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdbool.h>

// The pin for the color-changing LED is also used for debugging purposes.
typedef enum
{
    LEDCC_DISPLAY,  // Run the color-changing LED
    LEDCC_ISR,      // High when in ISR
    LEDCC_WAIT,     // High when in wait state
    LEDCC_SHUTDOWN, // High when in shutdown state
} ledcc_usage_t;

void LedCC_Initialize(void);

void LedCC_SetWaitState(bool state);

void LedCC_SetIsrState(bool state);

void LedCC_SetDisplayState(bool state);

void LedCC_SetShutdownState(bool state);

void LedCC_SetMode(ledcc_usage_t mode);


#ifdef	__cplusplus
}
#endif

#endif	/* LEDCC_H */

