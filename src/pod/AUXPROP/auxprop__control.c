#include "auxprop__control.h"
#include "auxprop__types.h"

/////////////////////////////////////////////////////////////////////
//  AuxProp transition and command guard functions
/////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////
//  AuxProp command and transition handling
/////////////////////////////////////////////////////////////////////


// Handle conditional transitions
// Return whether or not we're transitioning
bool handle_auxprop_conditional_transition(strAuxProp *sAuxProp)
{
    // No conditional transitions to handle
    return FALSE;
}


// Handle timeout transitions
// Return whether or not we're transitioning
bool handle_auxprop_timeout_transition(strAuxProp *sAuxProp)
{
    // No timeout transitions to handle
    return FALSE;
}


// Handle automatic transitions
// Return whether or not we're transitioning
bool handle_auxprop_automatic_transition(strAuxProp *sAuxProp)
{
    // No automatic transitions to handle
    return FALSE;
} 


/////////////////////////////////////////////////////////////////////
//  AuxProp command handling
/////////////////////////////////////////////////////////////////////

// Handle command
// Return whether or not a command was handled
bool handle_auxprop_command(strAuxProp *sAuxProp, const strAuxPropCmd *cmd, strAuxPropCmd *command_slot)
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
        // printf("Handling command in handle_auxprop_command()\n");
    #endif

    // Return quickly if no command
    if (cmd->command == AUXPROP_NO_CMD)
    {
        return FALSE;
    } 
    else 
    {
        // fall on
    }    

    E_AUXPROP_STATE_T state = sAuxProp->sm.state;
    E_AUXPROP_COMMAND_T command = cmd->command;

    bool exec_command = TRUE;

    //  1. Check to see if the command is allowed in our current state
    if (auxprop_state_allows_command(state, command))
    {

        //  2. Check any guards that may prevent a command from executing.        
        // (No checks necessary here)
                
    } 
    else 
    {
        #if DEBUG == 1U
        printf("%s -- REJECTING COMMAND: Command %s not allowed in state %s\n", sAuxProp->absname, lookup_auxprop_command(command), lookup_auxprop_state(state));
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
        E_AUXPROP_STATE_T target_state = get_auxprop_target_state(state, command);
        if ( target_state != AUXPROP_NULL_STATE )
        {
            sAuxProp->sm.state = target_state;
        }
        
        #if DEBUG == 1U
            printf("%s -- COMMITTING COMMAND %s in state %s\n", sAuxProp->absname, lookup_auxprop_command(command), lookup_auxprop_state(state));
        #endif

        // Commit the command (update variables based on command args)
        commit_auxprop_command(sAuxProp, cmd, command_slot);
    
    } 
    else 
    {
        // Reject the command
        reject_auxprop_command(sAuxProp, cmd, "handle_auxprop_command(): exec_command is false", command_slot);

    }

    // Note: The fact that we've executed a command does not necessarily mean we've transitioned
    return exec_command;

}


void commit_auxprop_command(strAuxProp *sAuxProp, const strAuxPropCmd *cmd, strAuxPropCmd *command_slot)
{
    // Update variables as needed based on command arguments
    switch (cmd->command)
    {
        case AUXPROP_DRIVE_FORWARD:
            // vAPU_CLUTCH__Engage();
            // vAPU_THROTTLE__Enable();
            // vAPU_THROTTLE__Set_Velocity_mms(u32Veloc_mms);
            // vAUP_THROTTLE__Forward();
            break;
        
        case AUXPROP_DRIVE_REVERSE:
            // // Engage the clutch;
            // vAPU_CLUTCH__Engage();;
            // // Disengage throttle so that we can;
            // vAPU_THROTTLE__Disable();;
            // vAPU_THROTTLE__Set_Velocity_mms(u32Veloc_mms);;
            // vAUP_THROTTLE__Reverse();;
            // vAPU_THROTTLE__Enable();;
            // @todo: add action for OrderedDict([('loop', 'a'), ('test', 'b')])
            break;
        
        case AUXPROP_SET_THROTTLE:
            // vAPU_THROTTLE__Set_Velocity_mms(u32Veloc_mms);
            break;
        
        case AUXPROP_MOTOR_FORWARD:
            // vAPU_THROTTLE__Enable();
            // vAPU_THROTTLE__Set_Velocity_mms(u32Veloc_mms);
            // vAUP_THROTTLE__Forward();
            break;
        
        case AUXPROP_MOTOR_REVERSE:
            // vAPU_THROTTLE__Enable();
            // vAPU_THROTTLE__Set_Velocity_mms(u32Veloc_mms);
            // vAUP_THROTTLE__Reverse();
            break;

        default:
            break;
    }

    // Clear the command now that we've handled it
    clear_auxprop_command(sAuxProp, command_slot);
}


void reject_auxprop_command(strAuxProp *sAuxProp, const strAuxPropCmd *cmd, const char *reject_message, strAuxPropCmd *command_slot)
{
    // Don't know if we need to do anything here, but maybe send a message? 
    // ...
    
    clear_auxprop_command(sAuxProp, command_slot);
}


void clear_auxprop_command(strAuxProp *sAuxProp, strAuxPropCmd *command_slot)
{
    // Clear the auxprop command
    command_slot->command = AUXPROP_NO_CMD; // No command
}


