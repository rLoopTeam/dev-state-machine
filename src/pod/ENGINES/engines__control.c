#include "engines__control.h"
#include "engines__types.h"

/////////////////////////////////////////////////////////////////////
//  Engines transition and command guard functions
/////////////////////////////////////////////////////////////////////

bool engine_startup_error(strEngines *sEngines)
{
    // @todo: implement
    return FALSE;
}


/////////////////////////////////////////////////////////////////////
//  Engines command and transition handling
/////////////////////////////////////////////////////////////////////


// Handle conditional transitions
// Return whether or not we're transitioning
bool handle_engines_conditional_transition(strEngines *sEngines)
{
    StateMachine *sm = &sEngines->sm;

    bool transitioning;

    switch(sm->state) {  // Current state
        case ENGINES_STARTUP_STATE:
            if ( engine_startup_error(sEngines) ) 
            {
                sm->state = ENGINES_SHUTDOWN_STATE;
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
bool handle_engines_timeout_transition(strEngines *sEngines)
{
    // No timeout transitions to handle
    return FALSE;
}


// Handle automatic transitions
// Return whether or not we're transitioning
bool handle_engines_automatic_transition(strEngines *sEngines)
{
    StateMachine *sm = &sEngines->sm;
    
    bool transitioning;

    switch(sm->state) {  // Current state
        case ENGINES_STARTUP_STATE:
            sEngines->sm.state = ENGINES_RUN_STATE;
        case ENGINES_SHUTDOWN_STATE:
            sEngines->sm.state = ENGINES_STOPPED_STATE;

        default:
            // Do nothing
            break;

    }
    
    return transitioning;

} 


/////////////////////////////////////////////////////////////////////
//  Engines command handling
/////////////////////////////////////////////////////////////////////

// Handle command
// Return whether or not a command was handled
bool handle_engines_command(strEngines *sEngines, const strEnginesCmd *cmd, strEnginesCmd *command_slot)
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
        // printf("Handling command in handle_engines_command()\n");
    #endif

    // Return quickly if no command
    if (cmd->command == ENGINES_NO_CMD)
    {
        return FALSE;
    } 
    else 
    {
        // fall on
    }    

    E_ENGINES_STATE_T state = sEngines->sm.state;
    E_ENGINES_COMMAND_T command = cmd->command;

    bool exec_command = TRUE;

    //  1. Check to see if the command is allowed in our current state
    if (engines_state_allows_command(state, command))
    {

        //  2. Check any guards that may prevent a command from executing.        
        // (No checks necessary here)
                
    } 
    else 
    {
        #if DEBUG == 1U
        printf("%s -- REJECTING COMMAND: Command %s not allowed in state %s\n", sEngines->absname, lookup_engines_command(command), lookup_engines_state(state));
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
        E_ENGINES_STATE_T target_state = get_engines_target_state(state, command);
        if ( target_state != ENGINES_NULL_STATE )
        {
            sEngines->sm.state = target_state;
        }
        
        #if DEBUG == 1U
            printf("%s -- COMMITTING COMMAND %s in state %s\n", sEngines->absname, lookup_engines_command(command), lookup_engines_state(state));
        #endif

        // Commit the command (update variables based on command args)
        commit_engines_command(sEngines, cmd, command_slot);
    
    } 
    else 
    {
        // Reject the command
        reject_engines_command(sEngines, cmd, "handle_engines_command(): exec_command is false", command_slot);

    }

    // Note: The fact that we've executed a command does not necessarily mean we've transitioned
    return exec_command;

}


void commit_engines_command(strEngines *sEngines, const strEnginesCmd *cmd, strEnginesCmd *command_slot)
{
    // Update variables as needed based on command arguments
    
    // Note: Only commands with arguments need to be handled here    

    // Clear the command now that we've handled it
    clear_engines_command(sEngines, command_slot);
}


void reject_engines_command(strEngines *sEngines, const strEnginesCmd *cmd, const char *reject_message, strEnginesCmd *command_slot)
{
    // Don't know if we need to do anything here, but maybe send a message? 
    // ...
    
    clear_engines_command(sEngines, command_slot);
}


void clear_engines_command(strEngines *sEngines, strEnginesCmd *command_slot)
{
    // Clear the engines command
    command_slot->command = ENGINES_NO_CMD; // No command
}


/////////////////////////////////////////////////////////////////////
//  Engines command functions
/////////////////////////////////////////////////////////////////////

void cmd_ENGINES_START(strEngines *sEngines)
{
    #if DEBUG == 1U
        printf("cmd_ENGINES_START() called\n");
    #endif
    
    strEnginesCmd * cmd = &sEngines->external_command;
    cmd->command = ENGINES_START;

}

void cmd_ENGINES_RUN(strEngines *sEngines)
{
    #if DEBUG == 1U
        printf("cmd_ENGINES_RUN() called\n");
    #endif
    
    strEnginesCmd * cmd = &sEngines->external_command;
    cmd->command = ENGINES_RUN;

}

void cmd_ENGINES_SHUTDOWN(strEngines *sEngines)
{
    #if DEBUG == 1U
        printf("cmd_ENGINES_SHUTDOWN() called\n");
    #endif
    
    strEnginesCmd * cmd = &sEngines->external_command;
    cmd->command = ENGINES_SHUTDOWN;

}

void cmd_ENGINES_INTERLOCK(strEngines *sEngines)
{
    #if DEBUG == 1U
        printf("cmd_ENGINES_INTERLOCK() called\n");
    #endif
    
    strEnginesCmd * cmd = &sEngines->external_command;
    cmd->command = ENGINES_INTERLOCK;

}

void cmd_ENGINES_RELEASE_INTERLOCK(strEngines *sEngines)
{
    #if DEBUG == 1U
        printf("cmd_ENGINES_RELEASE_INTERLOCK() called\n");
    #endif
    
    strEnginesCmd * cmd = &sEngines->external_command;
    cmd->command = ENGINES_RELEASE_INTERLOCK;

}

