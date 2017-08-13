#include "cooling__control.h"
#include "cooling__types.h"

/////////////////////////////////////////////////////////////////////
//  Cooling transition and command guard functions
/////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////
//  Cooling command and transition handling
/////////////////////////////////////////////////////////////////////


// Handle conditional transitions
// Return whether or not we're transitioning
bool handle_cooling_conditional_transition(strCooling *sCooling)
{
    // No conditional transitions to handle
    return FALSE;
}


// Handle timeout transitions
// Return whether or not we're transitioning
bool handle_cooling_timeout_transition(strCooling *sCooling)
{
    // No timeout transitions to handle
    return FALSE;
}


// Handle automatic transitions
// Return whether or not we're transitioning
bool handle_cooling_automatic_transition(strCooling *sCooling)
{
    // No automatic transitions to handle
    return FALSE;
} 


/////////////////////////////////////////////////////////////////////
//  Cooling command handling
/////////////////////////////////////////////////////////////////////

// Handle command
// Return whether or not a command was handled
bool handle_cooling_command(strCooling *sCooling, const strCoolingCmd *cmd, strCoolingCmd *command_slot)
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
        // printf("Handling command in handle_cooling_command()\n");
    #endif

    // Return quickly if no command
    if (cmd->command == COOLING_NO_CMD)
    {
        return FALSE;
    } 
    else 
    {
        // fall on
    }    

    E_COOLING_STATE_T state = sCooling->sm.state;
    E_COOLING_COMMAND_T command = cmd->command;

    bool exec_command = TRUE;

    //  1. Check to see if the command is allowed in our current state
    if (cooling_state_allows_command(state, command))
    {

        //  2. Check any guards that may prevent a command from executing.        
        // (No checks necessary here)
                
    } 
    else 
    {
        #if DEBUG == 1U
        printf("%s -- REJECTING COMMAND: Command %s not allowed in state %s\n", sCooling->absname, lookup_cooling_command(command), lookup_cooling_state(state));
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
        E_COOLING_STATE_T target_state = get_cooling_target_state(state, command);
        if ( target_state != COOLING_NULL_STATE )
        {
            sCooling->sm.state = target_state;
        }
        
        #if DEBUG == 1U
            printf("%s -- COMMITTING COMMAND %s in state %s\n", sCooling->absname, lookup_cooling_command(command), lookup_cooling_state(state));
        #endif

        // Commit the command (update variables based on command args)
        commit_cooling_command(sCooling, cmd, command_slot);
    
    } 
    else 
    {
        // Reject the command
        reject_cooling_command(sCooling, cmd, "handle_cooling_command(): exec_command is false", command_slot);

    }

    // Note: The fact that we've executed a command does not necessarily mean we've transitioned
    return exec_command;

}


void commit_cooling_command(strCooling *sCooling, const strCoolingCmd *cmd, strCoolingCmd *command_slot)
{
    // Update variables as needed based on command arguments
    
    // Note: Only commands with arguments need to be handled here    

    // Clear the command now that we've handled it
    clear_cooling_command(sCooling, command_slot);
}


void reject_cooling_command(strCooling *sCooling, const strCoolingCmd *cmd, const char *reject_message, strCoolingCmd *command_slot)
{
    // Don't know if we need to do anything here, but maybe send a message? 
    // ...
    
    clear_cooling_command(sCooling, command_slot);
}


void clear_cooling_command(strCooling *sCooling, strCoolingCmd *command_slot)
{
    // Clear the cooling command
    command_slot->command = COOLING_NO_CMD; // No command
}


/////////////////////////////////////////////////////////////////////
//  Cooling command functions
/////////////////////////////////////////////////////////////////////

void internal_cmd_COOLING_DISABLE(strCooling *sCooling)
{
    #if DEBUG == 1U
        printf("cmd_COOLING_DISABLE() called\n");
    #endif
    
    strCoolingCmd * cmd = &sCooling->internal_command;
    cmd->command = COOLING_DISABLE;

}

void cmd_COOLING_AUTO(strCooling *sCooling)
{
    #if DEBUG == 1U
        printf("cmd_COOLING_AUTO() called\n");
    #endif
    
    strCoolingCmd * cmd = &sCooling->external_command;
    cmd->command = COOLING_AUTO;

}

void cmd_COOLING_PURGE(strCooling *sCooling)
{
    #if DEBUG == 1U
        printf("cmd_COOLING_PURGE() called\n");
    #endif
    
    strCoolingCmd * cmd = &sCooling->external_command;
    cmd->command = COOLING_PURGE;

}

void cmd_COOLING_MANUAL(strCooling *sCooling)
{
    #if DEBUG == 1U
        printf("cmd_COOLING_MANUAL() called\n");
    #endif
    
    strCoolingCmd * cmd = &sCooling->external_command;
    cmd->command = COOLING_MANUAL;

}

void cmd_COOLING_INTERLOCK(strCooling *sCooling)
{
    #if DEBUG == 1U
        printf("cmd_COOLING_INTERLOCK() called\n");
    #endif
    
    strCoolingCmd * cmd = &sCooling->external_command;
    cmd->command = COOLING_INTERLOCK;

}

void cmd_COOLING_RELEASE_INTERLOCK(strCooling *sCooling)
{
    #if DEBUG == 1U
        printf("cmd_COOLING_RELEASE_INTERLOCK() called\n");
    #endif
    
    strCoolingCmd * cmd = &sCooling->external_command;
    cmd->command = COOLING_RELEASE_INTERLOCK;

}

void cmd_COOLING_SET_DUTY_CYCLE(strCooling *sCooling)
{
    #if DEBUG == 1U
        printf("cmd_COOLING_SET_DUTY_CYCLE() called\n");
    #endif
    
    strCoolingCmd * cmd = &sCooling->external_command;
    cmd->command = COOLING_SET_DUTY_CYCLE;

}

