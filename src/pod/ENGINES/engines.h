#ifndef _ENGINES_H_
#define _ENGINES_H_

#include "../../COMPAT.h"
#include "engines__control.h"
#include "engines__types.h"


/**
 *  Engines Init
 */
void vEngines__Init(strEngines *sEngines);

/**
 *  Process Engines
 */
void vEngines__Process(strEngines *sEngines);

/**
 *  Handle command, conditional, and automatic transitions
 *  Return whether or not we have transitioned
 */
void handle_engines_transitions(strEngines *sEngines);

/**
 *  Engines 10MS ISR
 */
void vEngines__10MS_ISR(strEngines *sEngines);

/**
 *  Engines 100MS ISR
 */
void vEngines__100MS_ISR(strEngines *sEngines);


#endif // _ENGINES_H_
