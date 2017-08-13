#include "auxprop.h"
#include "../../fcu_core.h"


void vAuxProp__Init(strAuxProp *sAuxProp)
{
    sAuxProp->sm.state = AUXPROP_DISABLED_STATE;
        
}


void vAuxProp__Process(strAuxProp *sAuxProp)
{
        
    // Step the state machine to pick up on state changes etc.
    sm_step(&sAuxProp->sm);
        
    // Process auxprop state machine
    switch (sAuxProp->sm.state)
    {
        case AUXPROP_DISABLED_STATE:
        
            if (sm_entering(&sAuxProp->sm, AUXPROP_DISABLED_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering AUXPROP_DISABLED_STATE\n", sAuxProp->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_auxprop_transitions(sAuxProp);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sAuxProp->sm, AUXPROP_DISABLED_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting AUXPROP_DISABLED_STATE\n", sAuxProp->absname);
                #endif
        
            }
            
            break;
        
        case AUXPROP_ENABLED_STATE:
        
            if (sm_entering(&sAuxProp->sm, AUXPROP_ENABLED_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering AUXPROP_ENABLED_STATE\n", sAuxProp->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_auxprop_transitions(sAuxProp);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sAuxProp->sm, AUXPROP_ENABLED_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting AUXPROP_ENABLED_STATE\n", sAuxProp->absname);
                #endif
        
            }
            
            break;
        
        case AUXPROP_MANUAL_STATE:
        
            if (sm_entering(&sAuxProp->sm, AUXPROP_MANUAL_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering AUXPROP_MANUAL_STATE\n", sAuxProp->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_auxprop_transitions(sAuxProp);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sAuxProp->sm, AUXPROP_MANUAL_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting AUXPROP_MANUAL_STATE\n", sAuxProp->absname);
                #endif
        
            }
            
            break;

    }
    
}


void vAuxProp__10MS_ISR(strAuxProp *sAuxProp) 
{
    
}

void vAuxProp__100MS_ISR(strAuxProp *sAuxProp)
{
    
}


// NOTE: Use this in your process() method
// Return: whether or not we've changed states during the transition
void handle_auxprop_transitions(strAuxProp *sAuxProp)
{
    #if DEBUG == 1U
        //printf("Handling transitions in handle_auxprop_transitions()\n");
    #endif
    
    bool command_executed;

    // Handle internal commands first
    // Note: we're passing in the internal command directly, but we could be passing in any strAuxPropCmd.
    command_executed = handle_auxprop_command(sAuxProp, &sAuxProp->internal_command, &sAuxProp->internal_command);

    if ( ! command_executed )
    {
        // Handle external commands if no internal command was executed
        // Note: we're passing in the external command directly, but we could be passing in any strAuxPropCmd.
        command_executed = handle_auxprop_command(sAuxProp, &sAuxProp->external_command, &sAuxProp->external_command);
    }
    
    // If we didn't execute a command, run our conditional transitions
    if ( ! command_executed )
    {
        // Run conditional transitions
        handle_auxprop_conditional_transition(sAuxProp);
    }
    else
    {
        // continue
    }
    
    // If we haven't changed states so far (i.e. nothing has caused a transition), try our timeouts
    if ( ! sm_transitioning(&sAuxProp->sm))
    {
        handle_auxprop_timeout_transition(sAuxProp);
    }
    else
    {
        // continue
    }

    // If we haven't changed states so far (i.e. nothing has caused a transition), try our automatic transitions
    if ( ! sm_transitioning(&sAuxProp->sm))
    {
        handle_auxprop_automatic_transition(sAuxProp);
    }
    else
    {
        // Nothing more to do
    }

}


