#include "pod__control.h"
#include "pod__types.h"

/////////////////////////////////////////////////////////////////////
//  Pod transition and command guard functions
/////////////////////////////////////////////////////////////////////

bool armed_wait_checks_ok(strPod *sPod)
{
    // @todo: implement
    return FALSE;
}

bool drive_checks_ok(strPod *sPod)
{
    // @todo: implement
    return FALSE;
}

bool flight_prep_checks_ok(strPod *sPod)
{
    // @todo: implement
    return FALSE;
}

bool flight_readiness_checks_ok(strPod *sPod)
{
    // @todo: implement
    return FALSE;
}

bool accel_confirmed(strPod *sPod)
{
    // @todo: implement
    return FALSE;
}

bool pusher_separation_confirmed(strPod *sPod)
{
    // @todo: implement
    return FALSE;
}

bool pod_stop_confirmed(strPod *sPod)
{
    // @todo: implement
    return FALSE;
}

bool spindown_complete_confirmed(strPod *sPod)
{
    // @todo: implement
    return FALSE;
}


/////////////////////////////////////////////////////////////////////
//  Pod command and transition handling
/////////////////////////////////////////////////////////////////////


// Handle conditional transitions
// Return whether or not we're transitioning
bool handle_pod_conditional_transition(strPod *sPod)
{
    StateMachine *sm = &sPod->sm;

    bool transitioning;

    switch(sm->state) {  // Current state
        case READY_STATE:
            if ( accel_confirmed(sPod) ) 
            {
                sm->state = ACCEL_STATE;
                transitioning = TRUE;
            } else {
                transitioning = FALSE;
            }
            break;
        
        case ACCEL_STATE:
            if ( pusher_separation_confirmed(sPod) ) 
            {
                sm->state = COAST_INTERLOCK_STATE;
                transitioning = TRUE;
            } else {
                transitioning = FALSE;
            }
            break;
        
        case BRAKE_STATE:
            if ( pod_stop_confirmed(sPod) ) 
            {
                sm->state = SPINDOWN_STATE;
                transitioning = TRUE;
            } else {
                transitioning = FALSE;
            }
            break;
        
        case SPINDOWN_STATE:
            if ( spindown_complete_confirmed(sPod) ) 
            {
                sm->state = IDLE_STATE;
                transitioning = TRUE;
            } else {
                transitioning = FALSE;
            }
            break;

        default:
            // Do nothing
            break;

    }
    
    return transitioning;
}


// Handle timeout transitions
// Return whether or not we're transitioning
bool handle_pod_timeout_transition(strPod *sPod)
{
    StateMachine *sm = &sPod->sm;
    
    bool transitioning;

    switch(sm->state) {  // Current state
        case READY_STATE:
            if ( timeout_expired(&sPod->ReadyExpiredBackupTimeout) ) 
            {
                sm->state = IDLE_STATE;
                transitioning = TRUE;
            } else {
                transitioning = FALSE;
            }
            break;
        
        case ACCEL_STATE:
            if ( timeout_expired(&sPod->AccelBackupTimeout) ) 
            {
                sm->state = COAST_INTERLOCK_STATE;
                transitioning = TRUE;
            } else {
                transitioning = FALSE;
            }
            break;
        
        case COAST_INTERLOCK_STATE:
            if ( timeout_expired(&sPod->CoastInterlockTimeout) ) 
            {
                sm->state = BRAKE_STATE;
                transitioning = TRUE;
            } else {
                transitioning = FALSE;
            }
            break;
        
        case BRAKE_STATE:
            if ( timeout_expired(&sPod->BrakeToSpindownBackupTimeout) ) 
            {
                sm->state = SPINDOWN_STATE;
                transitioning = TRUE;
            } else {
                transitioning = FALSE;
            }
            break;
        
        case SPINDOWN_STATE:
            if ( timeout_expired(&sPod->SpindownToIdleBackupTimeout) ) 
            {
                sm->state = IDLE_STATE;
                transitioning = TRUE;
            } else {
                transitioning = FALSE;
            }
            break;

        default:
            // No timeouts were tripped, so we're not transitioning
            transitioning = FALSE;
            break;

    }
    
    return transitioning;
}


