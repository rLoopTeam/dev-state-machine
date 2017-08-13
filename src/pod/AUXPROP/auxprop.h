#ifndef _AUXPROP_H_
#define _AUXPROP_H_

#include "../../COMPAT.h"
#include "auxprop__control.h"
#include "auxprop__types.h"


/**
 *  AuxProp Init
 */
void vAuxProp__Init(strAuxProp *sAuxProp);

/**
 *  Process AuxProp
 */
void vAuxProp__Process(strAuxProp *sAuxProp);

/**
 *  Handle command, conditional, and automatic transitions
 *  Return whether or not we have transitioned
 */
void handle_auxprop_transitions(strAuxProp *sAuxProp);

/**
 *  AuxProp 10MS ISR
 */
void vAuxProp__10MS_ISR(strAuxProp *sAuxProp);

/**
 *  AuxProp 100MS ISR
 */
void vAuxProp__100MS_ISR(strAuxProp *sAuxProp);


#endif // _AUXPROP_H_
