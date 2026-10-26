/* 
 * File:   led6_app.h
 * Author: kamor
 *
 * Created on February 19, 2025, 4:21 PM
 */

#ifndef LED6_APP_H
#define	LED6_APP_H

#ifdef	__cplusplus
extern "C" {
#endif


#include "fader.h"
#include "cplex.h"

void led6_init(void);
void led6_animate(void);
void led6_off(void);
void led6_timer_interrupt_handler(void);


#ifdef	__cplusplus
}
#endif

#endif	/* LED6_APP_H */

