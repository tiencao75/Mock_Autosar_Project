#include "Wdg.h"
#include "Wdg_Cfg.h"

static uint32 watchdog_counter = 0;
static uint32 watchdog_timeout = WDG_TIMEOUT_SLOW;
static WdgIf_ModeType Wdg_Mode = WDGIF_SLOW_MODE;

void Wdg_Init(void)
{
    watchdog_counter = 0;
    Wdg_Mode = WDGIF_SLOW_MODE;
    watchdog_timeout = WDG_TIMEOUT_SLOW;
    //printf("Watchdog Initialized (Timeout: %d cycles)\n", watchdog_timeout);
}

void Wdg_Trigger(void)
{
    watchdog_counter = 0; // Reset watchdog counter
    //printf("Watchdog Triggered!\n");
}

void Wdg_SetMode(WdgIf_ModeType Mode)
{
    Wdg_Mode = Mode;

    if (Mode == WDGIF_SLOW_MODE)
    {
        watchdog_timeout = WDG_TIMEOUT_SLOW;
        //printf("Watchdog set to SLOW mode\n");
    }
    else if (Mode == WDGIF_FAST_MODE)
    {
        watchdog_timeout = WDG_TIMEOUT_FAST;
        //printf("Watchdog set to FAST mode\n");
    }
    else
    {
        //printf("Watchdog OFF Mode (No Reset)\n");
    }
}

void Wdg_CheckTimeout(void)
{
    watchdog_counter++;

    if (watchdog_counter > watchdog_timeout)
    {
        //printf("Watchdog Timeout! System Resetting...\n");
        watchdog_counter = 0; // Giả lập reset bằng cách đặt lại biến
    }
}