/////////////////////////////////////////////////////////////////////
//  AuxProp command functions
/////////////////////////////////////////////////////////////////////

void internal_cmd_AUXPROP_ENABLE(strAuxProp *sAuxProp)
{
    #if DEBUG == 1U
        printf("cmd_AUXPROP_ENABLE() called\n");
    #endif
    
    strAuxPropCmd * cmd = &sAuxProp->internal_command;
    cmd->command = AUXPROP_ENABLE;

}

void internal_cmd_AUXPROP_MANUAL(strAuxProp *sAuxProp)
{
    #if DEBUG == 1U
        printf("cmd_AUXPROP_MANUAL() called\n");
    #endif
    
    strAuxPropCmd * cmd = &sAuxProp->internal_command;
    cmd->command = AUXPROP_MANUAL;

}

void internal_cmd_AUXPROP_DISABLE(strAuxProp *sAuxProp)
{
    #if DEBUG == 1U
        printf("cmd_AUXPROP_DISABLE() called\n");
    #endif
    
    strAuxPropCmd * cmd = &sAuxProp->internal_command;
    cmd->command = AUXPROP_DISABLE;

}

void cmd_AUXPROP_DRIVE_FORWARD(strAuxProp *sAuxProp, Luint32 u32Veloc_mms)
{
    #if DEBUG == 1U
        printf("cmd_AUXPROP_DRIVE_FORWARD() called\n");
    #endif
    
    strAuxPropCmd * cmd = &sAuxProp->external_command;
    cmd->command = AUXPROP_DRIVE_FORWARD;
    cmd->args.AUXPROP_DRIVE_FORWARD.u32Veloc_mms = u32Veloc_mms;

}

void cmd_AUXPROP_DRIVE_REVERSE(strAuxProp *sAuxProp, Luint32 u32Veloc_mms)
{
    #if DEBUG == 1U
        printf("cmd_AUXPROP_DRIVE_REVERSE() called\n");
    #endif
    
    strAuxPropCmd * cmd = &sAuxProp->external_command;
    cmd->command = AUXPROP_DRIVE_REVERSE;
    cmd->args.AUXPROP_DRIVE_REVERSE.u32Veloc_mms = u32Veloc_mms;

}

void cmd_AUXPROP_STOP(strAuxProp *sAuxProp)
{
    #if DEBUG == 1U
        printf("cmd_AUXPROP_STOP() called\n");
    #endif
    
    strAuxPropCmd * cmd = &sAuxProp->external_command;
    cmd->command = AUXPROP_STOP;

}

void cmd_AUXPROP_SET_THROTTLE(strAuxProp *sAuxProp, Luint32 u32Veloc_mms)
{
    #if DEBUG == 1U
        printf("cmd_AUXPROP_SET_THROTTLE() called\n");
    #endif
    
    strAuxPropCmd * cmd = &sAuxProp->external_command;
    cmd->command = AUXPROP_SET_THROTTLE;
    cmd->args.AUXPROP_SET_THROTTLE.u32Veloc_mms = u32Veloc_mms;

}

void cmd_AUXPROP_CLUTCH_ENGAGE(strAuxProp *sAuxProp)
{
    #if DEBUG == 1U
        printf("cmd_AUXPROP_CLUTCH_ENGAGE() called\n");
    #endif
    
    strAuxPropCmd * cmd = &sAuxProp->external_command;
    cmd->command = AUXPROP_CLUTCH_ENGAGE;

}

void cmd_AUXPROP_CLUTCH_DISENGAGE(strAuxProp *sAuxProp)
{
    #if DEBUG == 1U
        printf("cmd_AUXPROP_CLUTCH_DISENGAGE() called\n");
    #endif
    
    strAuxPropCmd * cmd = &sAuxProp->external_command;
    cmd->command = AUXPROP_CLUTCH_DISENGAGE;

}

void cmd_AUXPROP_MOTOR_FORWARD(strAuxProp *sAuxProp, Luint32 u32Veloc_mms)
{
    #if DEBUG == 1U
        printf("cmd_AUXPROP_MOTOR_FORWARD() called\n");
    #endif
    
    strAuxPropCmd * cmd = &sAuxProp->external_command;
    cmd->command = AUXPROP_MOTOR_FORWARD;
    cmd->args.AUXPROP_MOTOR_FORWARD.u32Veloc_mms = u32Veloc_mms;

}

void cmd_AUXPROP_MOTOR_REVERSE(strAuxProp *sAuxProp, Luint32 u32Veloc_mms)
{
    #if DEBUG == 1U
        printf("cmd_AUXPROP_MOTOR_REVERSE() called\n");
    #endif
    
    strAuxPropCmd * cmd = &sAuxProp->external_command;
    cmd->command = AUXPROP_MOTOR_REVERSE;
    cmd->args.AUXPROP_MOTOR_REVERSE.u32Veloc_mms = u32Veloc_mms;

}

void cmd_AUXPROP_MOTOR_STOP(strAuxProp *sAuxProp)
{
    #if DEBUG == 1U
        printf("cmd_AUXPROP_MOTOR_STOP() called\n");
    #endif
    
    strAuxPropCmd * cmd = &sAuxProp->external_command;
    cmd->command = AUXPROP_MOTOR_STOP;

}

