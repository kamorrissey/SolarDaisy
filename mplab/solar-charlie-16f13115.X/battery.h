/* 
 * File:   battery.h
 * Author: kamor
 *
 * Created on February 11, 2026, 10:06 PM
 */

#ifndef BATTERY_H
#define	BATTERY_H

#include <stdbool.h>
#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

void Battery_Initialize(void);
void Battery_ISR(void);
void Battery_Task(void);
int16_t Battery_FetchReading(void);
bool Battery_IsAboveUpperThreshold(void);
bool Battery_IsBelowLowerThreshold(void);

#ifdef	__cplusplus
}
#endif

#endif	/* BATTERY_H */

