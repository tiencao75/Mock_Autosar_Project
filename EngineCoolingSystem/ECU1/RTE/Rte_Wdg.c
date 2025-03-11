#include "Rte_Wdg.h"

FUNC(WdgM_StatusType, RTE_CODE) Rte_Call_WdgM_TriggerWatchdog(void)
{
    WdgM_StatusType status;
    status = WdgM_CheckStatus();
    return status;
}

FUNC(Std_ReturnType, RTE_CODE) Rte_Call_WdgM_SetMode(WdgIf_ModeType Mode)
{
    WdgIf_SetMode(Mode);
    return E_OK;
}