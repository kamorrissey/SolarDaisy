
#include "fader.h"

/*
 * For an 8-bit MCU with 16-bit int, we use a small fixed-point factor.
 * Here, SHIFT == 4 (i.e. FIX_SCALE == 16) to avoid overflow.
 */
#define SHIFT 4
#define FIX_SCALE (1 << SHIFT)

/*
 * Fader_SetValue()
 *
 *   Sets the starting value of the fade.
 *   This function initializes the internal fixed-point accumulator.
 */
void Fader_SetValue(Fader* fader, int16_t value)
{
    fader->steps_remaining = 0;
    fader->current_fp = fader->target_fp = value * FIX_SCALE;
}

/*
 * Fader_SetTarget()
 *
 *   Configures the fade to a target value with a given number of steps.
 *   The starting value must have been set previously via Fader_set_start().
 *   'steps' is the number of fade steps (starting value is not counted).
 *   After 'steps' calls to Fader_next(), the fade will reach the target value.
 */
void Fader_SetTarget(Fader* fader, int16_t target, int16_t steps)
{
    if (steps <= 0)
        steps = 1;
    fader->steps_remaining = steps;
    fader->target_fp = target * FIX_SCALE;
    fader->step_fp = (fader->target_fp - fader->current_fp) / steps;
}

/*
 * Fader_GetValue()
 *
 *   Returns the current integer value of the fade by rounding the fixed-point value.
 */
int16_t Fader_GetValue(const Fader* fader)
{
    if (fader->current_fp >= 0) {
        return (fader->current_fp + (FIX_SCALE >> 1)) >> SHIFT;
    }
    else {
        return -((-fader->current_fp + (FIX_SCALE >> 1)) >> SHIFT);
    }
}

/*
 * Fader_Step()
 *
 *   Advances the fade one step and returns the next integer value.
 *   The starting value is not counted as a step; the first call to Fader_next()
 *   returns one step away from the starting value, and the final call returns
 *   exactly the target value.
 *
 *   This function uses only addition and bit shifts.
 */
void Fader_Step(Fader* fader)
{
    if (fader->steps_remaining == 1)
    {
        // Final step: force the target value.
        fader->current_fp = fader->target_fp;
        fader->steps_remaining = 0;
    }
    else if (fader->steps_remaining > 1)
    {
        fader->current_fp += fader->step_fp;
        --fader->steps_remaining;
    }
}

/*
 * Fader_HasNext()
 *
 *   Returns true if the fade is complete (i.e., no steps remaining).
 */
bool Fader_HasNext(const Fader* fader)
{
    return fader->steps_remaining > 0;
}
