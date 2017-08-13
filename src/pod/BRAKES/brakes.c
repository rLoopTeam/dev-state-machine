#include "brakes.h"
#include "../../fcu_core.h"

// Subsystems
#include "brake/brake.h"


void vBrakes__Init(strBrakes *sBrakes)
{
    sBrakes->sm.state = BRAKES_HOLD_STATE;
        

    // Init Brake subsystems
    for (int i = 0; i < C_FCU__NUM_BRAKES; i++) 
    {
        // Set the index in the subsystem
        sBrakes->sBrake[i].index = i;
    
        #if DEBUG == 1U
        // Set names for debug printing
        sprintf(sBrakes->sBrake[i].name, "sBrake[%d]", i);
        sprintf(sBrakes->sBrake[i].absname, "%s.%s", sBrakes->absname, sBrakes->sBrake[i].name);
        #endif
    
        // Init
        vBrake__Init(&sBrakes->sBrake[i]);
    }

}


void vBrakes__Process(strBrakes *sBrakes)
{
        
    // Step the state machine to pick up on state changes etc.
    sm_step(&sBrakes->sm);
        
    // Process brakes state machine
    switch (sBrakes->sm.state)
    {
        case BRAKES_DISABLED_STATE:
        
            if (sm_entering(&sBrakes->sm, BRAKES_DISABLED_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering BRAKES_DISABLED_STATE\n", sBrakes->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_brakes_transitions(sBrakes);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sBrakes->sm, BRAKES_DISABLED_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting BRAKES_DISABLED_STATE\n", sBrakes->absname);
                #endif
        
            }
            
            break;
        
        case BRAKES_ENABLED_STATE:
        
            if (sm_entering(&sBrakes->sm, BRAKES_ENABLED_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering BRAKES_ENABLED_STATE\n", sBrakes->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_brakes_transitions(sBrakes);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sBrakes->sm, BRAKES_ENABLED_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting BRAKES_ENABLED_STATE\n", sBrakes->absname);
                #endif
        
            }
            
            break;
        
        case BRAKES_HOLD_STATE:
        
            if (sm_entering(&sBrakes->sm, BRAKES_HOLD_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering BRAKES_HOLD_STATE\n", sBrakes->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_brakes_transitions(sBrakes);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sBrakes->sm, BRAKES_HOLD_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting BRAKES_HOLD_STATE\n", sBrakes->absname);
                #endif
        
            }
            
            break;
        
        case BRAKES_DEPLOY_STATE:
        
            if (sm_entering(&sBrakes->sm, BRAKES_DEPLOY_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering BRAKES_DEPLOY_STATE\n", sBrakes->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_brakes_transitions(sBrakes);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sBrakes->sm, BRAKES_DEPLOY_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting BRAKES_DEPLOY_STATE\n", sBrakes->absname);
                #endif
        
            }
            
            break;
        
        case BRAKES_RETRACT_STATE:
        
            if (sm_entering(&sBrakes->sm, BRAKES_RETRACT_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering BRAKES_RETRACT_STATE\n", sBrakes->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_brakes_transitions(sBrakes);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sBrakes->sm, BRAKES_RETRACT_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting BRAKES_RETRACT_STATE\n", sBrakes->absname);
                #endif
        
            }
            
            break;
        
        case BRAKES_SEEK_STATE:
        
            if (sm_entering(&sBrakes->sm, BRAKES_SEEK_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering BRAKES_SEEK_STATE\n", sBrakes->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_brakes_transitions(sBrakes);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sBrakes->sm, BRAKES_SEEK_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting BRAKES_SEEK_STATE\n", sBrakes->absname);
                #endif
        
            }
            
            break;
        
        case BRAKES_CONTROLLED_BRAKE_STATE:
        
            if (sm_entering(&sBrakes->sm, BRAKES_CONTROLLED_BRAKE_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering BRAKES_CONTROLLED_BRAKE_STATE\n", sBrakes->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_brakes_transitions(sBrakes);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sBrakes->sm, BRAKES_CONTROLLED_BRAKE_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting BRAKES_CONTROLLED_BRAKE_STATE\n", sBrakes->absname);
                #endif
        
            }
            
            break;
        
        case BRAKES_EMERGENCY_BRAKE_STATE:
        
            if (sm_entering(&sBrakes->sm, BRAKES_EMERGENCY_BRAKE_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering BRAKES_EMERGENCY_BRAKE_STATE\n", sBrakes->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_brakes_transitions(sBrakes);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sBrakes->sm, BRAKES_EMERGENCY_BRAKE_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting BRAKES_EMERGENCY_BRAKE_STATE\n", sBrakes->absname);
                #endif
        
            }
            
            break;
        
        case BRAKES_INTERLOCK_STATE:
        
            if (sm_entering(&sBrakes->sm, BRAKES_INTERLOCK_STATE)) {
                // Perform entering actions
                #if DEBUG == 1U
                    printf("- %s Entering BRAKES_INTERLOCK_STATE\n", sBrakes->absname);
                #endif
            }
            
            // Handle commands and conditional transitions
            handle_brakes_transitions(sBrakes);  // Note: this returns bool for whether or not we've transitioned...
            
            if (sm_exiting(&sBrakes->sm, BRAKES_INTERLOCK_STATE)) 
            {
                // We're exiting this state -- perform any exit actions
                // ...
                #if DEBUG == 1U
                    printf("- %s Exiting BRAKES_INTERLOCK_STATE\n", sBrakes->absname);
                #endif
        
            }
            
            break;

    }
    
    /////////////////////////////////////////////////////////////////
    //  Process Subsystems
    /////////////////////////////////////////////////////////////////
    
    // Process Brake subsystems
    for (int i = 0; i < C_FCU__NUM_BRAKES; i++) 
    {
        vBrake__Process(&sBrakes->sBrake[i]);
    }

}


