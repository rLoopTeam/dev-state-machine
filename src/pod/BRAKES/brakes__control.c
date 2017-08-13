#include "brakes__control.h"
#include "brakes__types.h"

/////////////////////////////////////////////////////////////////////
//  Brakes transition and command guard functions
/////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////
//  Brakes command and transition handling
/////////////////////////////////////////////////////////////////////


// Handle conditional transitions
// Return whether or not we're transitioning
bool handle_brakes_conditional_transition(strBrakes *sBrakes)
{
    // No conditional transitions to handle
    return FALSE;
}


// Handle timeout transitions
// Return whether or not we're transitioning
bool handle_brakes_timeout_transition(strBrakes *sBrakes)
{
    // No timeout transitions to handle
    return FALSE;
}


// Handle automatic transitions
// Return whether or not we're transitioning
bool handle_brakes_automatic_transition(strBrakes *sBrakes)
{
    // No automatic transitions to handle
    return FALSE;
} 


/////////////////////////////////////////////////////////////////////
//  Brakes command handling
/////////////////////////////////////////////////////////////////////

// Handle command
// Return whether or not a command was handled
bool handle_brakes_command(strBrakes *sBrakes, const strBrakesCmd *cmd, strBrakesCmd *command_slot)
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
        // printf("Handling command in handle_brakes_command()\n");
    #endif

    // Return quickly if no command
    if (cmd->command == BRAKES_NO_CMD)
    {
        return FALSE;
    } 
    else 
    {
        // fall on
    }    

    E_BRAKES_STATE_T state = sBrakes->sm.state;
    E_BRAKES_COMMAND_T command = cmd->command;

    bool exec_command = TRUE;

    //  1. Check to see if the command is allowed in our current state
    if (brakes_state_allows_command(state, command))
    {

        //  2. Check any guards that may prevent a command from executing.        
        // (No checks necessary here)
                
    } 
    else 
    {
        #if DEBUG == 1U
        printf("%s -- REJECTING COMMAND: Command %s not allowed in state %s\n", sBrakes->absname, lookup_brakes_command(command), lookup_brakes_state(state));
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
        E_BRAKES_STATE_T target_state = get_brakes_target_state(state, command);
        if ( target_state != BRAKES_NULL_STATE )
        {
            sBrakes->sm.state = target_state;
        }
        
        #if DEBUG == 1U
            printf("%s -- COMMITTING COMMAND %s in state %s\n", sBrakes->absname, lookup_brakes_command(command), lookup_brakes_state(state));
        #endif

        // Commit the command (update variables based on command args)
        commit_brakes_command(sBrakes, cmd, command_slot);
    
    } 
    else 
    {
        // Reject the command
        reject_brakes_command(sBrakes, cmd, "handle_brakes_command(): exec_command is false", command_slot);

    }

    // Note: The fact that we've executed a command does not necessarily mean we've transitioned
    return exec_command;

}


void commit_brakes_command(strBrakes *sBrakes, const strBrakesCmd *cmd, strBrakesCmd *command_slot)
{
    // Update variables as needed based on command arguments
    switch (cmd->command)
    {
        case BRAKES_SEEK:
            
            break;

        default:
            break;
    }

    // Clear the command now that we've handled it
    clear_brakes_command(sBrakes, command_slot);
}


void reject_brakes_command(strBrakes *sBrakes, const strBrakesCmd *cmd, const char *reject_message, strBrakesCmd *command_slot)
{
    // Don't know if we need to do anything here, but maybe send a message? 
    // ...
    
    clear_brakes_command(sBrakes, command_slot);
}


void clear_brakes_command(strBrakes *sBrakes, strBrakesCmd *command_slot)
{
    // Clear the brakes command
    command_slot->command = BRAKES_NO_CMD; // No command
}


/////////////////////////////////////////////////////////////////////
//  Brakes command functions
/////////////////////////////////////////////////////////////////////

void internal_cmd_BRAKES_ENABLE(strBrakes *sBrakes)
{
    #if DEBUG == 1U
        printf("cmd_BRAKES_ENABLE() called\n");
    #endif
    
    strBrakesCmd * cmd = &sBrakes->internal_command;
    cmd->command = BRAKES_ENABLE;

}

void internal_cmd_BRAKES_DISABLE(strBrakes *sBrakes)
{
    #if DEBUG == 1U
        printf("cmd_BRAKES_DISABLE() called\n");
    #endif
    
    strBrakesCmd * cmd = &sBrakes->internal_command;
    cmd->command = BRAKES_DISABLE;

}

void cmd_BRAKES_HOLD(strBrakes *sBrakes)
{
    #if DEBUG == 1U
        printf("cmd_BRAKES_HOLD() called\n");
    #endif
    
    strBrakesCmd * cmd = &sBrakes->external_command;
    cmd->command = BRAKES_HOLD;

}

void cmd_BRAKES_DEPLOY(strBrakes *sBrakes)
{
    #if DEBUG == 1U
        printf("cmd_BRAKES_DEPLOY() called\n");
    #endif
    
    strBrakesCmd * cmd = &sBrakes->external_command;
    cmd->command = BRAKES_DEPLOY;

}

void cmd_BRAKES_RETRACT(strBrakes *sBrakes)
{
    #if DEBUG == 1U
        printf("cmd_BRAKES_RETRACT() called\n");
    #endif
    
    strBrakesCmd * cmd = &sBrakes->external_command;
    cmd->command = BRAKES_RETRACT;

}

void cmd_BRAKES_SEEK(strBrakes *sBrakes, int speed_what_units, int target_mm)
{
    #if DEBUG == 1U
        printf("cmd_BRAKES_SEEK() called\n");
    #endif
    
    strBrakesCmd * cmd = &sBrakes->external_command;
    cmd->command = BRAKES_SEEK;
    cmd->args.BRAKES_SEEK.speed_what_units = speed_what_units;
    cmd->args.BRAKES_SEEK.target_mm = target_mm;

}

void cmd_BRAKES_CONTROLLED_BRAKE(strBrakes *sBrakes)
{
    #if DEBUG == 1U
        printf("cmd_BRAKES_CONTROLLED_BRAKE() called\n");
    #endif
    
    strBrakesCmd * cmd = &sBrakes->external_command;
    cmd->command = BRAKES_CONTROLLED_BRAKE;

}

void cmd_BRAKES_EMERGENCY_BRAKE(strBrakes *sBrakes)
{
    #if DEBUG == 1U
        printf("cmd_BRAKES_EMERGENCY_BRAKE() called\n");
    #endif
    
    strBrakesCmd * cmd = &sBrakes->external_command;
    cmd->command = BRAKES_EMERGENCY_BRAKE;

}

void cmd_BRAKES_INTERLOCK(strBrakes *sBrakes)
{
    #if DEBUG == 1U
        printf("cmd_BRAKES_INTERLOCK() called\n");
    #endif
    
    strBrakesCmd * cmd = &sBrakes->external_command;
    cmd->command = BRAKES_INTERLOCK;

}

void internal_cmd_BRAKES_RELEASE_INTERLOCK(strBrakes *sBrakes)
{
    #if DEBUG == 1U
        printf("cmd_BRAKES_RELEASE_INTERLOCK() called\n");
    #endif
    
    strBrakesCmd * cmd = &sBrakes->internal_command;
    cmd->command = BRAKES_RELEASE_INTERLOCK;

}

