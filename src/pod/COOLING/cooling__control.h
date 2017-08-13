#ifndef _COOLING__GUARDS_H_
#define _COOLING__GUARDS_H_

#include "cooling__types.h"


/////////////////////////////////////////////////////////////////////
//  Cooling guard/check functions
/////////////////////////////////////////////////////////////////////
 



/////////////////////////////////////////////////////////////////////
//  Cooling transitions
/////////////////////////////////////////////////////////////////////

/**
 *  Cooling conditional transitions
 */
bool handle_cooling_conditional_transition(strCooling *sCooling);

/**
 *  Cooling timeout transitions
 */
bool handle_cooling_timeout_transition(strCooling *sCooling);

/**
 *  Cooling automatic transitions
 */
bool handle_cooling_automatic_transition(strCooling *sCooling);


/////////////////////////////////////////////////////////////////////
//  Cooling command handling
/////////////////////////////////////////////////////////////////////

/**
 *  Cooling command handler
 */
bool handle_cooling_command(strCooling *sCooling, const strCoolingCmd *cmd, strCoolingCmd *command_slot);

/**
 *  Apply changes to the system based on the command
 */
void commit_cooling_command(strCooling *sCooling, const strCoolingCmd *cmd, strCoolingCmd *command_slot);

/**
 *  Reject a command so that no change is made to the system
 */
void reject_cooling_command(strCooling *sCooling, const strCoolingCmd *cmd, const char *reject_message, strCoolingCmd *command_slot);

/**
 *  Clear command from sCooling
 */
void clear_cooling_command(strCooling *sCooling, strCoolingCmd *command_slot);


/////////////////////////////////////////////////////////////////////
//  Cooling command functions
/////////////////////////////////////////////////////////////////////

/**
 *  Shut all valves
 */
void internal_cmd_COOLING_DISABLE(strCooling *sCooling);

/**
 *  Run automatic cooling
 */
void cmd_COOLING_AUTO(strCooling *sCooling);

/**
 *  Shut the main valve (if we have one), then open the end valves for x seconds, the shut the end valves.
 */
void cmd_COOLING_PURGE(strCooling *sCooling);

/**
 *  Put cooling system into manual mode
 */
void cmd_COOLING_MANUAL(strCooling *sCooling);

/**
 *  Apply an interlock to the cooling system to prevent it from operating
 */
void cmd_COOLING_INTERLOCK(strCooling *sCooling);

/**
 *  Release the interlock on the cooling system and return them to COOLING_DISABLED_STATE
 */
void cmd_COOLING_RELEASE_INTERLOCK(strCooling *sCooling);

/**
 *  Set the cooling duty cycle. Note: what about different duty cycles for brakes vs engines? Should we have those as commands to our subsystems?
 */
void cmd_COOLING_SET_DUTY_CYCLE(strCooling *sCooling);


#endif // _COOLING__GUARDS_H_
