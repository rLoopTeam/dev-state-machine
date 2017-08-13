#include "COMPAT.h"
#include "pod/pod.h"
#include "fcu_core.h"  // For testing only @todo: change this

//main FCU structure;
// @todo: figure out where/how to define this struct in the real setup
extern struct _strFCU sFCU;

#define DEBUG 1U

#if DEBUG == 1U
#include <stdio.h>
#include "pod/pod__control.h"
#include "pod/BRAKES/brakes__control.h"
#include "pod/BRAKES/BRAKE/brake__control.h"
#endif



int main(void)
{

    #if DEBUG == 1U
        int counter = 0;
        strPod *pod = &sFCU.pod;

        // Set names for debug printing
        sprintf(pod->name, "Pod");
        sprintf(pod->absname, "Pod");
        printf("Initializing FCU\n");
    #endif
        
    vFCU__Init();
    

    #if DEBUG == 1U
    printf("Beginning FCU process loop");
    while(1 && counter < 20) 
    #else
    while(1)
    #endif
    {
        printf("----------------\n");
        vFCU__Process();
        #if DEBUG == 1U
        
        counter++;

        if (counter == 2) { cmd_TEST_MODE(pod); }
        
        if (counter == 7) { cmd_IDLE(pod); }
        
        if (counter == 11) { cmd_BRAKES_DEPLOY(&pod->sBrakes); }

        if (counter == 15) { cmd_SINGLE_BRAKE_DEPLOY(&pod->sBrakes.sBrake[0]); }
            
        #endif
    }
}
