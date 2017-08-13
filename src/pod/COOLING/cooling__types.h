#ifndef _COOLING__TYPES_H_
#define _COOLING__TYPES_H_

#include "../../COMPAT.h"
#include "../../state_machine.h"
#include "../../timers.h"



/////////////////////////////////////////////////////////////////////
//  Cooling States
/////////////////////////////////////////////////////////////////////
typedef enum 
{
    COOLING_NULL_STATE = 0,
    COOLING_DISABLED_STATE,
    COOLING_AUTO_STATE,
    COOLING_PURGE_STATE,
    COOLING_MANUAL_STATE,
    COOLING_INTERLOCK_STATE
} E_COOLING_STATE_T;
#define E_COOLING_STATE_N 6

// Cooling state lookup
static char *cooling_state_lookup[] =
{
    "COOLING_NULL_STATE",
    "COOLING_DISABLED_STATE",
    "COOLING_AUTO_STATE",
    "COOLING_PURGE_STATE",
    "COOLING_MANUAL_STATE",
    "COOLING_INTERLOCK_STATE"
};

// Cooling state lookup function
static inline const char * lookup_cooling_state(const E_COOLING_STATE_T state)
{
    return cooling_state_lookup[state];
}


/////////////////////////////////////////////////////////////////////
//  Cooling Commands
/////////////////////////////////////////////////////////////////////
typedef enum 
{
    COOLING_NO_CMD = 0,
    COOLING_DISABLE,
    COOLING_AUTO,
    COOLING_PURGE,
    COOLING_MANUAL,
    COOLING_INTERLOCK,
    COOLING_RELEASE_INTERLOCK,
    COOLING_SET_DUTY_CYCLE

} E_COOLING_COMMAND_T;
#define E_COOLING_COMMAND_N 8

// Cooling command lookup
static char *cooling_command_lookup[] = 
{
    "COOLING_NO_CMD",
    "COOLING_DISABLE",
    "COOLING_AUTO",
    "COOLING_PURGE",
    "COOLING_MANUAL",
    "COOLING_INTERLOCK",
    "COOLING_RELEASE_INTERLOCK",
    "COOLING_SET_DUTY_CYCLE"
};

// Cooling command lookup function
static inline const char * lookup_cooling_command(const E_COOLING_COMMAND_T command)
{
    return cooling_command_lookup[command];
}


/////////////////////////////////////////////////////////////////////
//  Cooling command struct
/////////////////////////////////////////////////////////////////////
typedef struct 
{
    // Command
    E_COOLING_COMMAND_T command;

    // @todo: handle indices -- e.g. brakes[0]

    struct {
                    
        
    
    } args;

} strCoolingCmd;


/////////////////////////////////////////////////////////////////////
//  Cooling struct to be used in sFCU
/////////////////////////////////////////////////////////////////////
typedef struct 
{
    // Internal command (first priority)
    strCoolingCmd internal_command;

    // External command (second priority)
    strCoolingCmd external_command;

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

    
} strCooling;


/////////////////////////////////////////////////////////////////////
//  Cooling Allowable commands per state
/////////////////////////////////////////////////////////////////////
static const int cooling_allowed_state_commands[E_COOLING_STATE_N][E_COOLING_COMMAND_N] = 
{
    [COOLING_DISABLED_STATE][COOLING_AUTO] = 1,
    [COOLING_DISABLED_STATE][COOLING_PURGE] = 1,
    [COOLING_DISABLED_STATE][COOLING_MANUAL] = 1,
    [COOLING_DISABLED_STATE][COOLING_INTERLOCK] = 1,
    [COOLING_DISABLED_STATE][COOLING_DISABLE] = 1,
    [COOLING_AUTO_STATE][COOLING_DISABLE] = 1,
    [COOLING_AUTO_STATE][COOLING_PURGE] = 1,
    [COOLING_AUTO_STATE][COOLING_MANUAL] = 1,
    [COOLING_AUTO_STATE][COOLING_INTERLOCK] = 1,
    [COOLING_AUTO_STATE][COOLING_AUTO] = 1,
    [COOLING_PURGE_STATE][COOLING_DISABLE] = 1,
    [COOLING_PURGE_STATE][COOLING_AUTO] = 1,
    [COOLING_PURGE_STATE][COOLING_MANUAL] = 1,
    [COOLING_PURGE_STATE][COOLING_INTERLOCK] = 1,
    [COOLING_PURGE_STATE][COOLING_PURGE] = 1,
    [COOLING_MANUAL_STATE][COOLING_DISABLE] = 1,
    [COOLING_MANUAL_STATE][COOLING_AUTO] = 1,
    [COOLING_MANUAL_STATE][COOLING_INTERLOCK] = 1,
    [COOLING_MANUAL_STATE][COOLING_PURGE] = 1,
    [COOLING_MANUAL_STATE][COOLING_MANUAL] = 1,
    [COOLING_INTERLOCK_STATE][COOLING_RELEASE_INTERLOCK] = 1,
    [COOLING_INTERLOCK_STATE][COOLING_INTERLOCK] = 1
};

static inline const bool cooling_state_allows_command(const E_COOLING_STATE_T state, const E_COOLING_COMMAND_T command)
{
    return cooling_allowed_state_commands[state][command];
}


/////////////////////////////////////////////////////////////////////
//  Cooling target states by current state+command
/////////////////////////////////////////////////////////////////////
static const int cooling_state_command_target_state[E_COOLING_STATE_N][E_COOLING_COMMAND_N] = {
    [COOLING_DISABLED_STATE][COOLING_AUTO] = COOLING_AUTO_STATE,
    [COOLING_DISABLED_STATE][COOLING_PURGE] = COOLING_PURGE_STATE,
    [COOLING_DISABLED_STATE][COOLING_MANUAL] = COOLING_MANUAL_STATE,
    [COOLING_DISABLED_STATE][COOLING_INTERLOCK] = COOLING_INTERLOCK_STATE,
    [COOLING_AUTO_STATE][COOLING_DISABLE] = COOLING_DISABLED_STATE,
    [COOLING_AUTO_STATE][COOLING_PURGE] = COOLING_PURGE_STATE,
    [COOLING_AUTO_STATE][COOLING_MANUAL] = COOLING_MANUAL_STATE,
    [COOLING_AUTO_STATE][COOLING_INTERLOCK] = COOLING_INTERLOCK_STATE,
    [COOLING_PURGE_STATE][COOLING_DISABLE] = COOLING_DISABLED_STATE,
    [COOLING_PURGE_STATE][COOLING_AUTO] = COOLING_AUTO_STATE,
    [COOLING_PURGE_STATE][COOLING_MANUAL] = COOLING_MANUAL_STATE,
    [COOLING_PURGE_STATE][COOLING_INTERLOCK] = COOLING_INTERLOCK_STATE,
    [COOLING_MANUAL_STATE][COOLING_DISABLE] = COOLING_DISABLED_STATE,
    [COOLING_MANUAL_STATE][COOLING_AUTO] = COOLING_AUTO_STATE,
    [COOLING_MANUAL_STATE][COOLING_INTERLOCK] = COOLING_INTERLOCK_STATE,
    [COOLING_MANUAL_STATE][COOLING_PURGE] = COOLING_PURGE_STATE,
    [COOLING_INTERLOCK_STATE][COOLING_RELEASE_INTERLOCK] = COOLING_DISABLED_STATE
};

static inline const E_COOLING_STATE_T get_cooling_target_state(const E_COOLING_STATE_T current_state, const E_COOLING_COMMAND_T command)
{
    return cooling_state_command_target_state[current_state][command];
}


#endif // _COOLING__TYPES_H_