void vBrakes__10MS_ISR(strBrakes *sBrakes) 
{
    // Brake 10ms ISR
    for (int i = 0; i < C_FCU__NUM_BRAKES; i++) 
    {
        vBrake__10MS_ISR(&sBrakes->sBrake[i]);
    }
    

}

void vBrakes__100MS_ISR(strBrakes *sBrakes)
{
    // Brake 100ms ISR
    for (int i = 0; i < C_FCU__NUM_BRAKES; i++) 
    {
        vBrake__100MS_ISR(&sBrakes->sBrake[i]);
    }
    

}


// NOTE: Use this in your process() method
// Return: whether or not we've changed states during the transition
void handle_brakes_transitions(strBrakes *sBrakes)
{
    #if DEBUG == 1U
        //printf("Handling transitions in handle_brakes_transitions()\n");
    #endif
    
    bool command_executed;

    // Handle internal commands first
    // Note: we're passing in the internal command directly, but we could be passing in any strBrakesCmd.
    command_executed = handle_brakes_command(sBrakes, &sBrakes->internal_command, &sBrakes->internal_command);

    if ( ! command_executed )
    {
        // Handle external commands if no internal command was executed
        // Note: we're passing in the external command directly, but we could be passing in any strBrakesCmd.
        command_executed = handle_brakes_command(sBrakes, &sBrakes->external_command, &sBrakes->external_command);
    }
    
    // If we didn't execute a command, run our conditional transitions
    if ( ! command_executed )
    {
        // Run conditional transitions
        handle_brakes_conditional_transition(sBrakes);
    }
    else
    {
        // continue
    }
    
    // If we haven't changed states so far (i.e. nothing has caused a transition), try our timeouts
    if ( ! sm_transitioning(&sBrakes->sm))
    {
        handle_brakes_timeout_transition(sBrakes);
    }
    else
    {
        // continue
    }

    // If we haven't changed states so far (i.e. nothing has caused a transition), try our automatic transitions
    if ( ! sm_transitioning(&sBrakes->sm))
    {
        handle_brakes_automatic_transition(sBrakes);
    }
    else
    {
        // Nothing more to do
    }

}


