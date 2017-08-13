#ifndef _BRAKES__GUARDS_H_
#define _BRAKES__GUARDS_H_

#include "brakes__types.h"


/////////////////////////////////////////////////////////////////////
//  Brakes guard/check functions
/////////////////////////////////////////////////////////////////////
 



/////////////////////////////////////////////////////////////////////
//  Brakes transitions
/////////////////////////////////////////////////////////////////////

/**
 *  Brakes conditional transitions
 */
bool handle_brakes_conditional_transition(strBrakes *sBrakes);

/**
 *  Brakes timeout transitions
 */
bool handle_brakes_timeout_transition(strBrakes *sBrakes);

/**
 *  Brakes automatic transitions
 */
bool handle_brakes_automatic_transition(strBrakes *sBrakes);


/////////////////////////////////////////////////////////////////////
//  Brakes command handling
/////////////////////////////////////////////////////////////////////

/**
 *  Brakes command handler
 */
bool handle_brakes_command(strBrakes *sBrakes, const strBrakesCmd *cmd, strBrakesCmd *command_slot);

/**
 *  Apply changes to the system based on the command
 */
void commit_brakes_command(strBrakes *sBrakes, const strBrakesCmd *cmd, strBrakesCmd *command_slot);

/**
 *  Reject a command so that no change is made to the system
 */
void reject_brakes_command(strBrakes *sBrakes, const strBrakesCmd *cmd, const char *reject_message, strBrakesCmd *command_slot);

/**
 *  Clear command from sBrakes
 */
void clear_brakes_command(strBrakes *sBrakes, strBrakesCmd *command_slot);


/////////////////////////////////////////////////////////////////////
//  Brakes command functions
/////////////////////////////////////////////////////////////////////

/**
 *  Enable the brakes (allow movement)
 */
void internal_cmd_BRAKES_ENABLE(strBrakes *sBrakes);

/**
 *  Disable the brakes (hold in place)
 */
void internal_cmd_BRAKES_DISABLE(strBrakes *sBrakes);

/**
 *  Deploy the brakes to the deploy target at the given speed
 */
void cmd_BRAKES_HOLD(strBrakes *sBrakes);

/**
 *  Deploy the brakes to the deploy target at the given speed
 */
void cmd_BRAKES_DEPLOY(strBrakes *sBrakes);

/**
 *  Retract the brakes to the retract target at the given speed
 */
void cmd_BRAKES_RETRACT(strBrakes *sBrakes);

/**
 *  Move the brakes to the given target at the given speed
 */
void cmd_BRAKES_SEEK(strBrakes *sBrakes, int speed_what_units, int target_mm);

/**
 *  Execute a controlled brake program (for use during runs)
 */
void cmd_BRAKES_CONTROLLED_BRAKE(strBrakes *sBrakes);

/**
 *  Deploy the brakes at the maximum speed to the emergency brake target
 */
void cmd_BRAKES_EMERGENCY_BRAKE(strBrakes *sBrakes);

/**
 *  Apply an interlock to the brakes to prevent them from moving
 */
void cmd_BRAKES_INTERLOCK(strBrakes *sBrakes);

/**
 *  Release the interlock on the brakes and return them to HOLD_STATE
 */
void internal_cmd_BRAKES_RELEASE_INTERLOCK(strBrakes *sBrakes);


#endif // _BRAKES__GUARDS_H_
