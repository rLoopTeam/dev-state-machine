#ifndef _ENGINES__GUARDS_H_
#define _ENGINES__GUARDS_H_

#include "engines__types.h"


/////////////////////////////////////////////////////////////////////
//  Engines guard/check functions
/////////////////////////////////////////////////////////////////////
 
/**
 * engine_startup_error
 */
bool engine_startup_error(strEngines * sEngines);


/////////////////////////////////////////////////////////////////////
//  Engines transitions
/////////////////////////////////////////////////////////////////////

/**
 *  Engines conditional transitions
 */
bool handle_engines_conditional_transition(strEngines *sEngines);

/**
 *  Engines timeout transitions
 */
bool handle_engines_timeout_transition(strEngines *sEngines);

/**
 *  Engines automatic transitions
 */
bool handle_engines_automatic_transition(strEngines *sEngines);


/////////////////////////////////////////////////////////////////////
//  Engines command handling
/////////////////////////////////////////////////////////////////////

/**
 *  Engines command handler
 */
bool handle_engines_command(strEngines *sEngines, const strEnginesCmd *cmd, strEnginesCmd *command_slot);

/**
 *  Apply changes to the system based on the command
 */
void commit_engines_command(strEngines *sEngines, const strEnginesCmd *cmd, strEnginesCmd *command_slot);

/**
 *  Reject a command so that no change is made to the system
 */
void reject_engines_command(strEngines *sEngines, const strEnginesCmd *cmd, const char *reject_message, strEnginesCmd *command_slot);

/**
 *  Clear command from sEngines
 */
void clear_engines_command(strEngines *sEngines, strEnginesCmd *command_slot);


/////////////////////////////////////////////////////////////////////
//  Engines command functions
/////////////////////////////////////////////////////////////////////

/**
 *  Start the engines
 */
void cmd_ENGINES_START(strEngines *sEngines);

/**
 *  Run the engines
 */
void cmd_ENGINES_RUN(strEngines *sEngines);

/**
 *  shut down the engines
 */
void cmd_ENGINES_SHUTDOWN(strEngines *sEngines);

/**
 *  Lock the hover engines from turing on
 */
void cmd_ENGINES_INTERLOCK(strEngines *sEngines);

/**
 *  Release the engines interlock
 */
void cmd_ENGINES_RELEASE_INTERLOCK(strEngines *sEngines);


#endif // _ENGINES__GUARDS_H_
