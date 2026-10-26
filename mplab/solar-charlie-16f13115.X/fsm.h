/* 
 * File:   fsm.h
 * Author: kamor
 *
 * Created on February 4, 2026, 1:04 AM
 */

#ifndef FSM_H
#define	FSM_H


#ifdef	__cplusplus
extern "C" {
#endif

typedef struct
{
     void (*on_entry)(void);
     void (*handler)(void);
     void (*on_exit)(void);
} State_t;

typedef struct
{
    const State_t *state;
} FSM_t;

void FSM_Initialize(FSM_t* fsm, const State_t* initial_state);
void FSM_Set_Next_State(FSM_t* fsm, const State_t* next_state);
void FSM_Dispatch(FSM_t* fsm);


#ifdef	__cplusplus
}
#endif

#endif	/* FSM_H */

