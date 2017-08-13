#include "pod.h"
#include "../fcu_core.h"

// Subsystems
#include "brakes/brakes.h"
#include "cooling/cooling.h"
#include "auxprop/auxprop.h"
#include "engines/engines.h"


void vPod__Init(strPod *sPod)
{
    sPod->sm.state = IDLE_STATE;
        

    // Init Brakes subsystem
    sPod->sBrakes.index = 0;
    
    #if DEBUG == 1U
    // Set names for debug printing
    sprintf(sPod->sBrakes.name, "sBrakes");
    sprintf(sPod->sBrakes.absname, "%s.%s", sPod->absname, sPod->sBrakes.name);
    #endif
    
    vBrakes__Init(&sPod->sBrakes);
    
    // Init Cooling subsystem
    sPod->sCooling.index = 0;
    
    #if DEBUG == 1U
    // Set names for debug printing
    sprintf(sPod->sCooling.name, "sCooling");
    sprintf(sPod->sCooling.absname, "%s.%s", sPod->absname, sPod->sCooling.name);
    #endif
    
    vCooling__Init(&sPod->sCooling);
    
    // Init AuxProp subsystem
    sPod->sAuxProp.index = 0;
    
    #if DEBUG == 1U
    // Set names for debug printing
    sprintf(sPod->sAuxProp.name, "sAuxProp");
    sprintf(sPod->sAuxProp.absname, "%s.%s", sPod->absname, sPod->sAuxProp.name);
    #endif
    
    vAuxProp__Init(&sPod->sAuxProp);
    
    // Init Engines subsystem
    sPod->sEngines.index = 0;
    
    #if DEBUG == 1U
    // Set names for debug printing
    sprintf(sPod->sEngines.name, "sEngines");
    sprintf(sPod->sEngines.absname, "%s.%s", sPod->absname, sPod->sEngines.name);
    #endif
    
    vEngines__Init(&sPod->sEngines);

}


void vPod__Process(strPod *sPod)
{
        
    // Step the state machine to pick up on state changes etc.
    sm_step(&sPod->sm);
        
    // Process pod state machine
    switch (sPod->sm.state)
    {
        case IDLE_STATE:
        
            if (sm_entering(&sPod->sm, IDLE_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering IDLE_STATE\n", sPod->absname);
                #endif
                internal_cmd_BRAKES_DISABLE(&sPod->sBrakes);
                internal_cmd_COOLING_DISABLE(&sPod->sCooling);
                internal_cmd_AUXPROP_DISABLE(&sPod->sAuxProp);
            }
            
            // Handle commands and conditional transitions
            handle_pod_transitions(sPod);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sPod->sm, IDLE_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting IDLE_STATE\n", sPod->absname);
                #endif
        
            }
            
            break;
        
        case TEST_MODE_STATE:
        
            if (sm_entering(&sPod->sm, TEST_MODE_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering TEST_MODE_STATE\n", sPod->absname);
                #endif
                internal_cmd_BRAKES_ENABLE(&sPod->sBrakes);
                cmd_COOLING_MANUAL(&sPod->sCooling);
                internal_cmd_AUXPROP_MANUAL(&sPod->sAuxProp);
            }
            
            // Handle commands and conditional transitions
            handle_pod_transitions(sPod);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sPod->sm, TEST_MODE_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting TEST_MODE_STATE\n", sPod->absname);
                #endif
        
            }
            
            break;
        
        case DRIVE_STATE:
        
            if (sm_entering(&sPod->sm, DRIVE_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering DRIVE_STATE\n", sPod->absname);
                #endif
                cmd_BRAKES_HOLD(&sPod->sBrakes);
                cmd_COOLING_MANUAL(&sPod->sCooling);
                internal_cmd_AUXPROP_ENABLE(&sPod->sAuxProp);
            }
            
            // Handle commands and conditional transitions
            handle_pod_transitions(sPod);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sPod->sm, DRIVE_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting DRIVE_STATE\n", sPod->absname);
                #endif
        
            }
            
            break;
        
        case ARMED_WAIT_STATE:
        
            if (sm_entering(&sPod->sm, ARMED_WAIT_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering ARMED_WAIT_STATE\n", sPod->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_pod_transitions(sPod);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sPod->sm, ARMED_WAIT_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting ARMED_WAIT_STATE\n", sPod->absname);
                #endif
        
            }
            
            break;
        
        case FLIGHT_PREP_STATE:
        
            if (sm_entering(&sPod->sm, FLIGHT_PREP_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering FLIGHT_PREP_STATE\n", sPod->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_pod_transitions(sPod);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sPod->sm, FLIGHT_PREP_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting FLIGHT_PREP_STATE\n", sPod->absname);
                #endif
        
            }
            
            break;
        
        case READY_STATE:
        
            if (sm_entering(&sPod->sm, READY_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering READY_STATE\n", sPod->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_pod_transitions(sPod);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sPod->sm, READY_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting READY_STATE\n", sPod->absname);
                #endif
        
            }
            
            break;
        
        case ACCEL_STATE:
        
            if (sm_entering(&sPod->sm, ACCEL_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering ACCEL_STATE\n", sPod->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_pod_transitions(sPod);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sPod->sm, ACCEL_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting ACCEL_STATE\n", sPod->absname);
                #endif
        
            }
            
            break;
        
        case COAST_INTERLOCK_STATE:
        
            if (sm_entering(&sPod->sm, COAST_INTERLOCK_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering COAST_INTERLOCK_STATE\n", sPod->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_pod_transitions(sPod);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sPod->sm, COAST_INTERLOCK_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting COAST_INTERLOCK_STATE\n", sPod->absname);
                #endif
        
            }
            
            break;
        
        case BRAKE_STATE:
        
            if (sm_entering(&sPod->sm, BRAKE_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering BRAKE_STATE\n", sPod->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_pod_transitions(sPod);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sPod->sm, BRAKE_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting BRAKE_STATE\n", sPod->absname);
                #endif
        
            }
            
            break;
        
        case SPINDOWN_STATE:
        
            if (sm_entering(&sPod->sm, SPINDOWN_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering SPINDOWN_STATE\n", sPod->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_pod_transitions(sPod);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sPod->sm, SPINDOWN_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting SPINDOWN_STATE\n", sPod->absname);
                #endif
        
            }
            
            break;

    }
    
    /////////////////////////////////////////////////////////////////
    //  Process Subsystems
    /////////////////////////////////////////////////////////////////
    
    // Process Brakes subsystem
    vBrakes__Process(&sPod->sBrakes);
    
    // Process Cooling subsystem
    vCooling__Process(&sPod->sCooling);
    
    // Process AuxProp subsystem
    vAuxProp__Process(&sPod->sAuxProp);
    
    // Process Engines subsystem
    vEngines__Process(&sPod->sEngines);

}


