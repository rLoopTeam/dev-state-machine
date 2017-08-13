#ifndef _POD__TYPES_H_
#define _POD__TYPES_H_

#include "../COMPAT.h"
#include "../state_machine.h"
#include "../timers.h"
#include "brakes/brakes__types.h"
#include "cooling/cooling__types.h"
#include "auxprop/auxprop__types.h"
#include "engines/engines__types.h"


/////////////////////////////////////////////////////////////////////
//  Pod States
/////////////////////////////////////////////////////////////////////
typedef enum 
{
    POD_NULL_STATE = 0,
    IDLE_STATE,
    TEST_MODE_STATE,
    DRIVE_STATE,
    ARMED_WAIT_STATE,
    FLIGHT_PREP_STATE,
    READY_STATE,
    ACCEL_STATE,
    COAST_INTERLOCK_STATE,
    BRAKE_STATE,
    SPINDOWN_STATE
} E_POD_STATE_T;
#define E_POD_STATE_N 11

// Pod state lookup
static char *pod_state_lookup[] =
{
    "POD_NULL_STATE",
    "IDLE_STATE",
    "TEST_MODE_STATE",
    "DRIVE_STATE",
    "ARMED_WAIT_STATE",
    "FLIGHT_PREP_STATE",
    "READY_STATE",
    "ACCEL_STATE",
    "COAST_INTERLOCK_STATE",
    "BRAKE_STATE",
    "SPINDOWN_STATE"
};

// Pod state lookup function
static inline const char * lookup_pod_state(const E_POD_STATE_T state)
{
    return pod_state_lookup[state];
}


/////////////////////////////////////////////////////////////////////
//  Pod Commands
/////////////////////////////////////////////////////////////////////
typedef enum 
{
    POD_NO_CMD = 0,
    IDLE,
    TEST_MODE,
    DRIVE,
    DRIVE_STOP,
    FLIGHT_PREP,
    ARMED_WAIT,
    READY,
    FLASH_LIGHTS,
    TEST_CMD_DRIVE

} E_POD_COMMAND_T;
#define E_POD_COMMAND_N 10

// Pod command lookup
static char *pod_command_lookup[] = 
{
    "POD_NO_CMD",
    "IDLE",
    "TEST_MODE",
    "DRIVE",
    "DRIVE_STOP",
    "FLIGHT_PREP",
    "ARMED_WAIT",
    "READY",
    "FLASH_LIGHTS",
    "TEST_CMD_DRIVE"
};

// Pod command lookup function
static inline const char * lookup_pod_command(const E_POD_COMMAND_T command)
{
    return pod_command_lookup[command];
}


/////////////////////////////////////////////////////////////////////
//  Pod command struct
/////////////////////////////////////////////////////////////////////
typedef struct 
{
    // Command
    E_POD_COMMAND_T command;

    // @todo: handle indices -- e.g. brakes[0]

    struct {
                    
        
    
    } args;

} strPodCmd;


/////////////////////////////////////////////////////////////////////
//  Pod struct to be used in sFCU
/////////////////////////////////////////////////////////////////////
typedef struct 
{
    // Internal command (first priority)
    strPodCmd internal_command;

    // External command (second priority)
    strPodCmd external_command;

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

    /**
     *  Brakes
     */
    strBrakes sBrakes;
    
    
    /**
     *  Cooling
     */
    strCooling sCooling;
    
    
    /**
     *  AuxProp
     */
    strAuxProp sAuxProp;
    
    
    /**
     *  Engines
     */
    strEngines sEngines;


    // Timers and timeouts
    // Ready state to Idle backup timeout
    strTimer ReadyExpiredBackupTimeout;
    
    // Accel to Coast Interlock backup timeout
    strTimer AccelBackupTimeout;
    
    // Coast interlock timeout
    strTimer CoastInterlockTimeout;
    
    // Brake to Spindown backup timeout
    strTimer BrakeToSpindownBackupTimeout;
    
    // Spindown to Idle backup timeout
    strTimer SpindownToIdleBackupTimeout;

} strPod;


/////////////////////////////////////////////////////////////////////
//  Pod Allowable commands per state
/////////////////////////////////////////////////////////////////////
static const int pod_allowed_state_commands[E_POD_STATE_N][E_POD_COMMAND_N] = 
{
    [IDLE_STATE][TEST_MODE] = 1,
    [IDLE_STATE][ARMED_WAIT] = 1,
    [IDLE_STATE][DRIVE] = 1,
    [IDLE_STATE][FLASH_LIGHTS] = 1,
    [IDLE_STATE][IDLE] = 1,
    [TEST_MODE_STATE][IDLE] = 1,
    [TEST_MODE_STATE][FLASH_LIGHTS] = 1,
    [TEST_MODE_STATE][TEST_MODE] = 1,
    [DRIVE_STATE][IDLE] = 1,
    [DRIVE_STATE][FLASH_LIGHTS] = 1,
    [DRIVE_STATE][DRIVE] = 1,
    [ARMED_WAIT_STATE][IDLE] = 1,
    [ARMED_WAIT_STATE][FLIGHT_PREP] = 1,
    [ARMED_WAIT_STATE][FLASH_LIGHTS] = 1,
    [ARMED_WAIT_STATE][ARMED_WAIT] = 1,
    [FLIGHT_PREP_STATE][ARMED_WAIT] = 1,
    [FLIGHT_PREP_STATE][READY] = 1,
    [FLIGHT_PREP_STATE][FLASH_LIGHTS] = 1,
    [FLIGHT_PREP_STATE][FLIGHT_PREP] = 1,
    [READY_STATE][FLASH_LIGHTS] = 1,
    [READY_STATE][READY] = 1
};

static inline const bool pod_state_allows_command(const E_POD_STATE_T state, const E_POD_COMMAND_T command)
{
    return pod_allowed_state_commands[state][command];
}


/////////////////////////////////////////////////////////////////////
//  Pod target states by current state+command
/////////////////////////////////////////////////////////////////////
static const int pod_state_command_target_state[E_POD_STATE_N][E_POD_COMMAND_N] = {
    [IDLE_STATE][TEST_MODE] = TEST_MODE_STATE,
    [IDLE_STATE][ARMED_WAIT] = ARMED_WAIT_STATE,
    [IDLE_STATE][DRIVE] = DRIVE_STATE,
    [TEST_MODE_STATE][IDLE] = IDLE_STATE,
    [DRIVE_STATE][IDLE] = IDLE_STATE,
    [ARMED_WAIT_STATE][IDLE] = IDLE_STATE,
    [ARMED_WAIT_STATE][FLIGHT_PREP] = FLIGHT_PREP_STATE,
    [FLIGHT_PREP_STATE][ARMED_WAIT] = ARMED_WAIT_STATE,
    [FLIGHT_PREP_STATE][READY] = READY_STATE
};

static inline const E_POD_STATE_T get_pod_target_state(const E_POD_STATE_T current_state, const E_POD_COMMAND_T command)
{
    return pod_state_command_target_state[current_state][command];
}


#endif // _POD__TYPES_H_
