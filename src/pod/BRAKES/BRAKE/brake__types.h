#ifndef _BRAKE__TYPES_H_
#define _BRAKE__TYPES_H_

#include "../../../COMPAT.h"
#include "../../../state_machine.h"
#include "../../../timers.h"



/////////////////////////////////////////////////////////////////////
//  Brake States
/////////////////////////////////////////////////////////////////////
typedef enum 
{
    BRAKE_NULL_STATE = 0,
    SINGLE_BRAKE_HOLD_STATE,
    SINGLE_BRAKE_DEPLOY_STATE,
    SINGLE_BRAKE_RETRACT_STATE,
    SINGLE_BRAKE_SEEK_STATE,
    SINGLE_BRAKE_INTERLOCK_STATE
} E_BRAKE_STATE_T;
#define E_BRAKE_STATE_N 6

// Brake state lookup
static char *brake_state_lookup[] =
{
    "BRAKE_NULL_STATE",
    "SINGLE_BRAKE_HOLD_STATE",
    "SINGLE_BRAKE_DEPLOY_STATE",
    "SINGLE_BRAKE_RETRACT_STATE",
    "SINGLE_BRAKE_SEEK_STATE",
    "SINGLE_BRAKE_INTERLOCK_STATE"
};

// Brake state lookup function
static inline const char * lookup_brake_state(const E_BRAKE_STATE_T state)
{
    return brake_state_lookup[state];
}


/////////////////////////////////////////////////////////////////////
//  Brake Commands
/////////////////////////////////////////////////////////////////////
typedef enum 
{
    BRAKE_NO_CMD = 0,
    SINGLE_BRAKE_HOLD,
    SINGLE_BRAKE_DEPLOY,
    SINGLE_BRAKE_RETRACT,
    SINGLE_BRAKE_SEEK,
    SINGLE_BRAKE_INTERLOCK,
    SINGLE_BRAKE_RELEASE_INTERLOCK

} E_BRAKE_COMMAND_T;
#define E_BRAKE_COMMAND_N 7

// Brake command lookup
static char *brake_command_lookup[] = 
{
    "BRAKE_NO_CMD",
    "SINGLE_BRAKE_HOLD",
    "SINGLE_BRAKE_DEPLOY",
    "SINGLE_BRAKE_RETRACT",
    "SINGLE_BRAKE_SEEK",
    "SINGLE_BRAKE_INTERLOCK",
    "SINGLE_BRAKE_RELEASE_INTERLOCK"
};

// Brake command lookup function
static inline const char * lookup_brake_command(const E_BRAKE_COMMAND_T command)
{
    return brake_command_lookup[command];
}


/////////////////////////////////////////////////////////////////////
//  Brake command struct
/////////////////////////////////////////////////////////////////////
typedef struct 
{
    // Command
    E_BRAKE_COMMAND_T command;

    // @todo: handle indices -- e.g. brakes[0]

    struct {
                    
        struct {
                        
            int speed_what_units;
            int target_mm;
        
        } SINGLE_BRAKE_SEEK;
    
    } args;

} strBrakeCmd;


/////////////////////////////////////////////////////////////////////
//  Brake struct to be used in sFCU
/////////////////////////////////////////////////////////////////////
typedef struct 
{
    // Internal command (first priority)
    strBrakeCmd internal_command;

    // External command (second priority)
    strBrakeCmd external_command;

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

    
} strBrake;


/////////////////////////////////////////////////////////////////////
//  Brake Allowable commands per state
/////////////////////////////////////////////////////////////////////
static const int brake_allowed_state_commands[E_BRAKE_STATE_N][E_BRAKE_COMMAND_N] = 
{
    [SINGLE_BRAKE_HOLD_STATE][SINGLE_BRAKE_DEPLOY] = 1,
    [SINGLE_BRAKE_HOLD_STATE][SINGLE_BRAKE_RETRACT] = 1,
    [SINGLE_BRAKE_HOLD_STATE][SINGLE_BRAKE_SEEK] = 1,
    [SINGLE_BRAKE_HOLD_STATE][SINGLE_BRAKE_INTERLOCK] = 1,
    [SINGLE_BRAKE_DEPLOY_STATE][SINGLE_BRAKE_HOLD] = 1,
    [SINGLE_BRAKE_DEPLOY_STATE][SINGLE_BRAKE_RETRACT] = 1,
    [SINGLE_BRAKE_DEPLOY_STATE][SINGLE_BRAKE_SEEK] = 1,
    [SINGLE_BRAKE_DEPLOY_STATE][SINGLE_BRAKE_INTERLOCK] = 1,
    [SINGLE_BRAKE_RETRACT_STATE][SINGLE_BRAKE_HOLD] = 1,
    [SINGLE_BRAKE_RETRACT_STATE][SINGLE_BRAKE_DEPLOY] = 1,
    [SINGLE_BRAKE_RETRACT_STATE][SINGLE_BRAKE_SEEK] = 1,
    [SINGLE_BRAKE_RETRACT_STATE][SINGLE_BRAKE_INTERLOCK] = 1,
    [SINGLE_BRAKE_SEEK_STATE][SINGLE_BRAKE_HOLD] = 1,
    [SINGLE_BRAKE_SEEK_STATE][SINGLE_BRAKE_DEPLOY] = 1,
    [SINGLE_BRAKE_SEEK_STATE][SINGLE_BRAKE_RETRACT] = 1,
    [SINGLE_BRAKE_SEEK_STATE][SINGLE_BRAKE_SEEK] = 1,
    [SINGLE_BRAKE_SEEK_STATE][SINGLE_BRAKE_INTERLOCK] = 1,
    [SINGLE_BRAKE_INTERLOCK_STATE][SINGLE_BRAKE_RELEASE_INTERLOCK] = 1
};

