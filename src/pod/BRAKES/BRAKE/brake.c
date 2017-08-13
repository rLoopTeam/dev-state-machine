#include "brake.h"
#include "../../../fcu_core.h"


void vBrake__Init(strBrake *sBrake)
{
    sBrake->sm.state = SINGLE_BRAKE_HOLD_STATE;
        
}


void vBrake__Process(strBrake *sBrake)
{
        
    // Step the state machine to pick up on state changes etc.
    sm_step(&sBrake->sm);
        
    // Process brake state machine
    switch (sBrake->sm.state)
    {
        case SINGLE_BRAKE_HOLD_STATE:
        
            if (sm_entering(&sBrake->sm, SINGLE_BRAKE_HOLD_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering SINGLE_BRAKE_HOLD_STATE\n", sBrake->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_brake_transitions(sBrake);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sBrake->sm, SINGLE_BRAKE_HOLD_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting SINGLE_BRAKE_HOLD_STATE\n", sBrake->absname);
                #endif
        
            }
            
            break;
        
        case SINGLE_BRAKE_DEPLOY_STATE:
        
            if (sm_entering(&sBrake->sm, SINGLE_BRAKE_DEPLOY_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering SINGLE_BRAKE_DEPLOY_STATE\n", sBrake->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_brake_transitions(sBrake);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sBrake->sm, SINGLE_BRAKE_DEPLOY_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting SINGLE_BRAKE_DEPLOY_STATE\n", sBrake->absname);
                #endif
        
            }
            
            break;
        
        case SINGLE_BRAKE_RETRACT_STATE:
        
            if (sm_entering(&sBrake->sm, SINGLE_BRAKE_RETRACT_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering SINGLE_BRAKE_RETRACT_STATE\n", sBrake->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_brake_transitions(sBrake);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sBrake->sm, SINGLE_BRAKE_RETRACT_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting SINGLE_BRAKE_RETRACT_STATE\n", sBrake->absname);
                #endif
        
            }
            
            break;
        
        case SINGLE_BRAKE_SEEK_STATE:
        
            if (sm_entering(&sBrake->sm, SINGLE_BRAKE_SEEK_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering SINGLE_BRAKE_SEEK_STATE\n", sBrake->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_brake_transitions(sBrake);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sBrake->sm, SINGLE_BRAKE_SEEK_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting SINGLE_BRAKE_SEEK_STATE\n", sBrake->absname);
                #endif
        
            }
            
            break;
        
        case SINGLE_BRAKE_INTERLOCK_STATE:
        
            if (sm_entering(&sBrake->sm, SINGLE_BRAKE_INTERLOCK_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering SINGLE_BRAKE_INTERLOCK_STATE\n", sBrake->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_brake_transitions(sBrake);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sBrake->sm, SINGLE_BRAKE_INTERLOCK_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting SINGLE_BRAKE_INTERLOCK_STATE\n", sBrake->absname);
                #endif
        
            }
            
            break;

    }
    
}


void vBrake__10MS_ISR(strBrake *sBrake) 
{
    
}

void vBrake__100MS_ISR(strBrake *sBrake)
{
    
}


// NOTE: Use this in your process() method
// Return: whether or not we've changed states during the transition
void handle_brake_transitions(strBrake *sBrake)
{
    #if DEBUG == 1U
        //printf("Handling transitions in handle_brake_transitions()\n");
    #endif
    
    bool command_executed;

    // Handle internal commands first
    // Note: we're passing in the internal command directly, but we could be passing in any strBrakeCmd.
    command_executed = handle_brake_command(sBrake, &sBrake->internal_command, &sBrake->internal_command);

    if ( ! command_executed )
    {
        // Handle external commands if no internal command was executed
        // Note: we're passing in the external command directly, but we could be passing in any strBrakeCmd.
        command_executed = handle_brake_command(sBrake, &sBrake->external_command, &sBrake->external_command);
    }
    
    // If we didn't execute a command, run our conditional transitions
    if ( ! command_executed )
    {
        // Run conditional transitions
        handle_brake_conditional_transition(sBrake);
    }
    else
    {
        // continue
    }
    
    // If we haven't changed states so far (i.e. nothing has caused a transition), try our timeouts
    if ( ! sm_transitioning(&sBrake->sm))
    {
        handle_brake_timeout_transition(sBrake);
    }
    else
    {
        // continue
    }

    // If we haven't changed states so far (i.e. nothing has caused a transition), try our automatic transitions
    if ( ! sm_transitioning(&sBrake->sm))
    {
        handle_brake_automatic_transition(sBrake);
    }
    else
    {
        // Nothing more to do
    }

}


