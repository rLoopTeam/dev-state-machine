#include "engines.h"
#include "../../fcu_core.h"


void vEngines__Init(strEngines *sEngines)
{
    sEngines->sm.state = ENGINES_INTERLOCK_STATE;
        
}


void vEngines__Process(strEngines *sEngines)
{
        
    // Step the state machine to pick up on state changes etc.
    sm_step(&sEngines->sm);
        
    // Process engines state machine
    switch (sEngines->sm.state)
    {
        case ENGINES_STOPPED_STATE:
        
            if (sm_entering(&sEngines->sm, ENGINES_STOPPED_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering ENGINES_STOPPED_STATE\n", sEngines->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_engines_transitions(sEngines);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sEngines->sm, ENGINES_STOPPED_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting ENGINES_STOPPED_STATE\n", sEngines->absname);
                #endif
        
            }
            
            break;
        
        case ENGINES_STARTUP_STATE:
        
            if (sm_entering(&sEngines->sm, ENGINES_STARTUP_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering ENGINES_STARTUP_STATE\n", sEngines->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_engines_transitions(sEngines);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sEngines->sm, ENGINES_STARTUP_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting ENGINES_STARTUP_STATE\n", sEngines->absname);
                #endif
        
            }
            
            break;
        
        case ENGINES_RUN_STATE:
        
            if (sm_entering(&sEngines->sm, ENGINES_RUN_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering ENGINES_RUN_STATE\n", sEngines->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_engines_transitions(sEngines);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sEngines->sm, ENGINES_RUN_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting ENGINES_RUN_STATE\n", sEngines->absname);
                #endif
        
            }
            
            break;
        
        case ENGINES_SHUTDOWN_STATE:
        
            if (sm_entering(&sEngines->sm, ENGINES_SHUTDOWN_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering ENGINES_SHUTDOWN_STATE\n", sEngines->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_engines_transitions(sEngines);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sEngines->sm, ENGINES_SHUTDOWN_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting ENGINES_SHUTDOWN_STATE\n", sEngines->absname);
                #endif
        
            }
            
            break;
        
        case ENGINES_INTERLOCK_STATE:
        
            if (sm_entering(&sEngines->sm, ENGINES_INTERLOCK_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering ENGINES_INTERLOCK_STATE\n", sEngines->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_engines_transitions(sEngines);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sEngines->sm, ENGINES_INTERLOCK_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting ENGINES_INTERLOCK_STATE\n", sEngines->absname);
                #endif
        
            }
            
            break;

    }
    
}


void vEngines__10MS_ISR(strEngines *sEngines) 
{
    
}

void vEngines__100MS_ISR(strEngines *sEngines)
{
    
}


// NOTE: Use this in your process() method
// Return: whether or not we've changed states during the transition
void handle_engines_transitions(strEngines *sEngines)
{
    #if DEBUG == 1U
        //printf("Handling transitions in handle_engines_transitions()\n");
    #endif
    
    bool command_executed;

    // Handle internal commands first
    // Note: we're passing in the internal command directly, but we could be passing in any strEnginesCmd.
    command_executed = handle_engines_command(sEngines, &sEngines->internal_command, &sEngines->internal_command);

    if ( ! command_executed )
    {
        // Handle external commands if no internal command was executed
        // Note: we're passing in the external command directly, but we could be passing in any strEnginesCmd.
        command_executed = handle_engines_command(sEngines, &sEngines->external_command, &sEngines->external_command);
    }
    
    // If we didn't execute a command, run our conditional transitions
    if ( ! command_executed )
    {
        // Run conditional transitions
        handle_engines_conditional_transition(sEngines);
    }
    else
    {
        // continue
    }
    
    // If we haven't changed states so far (i.e. nothing has caused a transition), try our timeouts
    if ( ! sm_transitioning(&sEngines->sm))
    {
        handle_engines_timeout_transition(sEngines);
    }
    else
    {
        // continue
    }

    // If we haven't changed states so far (i.e. nothing has caused a transition), try our automatic transitions
    if ( ! sm_transitioning(&sEngines->sm))
    {
        handle_engines_automatic_transition(sEngines);
    }
    else
    {
        // Nothing more to do
    }

}