static inline const bool brake_state_allows_command(const E_BRAKE_STATE_T state, const E_BRAKE_COMMAND_T command)
{
    return brake_allowed_state_commands[state][command];
}


/////////////////////////////////////////////////////////////////////
//  Brake target states by current state+command
/////////////////////////////////////////////////////////////////////
static const int brake_state_command_target_state[E_BRAKE_STATE_N][E_BRAKE_COMMAND_N] = {
    [SINGLE_BRAKE_HOLD_STATE][SINGLE_BRAKE_DEPLOY] = SINGLE_BRAKE_DEPLOY_STATE,
    [SINGLE_BRAKE_HOLD_STATE][SINGLE_BRAKE_RETRACT] = SINGLE_BRAKE_RETRACT_STATE,
    [SINGLE_BRAKE_HOLD_STATE][SINGLE_BRAKE_SEEK] = SINGLE_BRAKE_SEEK_STATE,
    [SINGLE_BRAKE_HOLD_STATE][SINGLE_BRAKE_INTERLOCK] = SINGLE_BRAKE_INTERLOCK_STATE,
    [SINGLE_BRAKE_DEPLOY_STATE][SINGLE_BRAKE_HOLD] = SINGLE_BRAKE_HOLD_STATE,
    [SINGLE_BRAKE_DEPLOY_STATE][SINGLE_BRAKE_RETRACT] = SINGLE_BRAKE_RETRACT_STATE,
    [SINGLE_BRAKE_DEPLOY_STATE][SINGLE_BRAKE_SEEK] = SINGLE_BRAKE_SEEK_STATE,
    [SINGLE_BRAKE_DEPLOY_STATE][SINGLE_BRAKE_INTERLOCK] = SINGLE_BRAKE_INTERLOCK_STATE,
    [SINGLE_BRAKE_RETRACT_STATE][SINGLE_BRAKE_HOLD] = SINGLE_BRAKE_HOLD_STATE,
    [SINGLE_BRAKE_RETRACT_STATE][SINGLE_BRAKE_DEPLOY] = SINGLE_BRAKE_DEPLOY_STATE,
    [SINGLE_BRAKE_RETRACT_STATE][SINGLE_BRAKE_SEEK] = SINGLE_BRAKE_SEEK_STATE,
    [SINGLE_BRAKE_RETRACT_STATE][SINGLE_BRAKE_INTERLOCK] = SINGLE_BRAKE_INTERLOCK_STATE,
    [SINGLE_BRAKE_SEEK_STATE][SINGLE_BRAKE_HOLD] = SINGLE_BRAKE_HOLD_STATE,
    [SINGLE_BRAKE_SEEK_STATE][SINGLE_BRAKE_DEPLOY] = SINGLE_BRAKE_DEPLOY_STATE,
    [SINGLE_BRAKE_SEEK_STATE][SINGLE_BRAKE_RETRACT] = SINGLE_BRAKE_RETRACT_STATE,
    [SINGLE_BRAKE_SEEK_STATE][SINGLE_BRAKE_SEEK] = SINGLE_BRAKE_SEEK_STATE,
    [SINGLE_BRAKE_SEEK_STATE][SINGLE_BRAKE_INTERLOCK] = SINGLE_BRAKE_INTERLOCK_STATE,
    [SINGLE_BRAKE_INTERLOCK_STATE][SINGLE_BRAKE_RELEASE_INTERLOCK] = SINGLE_BRAKE_HOLD_STATE
};

static inline const E_BRAKE_STATE_T get_brake_target_state(const E_BRAKE_STATE_T current_state, const E_BRAKE_COMMAND_T command)
{
    return brake_state_command_target_state[current_state][command];
}


#endif // _BRAKE__TYPES_H_
