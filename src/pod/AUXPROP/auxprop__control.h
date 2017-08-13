#ifndef _AUXPROP__GUARDS_H_
#define _AUXPROP__GUARDS_H_

#include "auxprop__types.h"


/////////////////////////////////////////////////////////////////////
//  AuxProp guard/check functions
/////////////////////////////////////////////////////////////////////
 



/////////////////////////////////////////////////////////////////////
//  AuxProp transitions
/////////////////////////////////////////////////////////////////////

/**
 *  AuxProp conditional transitions
 */
bool handle_auxprop_conditional_transition(strAuxProp *sAuxProp);

/**
 *  AuxProp timeout transitions
 */
bool handle_auxprop_timeout_transition(strAuxProp *sAuxProp);

/**
 *  AuxProp automatic transitions
 */
bool handle_auxprop_automatic_transition(strAuxProp *sAuxProp);


/////////////////////////////////////////////////////////////////////
//  AuxProp command handling
/////////////////////////////////////////////////////////////////////

/**
 *  AuxProp command handler
 */
bool handle_auxprop_command(strAuxProp *sAuxProp, const strAuxPropCmd *cmd, strAuxPropCmd *command_slot);

/**
 *  Apply changes to the system based on the command
 */
void commit_auxprop_command(strAuxProp *sAuxProp, const strAuxPropCmd *cmd, strAuxPropCmd *command_slot);

/**
 *  Reject a command so that no change is made to the system
 */
void reject_auxprop_command(strAuxProp *sAuxProp, const strAuxPropCmd *cmd, const char *reject_message, strAuxPropCmd *command_slot);

/**
 *  Clear command from sAuxProp
 */
void clear_auxprop_command(strAuxProp *sAuxProp, strAuxPropCmd *command_slot);


/////////////////////////////////////////////////////////////////////
//  AuxProp command functions
/////////////////////////////////////////////////////////////////////

/**
 *  Enable auxiliary propulsion
 */
void internal_cmd_AUXPROP_ENABLE(strAuxProp *sAuxProp);

/**
 *  Transition to manual mode
 */
void internal_cmd_AUXPROP_MANUAL(strAuxProp *sAuxProp);

/**
 *  Disable auxiliary propulsion
 */
void internal_cmd_AUXPROP_DISABLE(strAuxProp *sAuxProp);

/**
 *  Drive forward
 */
void cmd_AUXPROP_DRIVE_FORWARD(strAuxProp *sAuxProp, Luint32 u32Veloc_mms);

/**
 *  Drive reverse
 */
void cmd_AUXPROP_DRIVE_REVERSE(strAuxProp *sAuxProp, Luint32 u32Veloc_mms);

/**
 *  Stop
 */
void cmd_AUXPROP_STOP(strAuxProp *sAuxProp);

/**
 *  Set the throttle
 */
void cmd_AUXPROP_SET_THROTTLE(strAuxProp *sAuxProp, Luint32 u32Veloc_mms);

/**
 *  Engage clutches. Only available in manual mode (for testing)
 */
void cmd_AUXPROP_CLUTCH_ENGAGE(strAuxProp *sAuxProp);

/**
 *  Disengage clutches. Only available in manual mode (for testing)
 */
void cmd_AUXPROP_CLUTCH_DISENGAGE(strAuxProp *sAuxProp);

/**
 *  Drive motor forward. Note: Only available in manual mode (for testing)
 */
void cmd_AUXPROP_MOTOR_FORWARD(strAuxProp *sAuxProp, Luint32 u32Veloc_mms);

/**
 *  Drive motor in reverse. Note: Only available in manual mode (for testing)
 */
void cmd_AUXPROP_MOTOR_REVERSE(strAuxProp *sAuxProp, Luint32 u32Veloc_mms);

/**
 *  Stop the motor. Only available in manual mode (for testing)
 */
void cmd_AUXPROP_MOTOR_STOP(strAuxProp *sAuxProp);


#endif // _AUXPROP__GUARDS_H_
