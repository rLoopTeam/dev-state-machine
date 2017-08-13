#ifndef _AUXPROP__TYPES_H_
#define _AUXPROP__TYPES_H_

#include "../../COMPAT.h"
#include "../../state_machine.h"
#include "../../timers.h"



/////////////////////////////////////////////////////////////////////
//  AuxProp States
/////////////////////////////////////////////////////////////////////
typedef enum 
{
    AUXPROP_NULL_STATE = 0,
    AUXPROP_DISABLED_STATE,
    AUXPROP_ENABLED_STATE,
    AUXPROP_MANUAL_STATE
} E_AUXPROP_STATE_T;
#define E_AUXPROP_STATE_N 4

// AuxProp state lookup
static char *auxprop_state_lookup[] =
{
    "AUXPROP_NULL_STATE",
    "AUXPROP_DISABLED_STATE",
    "AUXPROP_ENABLED_STATE",
    "AUXPROP_MANUAL_STATE"
};

// AuxProp state lookup function
static inline const char * lookup_auxprop_state(const E_AUXPROP_STATE_T state)
{
    return auxprop_state_lookup[state];
}


/////////////////////////////////////////////////////////////////////
//  AuxProp Commands
/////////////////////////////////////////////////////////////////////
typedef enum 
{
    AUXPROP_NO_CMD = 0,
    AUXPROP_ENABLE,
    AUXPROP_MANUAL,
    AUXPROP_DISABLE,
    AUXPROP_DRIVE_FORWARD,
    AUXPROP_DRIVE_REVERSE,
    AUXPROP_STOP,
    AUXPROP_SET_THROTTLE,
    AUXPROP_CLUTCH_ENGAGE,
    AUXPROP_CLUTCH_DISENGAGE,
    AUXPROP_MOTOR_FORWARD,
    AUXPROP_MOTOR_REVERSE,
    AUXPROP_MOTOR_STOP

} E_AUXPROP_COMMAND_T;
#define E_AUXPROP_COMMAND_N 13

// AuxProp command lookup
static char *auxprop_command_lookup[] = 
{
    "AUXPROP_NO_CMD",
    "AUXPROP_ENABLE",
    "AUXPROP_MANUAL",
    "AUXPROP_DISABLE",
    "AUXPROP_DRIVE_FORWARD",
    "AUXPROP_DRIVE_REVERSE",
    "AUXPROP_STOP",
    "AUXPROP_SET_THROTTLE",
    "AUXPROP_CLUTCH_ENGAGE",
    "AUXPROP_CLUTCH_DISENGAGE",
    "AUXPROP_MOTOR_FORWARD",
    "AUXPROP_MOTOR_REVERSE",
    "AUXPROP_MOTOR_STOP"
};

// AuxProp command lookup function
static inline const char * lookup_auxprop_command(const E_AUXPROP_COMMAND_T command)
{
    return auxprop_command_lookup[command];
}


/////////////////////////////////////////////////////////////////////
//  AuxProp command struct
/////////////////////////////////////////////////////////////////////
typedef struct 
{
    // Command
    E_AUXPROP_COMMAND_T command;

    // @todo: handle indices -- e.g. brakes[0]

    struct {
                    
        struct {
                        
            Luint32 u32Veloc_mms;
        
        } AUXPROP_DRIVE_FORWARD;
        
        struct {
                        
            Luint32 u32Veloc_mms;
        
        } AUXPROP_DRIVE_REVERSE;
        
        struct {
                        
            Luint32 u32Veloc_mms;
        
        } AUXPROP_SET_THROTTLE;
        
        struct {
                        
            Luint32 u32Veloc_mms;
        
        } AUXPROP_MOTOR_FORWARD;
        
        struct {
                        
            Luint32 u32Veloc_mms;
        
        } AUXPROP_MOTOR_REVERSE;
    
    } args;

} strAuxPropCmd;


/////////////////////////////////////////////////////////////////////
//  AuxProp struct to be used in sFCU
/////////////////////////////////////////////////////////////////////
typedef struct 
{
    // Internal command (first priority)
    strAuxPropCmd internal_command;

    // External command (second priority)
    strAuxPropCmd external_command;

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

    
} strAuxProp;


