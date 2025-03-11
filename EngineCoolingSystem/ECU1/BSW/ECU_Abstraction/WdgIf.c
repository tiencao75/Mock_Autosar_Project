#include "WdgIf.h"

void WdgIf_Init(void)
{
    Wdg_Init();
}

void WdgIf_Trigger(void)
{
    Wdg_Trigger();
}

void WdgIf_SetMode(WdgIf_ModeType Mode)
{
    Wdg_SetMode(Mode);
}

void WdgIf_CheckTimeout(void)
{
    Wdg_CheckTimeout();
}