#ifndef _FCU_CORE_H_
#define _FCU_CORE_H_

// @todo: fix this to be the correct path for the pod
#include "./pod/pod__types.h"

void vFCU__Init();
void vFCU__Process();

struct _strFCU
{
    strPod pod;
    
};

#endif //_FCU_CORE_H_
