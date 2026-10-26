/* 
 * File:   fsm.c
 * Author: kamor
 *
 * Created on February 4, 2026, 1:04 AM
 */

#include "fsm.h"

void FSM_Initialize(FSM_t* fsm, const State_t* initial_state)
{
    fsm->state = initial_state;
    if (fsm->state && fsm->state->on_entry)
    {
        fsm->state->on_entry();
    }
}

void FSM_Set_Next_State(FSM_t* fsm, const State_t* next_state)
{
    if (fsm->state && fsm->state->on_exit)
    {
        fsm->state->on_exit();
    }
    fsm->state = next_state;
    if (fsm->state && fsm->state->on_entry)
    {
        fsm->state->on_entry();
    }
}

void FSM_Dispatch(FSM_t* fsm)
{
    fsm->state->handler();
}