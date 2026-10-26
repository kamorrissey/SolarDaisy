/* 
 * File:   jsf8.h
 * Author: kamor
 *
 * Created on July 7, 2026, 8:27 PM
 */

#ifndef JSF8_H
#define	JSF8_H

#ifdef	__cplusplus
extern "C" {
#endif

// Jenkins small-fast 8-bit pseudo-random number generator
// Uses no multiplication

#include <stdint.h>

uint8_t jsf8(void);

void jsf8_seed(uint8_t seed);


#ifdef	__cplusplus
}
#endif

#endif	/* JSF8_H */

