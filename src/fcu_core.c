#include "fcu_core.h"
#include "pod/pod.h"

// @todo: figure out where/how to create this struct in the real environment
struct _strFCU sFCU;

void vFCU__Init()
{
    // Initialize subsystems
    vPod__Init(&sFCU.pod);

}


void vFCU__Process(strPod *subsystem)
{
    vPod__Process(&sFCU.pod);
}
