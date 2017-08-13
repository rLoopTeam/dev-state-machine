#include "cooling.h"
#include "../../fcu_core.h"


void vCooling__Init(strCooling *sCooling)
{
    sCooling->sm.state = COOLING_DISABLED_STATE;
        
}


void vCooling__Process(strCooling *sCooling)
{
        
    // Step the state machine to pick up on state changes etc.
    sm_step(&sCooling->sm);
        
    // Process cooling state machine
    switch (sCooling->sm.state)
    {
        case COOLING_DISABLED_STATE:
        
            if (sm_entering(&sCooling->sm, COOLING_DISABLED_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering COOLING_DISABLED_STATE\n", sCooling->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_cooling_transitions(sCooling);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sCooling->sm, COOLING_DISABLED_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting COOLING_DISABLED_STATE\n", sCooling->absname);
                #endif
        
            }
            
            break;
        
        case COOLING_AUTO_STATE:
        
            if (sm_entering(&sCooling->sm, COOLING_AUTO_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering COOLING_AUTO_STATE\n", sCooling->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_cooling_transitions(sCooling);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sCooling->sm, COOLING_AUTO_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting COOLING_AUTO_STATE\n", sCooling->absname);
                #endif
        
            }
            
            break;
        
        case COOLING_PURGE_STATE:
        
            if (sm_entering(&sCooling->sm, COOLING_PURGE_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering COOLING_PURGE_STATE\n", sCooling->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_cooling_transitions(sCooling);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sCooling->sm, COOLING_PURGE_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting COOLING_PURGE_STATE\n", sCooling->absname);
                #endif
        
            }
            
            break;
        
        case COOLING_MANUAL_STATE:
        
            if (sm_entering(&sCooling->sm, COOLING_MANUAL_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering COOLING_MANUAL_STATE\n", sCooling->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_cooling_transitions(sCooling);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sCooling->sm, COOLING_MANUAL_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting COOLING_MANUAL_STATE\n", sCooling->absname);
                #endif
        
            }
            
            break;
        
        case COOLING_INTERLOCK_STATE:
        
            if (sm_entering(&sCooling->sm, COOLING_INTERLOCK_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering COOLING_INTERLOCK_STATE\n", sCooling->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_cooling_transitions(sCooling);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sCooling->sm, COOLING_INTERLOCK_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting COOLING_INTERLOCK_STATE\n", sCooling->absname);
                #endif
        
            }
            
            break;

    }
    
}


void vCooling__10MS_ISR(strCooling *sCooling) 
{
    
}

void vCooling__100MS_ISR(strCooling *sCooling)
{
    
}


// NOTE: Use this in your process() method
// Return: whether or not we've changed states during the transition
void handle_cooling_transitions(strCooling *sCooling)
{
    #if DEBUG == 1U
        //printf("Handling transitions in handle_cooling_transitions()\n");
    #endif
    
    bool command_executed;

    // Handle internal commands first
    // Note: we're passing in the internal command directly, but we could be passing in any strCoolingCmd.
    command_executed = handle_cooling_command(sCooling, &sCooling->internal_command, &sCooling->internal_command);

    if ( ! command_executed )
    {
        // Handle external commands if no internal command was executed
        // Note: we're passing in the external command directly, but we could be passing in any strCoolingCmd.
        command_executed = handle_cooling_command(sCooling, &sCooling->external_command, &sCooling->external_command);
    }
    
    // If we didn't execute a command, run our conditional transitions
    if ( ! command_executed )
    {
        // Run conditional transitions
        handle_cooling_conditional_transition(sCooling);
    }
    else
    {
        // continue
    }
    
    // If we haven't changed states so far (i.e. nothing has caused a transition), try our timeouts
    if ( ! sm_transitioning(&sCooling->sm))
    {
        handle_cooling_timeout_transition(sCooling);
    }
    else
    {
        // continue
    }

    // If we haven't changed states so far (i.e. nothing has caused a transition), try our automatic transitions
    if ( ! sm_transitioning(&sCooling->sm))
    {
        handle_cooling_automatic_transition(sCooling);
    }
    else
    {
        // Nothing more to do
    }

}


