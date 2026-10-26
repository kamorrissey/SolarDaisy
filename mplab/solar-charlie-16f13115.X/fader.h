/* 
 * File:   fader.h
 * Author: kamor
 *
 * Created on September 29, 2024, 4:14 PM
 */

#ifndef FADER_H
#define	FADER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    int16_t current_fp;      // Current value in fixed-point representation
    int16_t step_fp;         // Fixed-point increment per step
    int16_t steps_remaining; // Number of steps remaining
    int16_t target_fp;       // Target integer value in fixed-point
} Fader;

int16_t Fader_GetValue(const Fader* f);

void Fader_SetValue(Fader* f, int16_t value);

void Fader_SetTarget(Fader* f, int16_t targetValue, int16_t steps);

void Fader_Step(Fader* f);

bool Fader_HasNext(const Fader* f);

#ifdef	__cplusplus
}
#endif

#endif	/* FADER_H */

