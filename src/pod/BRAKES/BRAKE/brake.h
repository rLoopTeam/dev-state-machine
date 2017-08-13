#ifndef _BRAKE_H_
#define _BRAKE_H_

#include "../../../COMPAT.h"
#include "brake__control.h"
#include "brake__types.h"


/**
 *  Brake Init
 */
void vBrake__Init(strBrake *sBrake);

/**
 *  Process Brake
 */
void vBrake__Process(strBrake *sBrake);

/**
 *  Handle command, conditional, and automatic transitions
 *  Return whether or not we have transitioned
 */
void handle_brake_transitions(strBrake *sBrake);

/**
 *  Brake 10MS ISR
 */
void vBrake__10MS_ISR(strBrake *sBrake);

/**
 *  Brake 100MS ISR
 */
void vBrake__100MS_ISR(strBrake *sBrake);


#endif // _BRAKE_H_
