#ifndef _BRAKES_H_
#define _BRAKES_H_

#include "../../COMPAT.h"
#include "brakes__control.h"
#include "brakes__types.h"


/**
 *  Brakes Init
 */
void vBrakes__Init(strBrakes *sBrakes);

/**
 *  Process Brakes
 */
void vBrakes__Process(strBrakes *sBrakes);

/**
 *  Handle command, conditional, and automatic transitions
 *  Return whether or not we have transitioned
 */
void handle_brakes_transitions(strBrakes *sBrakes);

/**
 *  Brakes 10MS ISR
 */
void vBrakes__10MS_ISR(strBrakes *sBrakes);

/**
 *  Brakes 100MS ISR
 */
void vBrakes__100MS_ISR(strBrakes *sBrakes);


#endif // _BRAKES_H_
