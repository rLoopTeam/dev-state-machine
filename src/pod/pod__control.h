#ifndef _POD__GUARDS_H_
#define _POD__GUARDS_H_

#include "pod__types.h"


/////////////////////////////////////////////////////////////////////
//  Pod guard/check functions
/////////////////////////////////////////////////////////////////////
 
/**
 * armed_wait_checks_ok
 */
bool armed_wait_checks_ok(strPod * sPod);

/**
 * drive_checks_ok
 */
bool drive_checks_ok(strPod * sPod);

/**
 * flight_prep_checks_ok
 */
bool flight_prep_checks_ok(strPod * sPod);

/**
 * flight_readiness_checks_ok
 */
bool flight_readiness_checks_ok(strPod * sPod);

/**
 * accel_confirmed
 */
bool accel_confirmed(strPod * sPod);

/**
 * pusher_separation_confirmed
 */
bool pusher_separation_confirmed(strPod * sPod);

/**
 * pod_stop_confirmed
 */
bool pod_stop_confirmed(strPod * sPod);

/**
 * spindown_complete_confirmed
 */
bool spindown_complete_confirmed(strPod * sPod);


/////////////////////////////////////////////////////////////////////
//  Pod transitions
/////////////////////////////////////////////////////////////////////

/**
 *  Pod conditional transitions
 */
bool handle_pod_conditional_transition(strPod *sPod);

/**
 *  Pod timeout transitions
 */
bool handle_pod_timeout_transition(strPod *sPod);

/**
 *  Pod automatic transitions
 */
bool handle_pod_automatic_transition(strPod *sPod);


/////////////////////////////////////////////////////////////////////
//  Pod command handling
/////////////////////////////////////////////////////////////////////

/**
 *  Pod command handler
 */
bool handle_pod_command(strPod *sPod, const strPodCmd *cmd, strPodCmd *command_slot);

/**
 *  Apply changes to the system based on the command
 */
void commit_pod_command(strPod *sPod, const strPodCmd *cmd, strPodCmd *command_slot);

/**
 *  Reject a command so that no change is made to the system
 */
void reject_pod_command(strPod *sPod, const strPodCmd *cmd, const char *reject_message, strPodCmd *command_slot);

/**
 *  Clear command from sPod
 */
void clear_pod_command(strPod *sPod, strPodCmd *command_slot);


/////////////////////////////////////////////////////////////////////
//  Pod command functions
/////////////////////////////////////////////////////////////////////

/**
 *  Transition to IDLE
 */
void cmd_IDLE(strPod *sPod);

/**
 *  Transition to TEST_MODE
 */
void cmd_TEST_MODE(strPod *sPod);

/**
 *  Transition to DRIVE
 */
void cmd_DRIVE(strPod *sPod);

/**
 *  Stop the pod
 */
void cmd_DRIVE_STOP(strPod *sPod);

/**
 *  Transition to FLIGHT_PREP
 */
void cmd_FLIGHT_PREP(strPod *sPod);

/**
 *  Transition to ARMED_WAIT
 */
void cmd_ARMED_WAIT(strPod *sPod);

/**
 *  Transition to READY
 */
void cmd_READY(strPod *sPod);

/**
 *  Flash the lights to provide an outside signal that the pod is receiving commands
 */
void cmd_FLASH_LIGHTS(strPod *sPod);

/**
 *  Testing accidental/specific allowed commands
 */
void cmd_TEST_CMD_DRIVE(strPod *sPod);


#endif // _POD__GUARDS_H_
