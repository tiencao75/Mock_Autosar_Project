#include "WdgM.h"

extern volatile uint8 Simulate_Error;  

void WdgM_Init(void)
{
    WdgIf_Init();
}

WdgM_StatusType WdgM_CheckStatus(void)
{
    if (Simulate_Error == 1)  
    {
        return WDGM_SYSTEM_ERROR;
    }
    Simulate_Error = 0;    
    return WDGM_SYSTEM_OK;
}


void WdgM_MainFunction(void)
{
    static uint8 system_healthy = 1; 

    if (system_healthy)
    {
        WdgIf_Trigger();
    }
    else
    {
        //printf("System Error: Watchdog not triggered!\n");
    }

    WdgIf_CheckTimeout();
}