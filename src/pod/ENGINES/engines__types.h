#ifndef _ENGINES__TYPES_H_
#define _ENGINES__TYPES_H_

#include "../../COMPAT.h"
#include "../../state_machine.h"
#include "../../timers.h"



/////////////////////////////////////////////////////////////////////
//  Engines States
/////////////////////////////////////////////////////////////////////
typedef enum 
{
    ENGINES_NULL_STATE = 0,
    ENGINES_STOPPED_STATE,
    ENGINES_STARTUP_STATE,
    ENGINES_RUN_STATE,
    ENGINES_SHUTDOWN_STATE,
    ENGINES_INTERLOCK_STATE
} E_ENGINES_STATE_T;
#define E_ENGINES_STATE_N 6

// Engines state lookup
static char *engines_state_lookup[] =
{
    "ENGINES_NULL_STATE",
    "ENGINES_STOPPED_STATE",
    "ENGINES_STARTUP_STATE",
    "ENGINES_RUN_STATE",
    "ENGINES_SHUTDOWN_STATE",
    "ENGINES_INTERLOCK_STATE"
};

// Engines state lookup function
static inline const char * lookup_engines_state(const E_ENGINES_STATE_T state)
{
    return engines_state_lookup[state];
}


/////////////////////////////////////////////////////////////////////
//  Engines Commands
/////////////////////////////////////////////////////////////////////
typedef enum 
{
    ENGINES_NO_CMD = 0,
    ENGINES_START,
    ENGINES_RUN,
    ENGINES_SHUTDOWN,
    ENGINES_INTERLOCK,
    ENGINES_RELEASE_INTERLOCK

} E_ENGINES_COMMAND_T;
#define E_ENGINES_COMMAND_N 6

// Engines command lookup
static char *engines_command_lookup[] = 
{
    "ENGINES_NO_CMD",
    "ENGINES_START",
    "ENGINES_RUN",
    "ENGINES_SHUTDOWN",
    "ENGINES_INTERLOCK",
    "ENGINES_RELEASE_INTERLOCK"
};

// Engines command lookup function
static inline const char * lookup_engines_command(const E_ENGINES_COMMAND_T command)
{
    return engines_command_lookup[command];
}


/////////////////////////////////////////////////////////////////////
//  Engines command struct
/////////////////////////////////////////////////////////////////////
typedef struct 
{
    // Command
    E_ENGINES_COMMAND_T command;

    // @todo: handle indices -- e.g. brakes[0]

    struct {
                    
        
    
    } args;

} strEnginesCmd;


/////////////////////////////////////////////////////////////////////
//  Engines struct to be used in sFCU
/////////////////////////////////////////////////////////////////////
typedef struct 
{
    // Internal command (first priority)
    strEnginesCmd internal_command;

    // External command (second priority)
    strEnginesCmd external_command;

    StateMachine sm;
    
    // Determine if the subsystem will accept commands
    bool enabled;

    // Index of this subsystem in its parent. Defaults to 0 for single-instance subsystems.
    int index;

    #if DEBUG == 1U
        // For debug printing
        char name[32];  
        char absname[64];
    #endif

    
} strEngines;


/////////////////////////////////////////////////////////////////////
//  Engines Allowable commands per state
/////////////////////////////////////////////////////////////////////
static const int engines_allowed_state_commands[E_ENGINES_STATE_N][E_ENGINES_COMMAND_N] = 
{
    [ENGINES_STOPPED_STATE][ENGINES_START] = 1,
    [ENGINES_STOPPED_STATE][ENGINES_INTERLOCK] = 1,
    [ENGINES_STOPPED_STATE][ENGINES_RUN] = 1,
    [ENGINES_STOPPED_STATE][ENGINES_SHUTDOWN] = 1,
    [ENGINES_STARTUP_STATE][ENGINES_SHUTDOWN] = 1,
    [ENGINES_STARTUP_STATE][ENGINES_START] = 1,
    [ENGINES_STARTUP_STATE][ENGINES_INTERLOCK] = 1,
    [ENGINES_RUN_STATE][ENGINES_SHUTDOWN] = 1,
    [ENGINES_RUN_STATE][ENGINES_RUN] = 1,
    [ENGINES_SHUTDOWN_STATE][ENGINES_SHUTDOWN] = 1,
    [ENGINES_INTERLOCK_STATE][ENGINES_RELEASE_INTERLOCK] = 1,
    [ENGINES_INTERLOCK_STATE][ENGINES_INTERLOCK] = 1
};

static inline const bool engines_state_allows_command(const E_ENGINES_STATE_T state, const E_ENGINES_COMMAND_T command)
{
    return engines_allowed_state_commands[state][command];
}


/////////////////////////////////////////////////////////////////////
//  Engines target states by current state+command
/////////////////////////////////////////////////////////////////////
static const int engines_state_command_target_state[E_ENGINES_STATE_N][E_ENGINES_COMMAND_N] = {
    [ENGINES_STOPPED_STATE][ENGINES_START] = ENGINES_STARTUP_STATE,
    [ENGINES_STOPPED_STATE][ENGINES_INTERLOCK] = ENGINES_INTERLOCK_STATE,
    [ENGINES_STOPPED_STATE][ENGINES_RUN] = ENGINES_STARTUP_STATE,
    [ENGINES_STARTUP_STATE][ENGINES_SHUTDOWN] = ENGINES_SHUTDOWN_STATE,
    [ENGINES_RUN_STATE][ENGINES_SHUTDOWN] = ENGINES_SHUTDOWN_STATE,
    [ENGINES_INTERLOCK_STATE][ENGINES_RELEASE_INTERLOCK] = ENGINES_STOPPED_STATE
};

static inline const E_ENGINES_STATE_T get_engines_target_state(const E_ENGINES_STATE_T current_state, const E_ENGINES_COMMAND_T command)
{
    return engines_state_command_target_state[current_state][command];
}


#endif // _ENGINES__TYPES_H_