void vPod__10MS_ISR(strPod *sPod) 
{
    // Coast interlock timeout
    timeout_update(&sPod->CoastInterlockTimeout, 10);
    // Brakes 10ms ISR
    vBrakes__10MS_ISR(&sPod->sBrakes);
    
    
    // Cooling 10ms ISR
    vCooling__10MS_ISR(&sPod->sCooling);
    
    
    // AuxProp 10ms ISR
    vAuxProp__10MS_ISR(&sPod->sAuxProp);
    
    
    // Engines 10ms ISR
    vEngines__10MS_ISR(&sPod->sEngines);
    

}

void vPod__100MS_ISR(strPod *sPod)
{
    // Ready state to Idle backup timeout
    timeout_update(&sPod->ReadyExpiredBackupTimeout, 100);
    
    // Accel to Coast Interlock backup timeout
    timeout_update(&sPod->AccelBackupTimeout, 100);
    
    // Brake to Spindown backup timeout
    timeout_update(&sPod->BrakeToSpindownBackupTimeout, 100);
    
    // Spindown to Idle backup timeout
    timeout_update(&sPod->SpindownToIdleBackupTimeout, 100);
    // Brakes 100ms ISR
    vBrakes__100MS_ISR(&sPod->sBrakes);
    
    
    // Cooling 100ms ISR
    vCooling__100MS_ISR(&sPod->sCooling);
    
    
    // AuxProp 100ms ISR
    vAuxProp__100MS_ISR(&sPod->sAuxProp);
    
    
    // Engines 100ms ISR
    vEngines__100MS_ISR(&sPod->sEngines);
    

}


// NOTE: Use this in your process() method
// Return: whether or not we've changed states during the transition
void handle_pod_transitions(strPod *sPod)
{
    #if DEBUG == 1U
        //printf("Handling transitions in handle_pod_transitions()\n");
    #endif
    
    bool command_executed;

    // Handle internal commands first
    // Note: we're passing in the internal command directly, but we could be passing in any strPodCmd.
    command_executed = handle_pod_command(sPod, &sPod->internal_command, &sPod->internal_command);

    if ( ! command_executed )
    {
        // Handle external commands if no internal command was executed
        // Note: we're passing in the external command directly, but we could be passing in any strPodCmd.
        command_executed = handle_pod_command(sPod, &sPod->external_command, &sPod->external_command);
    }
    
    // If we didn't execute a command, run our conditional transitions
    if ( ! command_executed )
    {
        // Run conditional transitions
        handle_pod_conditional_transition(sPod);
    }
    else
    {
        // continue
    }
    
    // If we haven't changed states so far (i.e. nothing has caused a transition), try our timeouts
    if ( ! sm_transitioning(&sPod->sm))
    {
        handle_pod_timeout_transition(sPod);
    }
    else
    {
        // continue
    }

    // If we haven't changed states so far (i.e. nothing has caused a transition), try our automatic transitions
    if ( ! sm_transitioning(&sPod->sm))
    {
        handle_pod_automatic_transition(sPod);
    }
    else
    {
        // Nothing more to do
    }

}


