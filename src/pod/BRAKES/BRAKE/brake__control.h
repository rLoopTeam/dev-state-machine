#ifndef _BRAKE__GUARDS_H_
#define _BRAKE__GUARDS_H_

#include "brake__types.h"


/////////////////////////////////////////////////////////////////////
//  Brake guard/check functions
/////////////////////////////////////////////////////////////////////
 



/////////////////////////////////////////////////////////////////////
//  Brake transitions
/////////////////////////////////////////////////////////////////////

/**
 *  Brake conditional transitions
 */
bool handle_brake_conditional_transition(strBrake *sBrake);

/**
 *  Brake timeout transitions
 */
bool handle_brake_timeout_transition(strBrake *sBrake);

/**
 *  Brake automatic transitions
 */
bool handle_brake_automatic_transition(strBrake *sBrake);


/////////////////////////////////////////////////////////////////////
//  Brake command handling
/////////////////////////////////////////////////////////////////////

/**
 *  Brake command handler
 */
bool handle_brake_command(strBrake *sBrake, const strBrakeCmd *cmd, strBrakeCmd *command_slot);

/**
 *  Apply changes to the system based on the command
 */
void commit_brake_command(strBrake *sBrake, const strBrakeCmd *cmd, strBrakeCmd *command_slot);

/**
 *  Reject a command so that no change is made to the system
 */
void reject_brake_command(strBrake *sBrake, const strBrakeCmd *cmd, const char *reject_message, strBrakeCmd *command_slot);

/**
 *  Clear command from sBrake
 */
void clear_brake_command(strBrake *sBrake, strBrakeCmd *command_slot);


/////////////////////////////////////////////////////////////////////
//  Brake command functions
/////////////////////////////////////////////////////////////////////

/**
 *  Hold the brakes in place
 */
void cmd_SINGLE_BRAKE_HOLD(strBrake *sBrake);

/**
 *  Deploy the brakes to the deploy target at the given speed
 */
void cmd_SINGLE_BRAKE_DEPLOY(strBrake *sBrake);

/**
 *  Retract the brakes to the retract target at the given speed
 */
void cmd_SINGLE_BRAKE_RETRACT(strBrake *sBrake);

/**
 *  Move the brakes to the given target at the given speed
 */
void cmd_SINGLE_BRAKE_SEEK(strBrake *sBrake, int speed_what_units, int target_mm);

/**
 *  Apply an interlock to the brakes to prevent them from moving
 */
void cmd_SINGLE_BRAKE_INTERLOCK(strBrake *sBrake);

/**
 *  Release the interlock on the brakes and return them to HOLD_STATE
 */
void cmd_SINGLE_BRAKE_RELEASE_INTERLOCK(strBrake *sBrake);


#endif // _BRAKE__GUARDS_H_
