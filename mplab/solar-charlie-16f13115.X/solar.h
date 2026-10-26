/* 
 * File:   solar.h
 * Author: Karen Morrissey
 *
 * Created on September 23, 2026, 7:21 AM
 */

#ifndef SOLAR_H
#define	SOLAR_H

#include "mcc_generated_files/comparator/cmp1.h"

#ifdef	__cplusplus
extern "C" {
#endif

inline bool Solar_IsDark(void)
{
    return CMP1_GetOutputStatus();
}


#ifdef	__cplusplus
}
#endif

#endif	/* SOLAR_H */