// Handle automatic transitions
// Return whether or not we're transitioning
bool handle_pod_automatic_transition(strPod *sPod)
{
    // No automatic transitions to handle
    return FALSE;
} 


/////////////////////////////////////////////////////////////////////
//  Pod command handling
/////////////////////////////////////////////////////////////////////

// Handle command
// Return whether or not a command was handled
bool handle_pod_command(strPod *sPod, const strPodCmd *cmd, strPodCmd *command_slot)
{

/////////////////////////////////////////////////////////////////////
//  Order of operations:
//  1. Check to see if the command is allowed in our current state
//  2. Check any guards that may prevent a command from executing. 
//     Note: some state/command combinations have guards, some do not.
//  3. If the command has passed all of our checks, perform a state
//     change if there's one associated with the command/state combo,
//     and update any variables etc. based on the command arguments.
/////////////////////////////////////////////////////////////////////    

    #if DEBUG == 1U
        // printf("Handling command in handle_pod_command()\n");
    #endif

    // Return quickly if no command
    if (cmd->command == POD_NO_CMD)
    {
        return FALSE;
    } 
    else 
    {
        // fall on
    }    

    E_POD_STATE_T state = sPod->sm.state;
    E_POD_COMMAND_T command = cmd->command;

    bool exec_command = TRUE;

    //  1. Check to see if the command is allowed in our current state
    if (pod_state_allows_command(state, command))
    {

        //  2. Check any guards that may prevent a command from executing.        
        if (state == IDLE_STATE && command == ARMED_WAIT)
        {
            if ( armed_wait_checks_ok(sPod) )
            {
                exec_command = TRUE;
            } 
            else 
            {
                #if DEBUG == 1U
                printf("%s -- REJECTING COMMAND %s in state %s: failed armed_wait_checks_ok() check", sPod->absname, lookup_pod_command(ARMED_WAIT), lookup_pod_state(IDLE_STATE));
                #endif
                exec_command = FALSE;
            }
        }
        else if (state == IDLE_STATE && command == DRIVE)
        {
            if ( drive_checks_ok(sPod) )
            {
                exec_command = TRUE;
            } 
            else 
            {
                #if DEBUG == 1U
                printf("%s -- REJECTING COMMAND %s in state %s: failed drive_checks_ok() check", sPod->absname, lookup_pod_command(DRIVE), lookup_pod_state(IDLE_STATE));
                #endif
                exec_command = FALSE;
            }
        }
        else if (state == ARMED_WAIT_STATE && command == FLIGHT_PREP)
        {
            if ( flight_prep_checks_ok(sPod) )
            {
                exec_command = TRUE;
            } 
            else 
            {
                #if DEBUG == 1U
                printf("%s -- REJECTING COMMAND %s in state %s: failed flight_prep_checks_ok() check", sPod->absname, lookup_pod_command(FLIGHT_PREP), lookup_pod_state(ARMED_WAIT_STATE));
                #endif
                exec_command = FALSE;
            }
        }
        else if (state == FLIGHT_PREP_STATE && command == READY)
        {
            if ( flight_readiness_checks_ok(sPod) )
            {
                exec_command = TRUE;
            } 
            else 
            {
                #if DEBUG == 1U
                printf("%s -- REJECTING COMMAND %s in state %s: failed flight_readiness_checks_ok() check", sPod->absname, lookup_pod_command(READY), lookup_pod_state(FLIGHT_PREP_STATE));
                #endif
                exec_command = FALSE;
            }
        }
                
    } 
    else 
    {
        #if DEBUG == 1U
        printf("%s -- REJECTING COMMAND: Command %s not allowed in state %s\n", sPod->absname, lookup_pod_command(command), lookup_pod_state(state));
        #endif
        
        // Command not allowed in this state
        exec_command = FALSE;
    }
    
    
    //  3. If we've passed all of our checks, handle state changes and command args

    if (exec_command) 
    {
        /////////////////////////////////////////////////////////////////////
        //  Handle state transition if one is associated with the 
        //  state/command combination
        /////////////////////////////////////////////////////////////////////
        E_POD_STATE_T target_state = get_pod_target_state(state, command);
        if ( target_state != POD_NULL_STATE )
        {
            sPod->sm.state = target_state;
        }
        
        #if DEBUG == 1U
            printf("%s -- COMMITTING COMMAND %s in state %s\n", sPod->absname, lookup_pod_command(command), lookup_pod_state(state));
        #endif

        // Commit the command (update variables based on command args)
        commit_pod_command(sPod, cmd, command_slot);
    
    } 
    else 
    {
        // Reject the command
        reject_pod_command(sPod, cmd, "handle_pod_command(): exec_command is false", command_slot);

    }

    // Note: The fact that we've executed a command does not necessarily mean we've transitioned
    return exec_command;

}