/////////////////////////////////////////////////////////////////////
//  AuxProp Allowable commands per state
/////////////////////////////////////////////////////////////////////
static const int auxprop_allowed_state_commands[E_AUXPROP_STATE_N][E_AUXPROP_COMMAND_N] = 
{
    [AUXPROP_DISABLED_STATE][AUXPROP_ENABLE] = 1,
    [AUXPROP_DISABLED_STATE][AUXPROP_MANUAL] = 1,
    [AUXPROP_DISABLED_STATE][AUXPROP_DISABLE] = 1,
    [AUXPROP_ENABLED_STATE][AUXPROP_DISABLE] = 1,
    [AUXPROP_ENABLED_STATE][AUXPROP_MANUAL] = 1,
    [AUXPROP_ENABLED_STATE][AUXPROP_DRIVE_FORWARD] = 1,
    [AUXPROP_ENABLED_STATE][AUXPROP_DRIVE_REVERSE] = 1,
    [AUXPROP_ENABLED_STATE][AUXPROP_STOP] = 1,
    [AUXPROP_ENABLED_STATE][AUXPROP_SET_THROTTLE] = 1,
    [AUXPROP_ENABLED_STATE][AUXPROP_ENABLE] = 1,
    [AUXPROP_MANUAL_STATE][AUXPROP_DISABLE] = 1,
    [AUXPROP_MANUAL_STATE][AUXPROP_MANUAL] = 1,
    [AUXPROP_MANUAL_STATE][AUXPROP_DRIVE_FORWARD] = 1,
    [AUXPROP_MANUAL_STATE][AUXPROP_DRIVE_REVERSE] = 1,
    [AUXPROP_MANUAL_STATE][AUXPROP_STOP] = 1,
    [AUXPROP_MANUAL_STATE][AUXPROP_SET_THROTTLE] = 1,
    [AUXPROP_MANUAL_STATE][AUXPROP_CLUTCH_ENGAGE] = 1,
    [AUXPROP_MANUAL_STATE][AUXPROP_CLUTCH_DISENGAGE] = 1,
    [AUXPROP_MANUAL_STATE][AUXPROP_MOTOR_FORWARD] = 1,
    [AUXPROP_MANUAL_STATE][AUXPROP_MOTOR_REVERSE] = 1,
    [AUXPROP_MANUAL_STATE][AUXPROP_MOTOR_STOP] = 1
};

static inline const bool auxprop_state_allows_command(const E_AUXPROP_STATE_T state, const E_AUXPROP_COMMAND_T command)
{
    return auxprop_allowed_state_commands[state][command];
}


/////////////////////////////////////////////////////////////////////
//  AuxProp target states by current state+command
/////////////////////////////////////////////////////////////////////
static const int auxprop_state_command_target_state[E_AUXPROP_STATE_N][E_AUXPROP_COMMAND_N] = {
    [AUXPROP_DISABLED_STATE][AUXPROP_ENABLE] = AUXPROP_ENABLED_STATE,
    [AUXPROP_DISABLED_STATE][AUXPROP_MANUAL] = AUXPROP_MANUAL_STATE,
    [AUXPROP_ENABLED_STATE][AUXPROP_DISABLE] = AUXPROP_DISABLED_STATE,
    [AUXPROP_ENABLED_STATE][AUXPROP_MANUAL] = AUXPROP_MANUAL_STATE,
    [AUXPROP_MANUAL_STATE][AUXPROP_DISABLE] = AUXPROP_DISABLED_STATE,
    [AUXPROP_MANUAL_STATE][AUXPROP_MANUAL] = AUXPROP_ENABLED_STATE
};

static inline const E_AUXPROP_STATE_T get_auxprop_target_state(const E_AUXPROP_STATE_T current_state, const E_AUXPROP_COMMAND_T command)
{
    return auxprop_state_command_target_state[current_state][command];
}


#endif // _AUXPROP__TYPES_H_
