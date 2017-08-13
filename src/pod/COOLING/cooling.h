#ifndef _COOLING_H_
#define _COOLING_H_

#include "../../COMPAT.h"
#include "cooling__control.h"
#include "cooling__types.h"


/**
 *  Cooling Init
 */
void vCooling__Init(strCooling *sCooling);

/**
 *  Process Cooling
 */
void vCooling__Process(strCooling *sCooling);

/**
 *  Handle command, conditional, and automatic transitions
 *  Return whether or not we have transitioned
 */
void handle_cooling_transitions(strCooling *sCooling);

/**
 *  Cooling 10MS ISR
 */
void vCooling__10MS_ISR(strCooling *sCooling);

/**
 *  Cooling 100MS ISR
 */
void vCooling__100MS_ISR(strCooling *sCooling);


#endif // _COOLING_H_