void commit_pod_command(strPod *sPod, const strPodCmd *cmd, strPodCmd *command_slot)
{
    // Update variables as needed based on command arguments
    
    // Note: Only commands with arguments need to be handled here    

    // Clear the command now that we've handled it
    clear_pod_command(sPod, command_slot);
}


void reject_pod_command(strPod *sPod, const strPodCmd *cmd, const char *reject_message, strPodCmd *command_slot)
{
    // Don't know if we need to do anything here, but maybe send a message? 
    // ...
    
    clear_pod_command(sPod, command_slot);
}


void clear_pod_command(strPod *sPod, strPodCmd *command_slot)
{
    // Clear the pod command
    command_slot->command = POD_NO_CMD; // No command
}


/////////////////////////////////////////////////////////////////////
//  Pod command functions
/////////////////////////////////////////////////////////////////////

void cmd_IDLE(strPod *sPod)
{
    #if DEBUG == 1U
        printf("cmd_IDLE() called\n");
    #endif
    
    strPodCmd * cmd = &sPod->external_command;
    cmd->command = IDLE;

}

void cmd_TEST_MODE(strPod *sPod)
{
    #if DEBUG == 1U
        printf("cmd_TEST_MODE() called\n");
    #endif
    
    strPodCmd * cmd = &sPod->external_command;
    cmd->command = TEST_MODE;

}

void cmd_DRIVE(strPod *sPod)
{
    #if DEBUG == 1U
        printf("cmd_DRIVE() called\n");
    #endif
    
    strPodCmd * cmd = &sPod->external_command;
    cmd->command = DRIVE;

}

void cmd_DRIVE_STOP(strPod *sPod)
{
    #if DEBUG == 1U
        printf("cmd_DRIVE_STOP() called\n");
    #endif
    
    strPodCmd * cmd = &sPod->external_command;
    cmd->command = DRIVE_STOP;

}

void cmd_FLIGHT_PREP(strPod *sPod)
{
    #if DEBUG == 1U
        printf("cmd_FLIGHT_PREP() called\n");
    #endif
    
    strPodCmd * cmd = &sPod->external_command;
    cmd->command = FLIGHT_PREP;

}

void cmd_ARMED_WAIT(strPod *sPod)
{
    #if DEBUG == 1U
        printf("cmd_ARMED_WAIT() called\n");
    #endif
    
    strPodCmd * cmd = &sPod->external_command;
    cmd->command = ARMED_WAIT;

}

void cmd_READY(strPod *sPod)
{
    #if DEBUG == 1U
        printf("cmd_READY() called\n");
    #endif
    
    strPodCmd * cmd = &sPod->external_command;
    cmd->command = READY;

}

void cmd_FLASH_LIGHTS(strPod *sPod)
{
    #if DEBUG == 1U
        printf("cmd_FLASH_LIGHTS() called\n");
    #endif
    
    strPodCmd * cmd = &sPod->external_command;
    cmd->command = FLASH_LIGHTS;

}

void cmd_TEST_CMD_DRIVE(strPod *sPod)
{
    #if DEBUG == 1U
        printf("cmd_TEST_CMD_DRIVE() called\n");
    #endif
    
    strPodCmd * cmd = &sPod->external_command;
    cmd->command = TEST_CMD_DRIVE;

}

