#include "brake__control.h"
#include "brake__types.h"

/////////////////////////////////////////////////////////////////////
//  Brake transition and command guard functions
/////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////
//  Brake command and transition handling
/////////////////////////////////////////////////////////////////////


// Handle conditional transitions
// Return whether or not we're transitioning
bool handle_brake_conditional_transition(strBrake *sBrake)
{
    // No conditional transitions to handle
    return FALSE;
}


// Handle timeout transitions
// Return whether or not we're transitioning
bool handle_brake_timeout_transition(strBrake *sBrake)
{
    // No timeout transitions to handle
    return FALSE;
}


// Handle automatic transitions
// Return whether or not we're transitioning
bool handle_brake_automatic_transition(strBrake *sBrake)
{
    // No automatic transitions to handle
    return FALSE;
} 


/////////////////////////////////////////////////////////////////////
//  Brake command handling
/////////////////////////////////////////////////////////////////////

// Handle command
// Return whether or not a command was handled
bool handle_brake_command(strBrake *sBrake, const strBrakeCmd *cmd, strBrakeCmd *command_slot)
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
        // printf("Handling command in handle_brake_command()\n");
    #endif

    // Return quickly if no command
    if (cmd->command == BRAKE_NO_CMD)
    {
        return FALSE;
    } 
    else 
    {
        // fall on
    }    

    E_BRAKE_STATE_T state = sBrake->sm.state;
    E_BRAKE_COMMAND_T command = cmd->command;

    bool exec_command = TRUE;

    //  1. Check to see if the command is allowed in our current state
    if (brake_state_allows_command(state, command))
    {

        //  2. Check any guards that may prevent a command from executing.        
        // (No checks necessary here)
                
    } 
    else 
    {
        #if DEBUG == 1U
        printf("%s -- REJECTING COMMAND: Command %s not allowed in state %s\n", sBrake->absname, lookup_brake_command(command), lookup_brake_state(state));
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
        E_BRAKE_STATE_T target_state = get_brake_target_state(state, command);
        if ( target_state != BRAKE_NULL_STATE )
        {
            sBrake->sm.state = target_state;
        }
        
        #if DEBUG == 1U
            printf("%s -- COMMITTING COMMAND %s in state %s\n", sBrake->absname, lookup_brake_command(command), lookup_brake_state(state));
        #endif

        // Commit the command (update variables based on command args)
        commit_brake_command(sBrake, cmd, command_slot);
    
    } 
    else 
    {
        // Reject the command
        reject_brake_command(sBrake, cmd, "handle_brake_command(): exec_command is false", command_slot);

    }

    // Note: The fact that we've executed a command does not necessarily mean we've transitioned
    return exec_command;

}


void commit_brake_command(strBrake *sBrake, const strBrakeCmd *cmd, strBrakeCmd *command_slot)
{
    // Update variables as needed based on command arguments
    switch (cmd->command)
    {
        case SINGLE_BRAKE_SEEK:
            
            break;

        default:
            break;
    }

    // Clear the command now that we've handled it
    clear_brake_command(sBrake, command_slot);
}


void reject_brake_command(strBrake *sBrake, const strBrakeCmd *cmd, const char *reject_message, strBrakeCmd *command_slot)
{
    // Don't know if we need to do anything here, but maybe send a message? 
    // ...
    
    clear_brake_command(sBrake, command_slot);
}


void clear_brake_command(strBrake *sBrake, strBrakeCmd *command_slot)
{
    // Clear the brake command
    command_slot->command = BRAKE_NO_CMD; // No command
}


/////////////////////////////////////////////////////////////////////
//  Brake command functions
/////////////////////////////////////////////////////////////////////

void cmd_SINGLE_BRAKE_HOLD(strBrake *sBrake)
{
    #if DEBUG == 1U
        printf("cmd_SINGLE_BRAKE_HOLD() called\n");
    #endif
    
    strBrakeCmd * cmd = &sBrake->external_command;
    cmd->command = SINGLE_BRAKE_HOLD;

}

void cmd_SINGLE_BRAKE_DEPLOY(strBrake *sBrake)
{
    #if DEBUG == 1U
        printf("cmd_SINGLE_BRAKE_DEPLOY() called\n");
    #endif
    
    strBrakeCmd * cmd = &sBrake->external_command;
    cmd->command = SINGLE_BRAKE_DEPLOY;

}

void cmd_SINGLE_BRAKE_RETRACT(strBrake *sBrake)
{
    #if DEBUG == 1U
        printf("cmd_SINGLE_BRAKE_RETRACT() called\n");
    #endif
    
    strBrakeCmd * cmd = &sBrake->external_command;
    cmd->command = SINGLE_BRAKE_RETRACT;

}

void cmd_SINGLE_BRAKE_SEEK(strBrake *sBrake, int speed_what_units, int target_mm)
{
    #if DEBUG == 1U
        printf("cmd_SINGLE_BRAKE_SEEK() called\n");
    #endif
    
    strBrakeCmd * cmd = &sBrake->external_command;
    cmd->command = SINGLE_BRAKE_SEEK;
    cmd->args.SINGLE_BRAKE_SEEK.speed_what_units = speed_what_units;
    cmd->args.SINGLE_BRAKE_SEEK.target_mm = target_mm;

}

void cmd_SINGLE_BRAKE_INTERLOCK(strBrake *sBrake)
{
    #if DEBUG == 1U
        printf("cmd_SINGLE_BRAKE_INTERLOCK() called\n");
    #endif
    
    strBrakeCmd * cmd = &sBrake->external_command;
    cmd->command = SINGLE_BRAKE_INTERLOCK;

}

void cmd_SINGLE_BRAKE_RELEASE_INTERLOCK(strBrake *sBrake)
{
    #if DEBUG == 1U
        printf("cmd_SINGLE_BRAKE_RELEASE_INTERLOCK() called\n");
    #endif
    
    strBrakeCmd * cmd = &sBrake->external_command;
    cmd->command = SINGLE_BRAKE_RELEASE_INTERLOCK;

}

