#include "counter.h"
#include "OsCfg.h"
#include <stdint.h>
#include "WdgM.h"

#define NVIC_ST_CTRL_R (*((volatile uint32_t*)0xE000E010))
#define NVIC_ST_RELOAD_R (*((volatile uint32_t*)0xE000E014))
#define NVIC_ST_CURRENT_R (*((volatile uint32_t*)0xE000E018))
#define NVIC_SYSPRI3_R (*((volatile uint32_t*)0xE000ED20))
#define NVIC_AIRCR  (*((volatile uint32_t*)0xE000ED0C))
#define INIT_TO_ZERO 0U
#define NVIC_RESET_VALUE 0x05FA0004  

static uint32_t OsCnt_SystemCounter = INIT_TO_ZERO;
volatile uint32_t counter = 0;
volatile uint32_t reset = 0;

void NVIC_SystemReset(void)
{
    NVIC_AIRCR = NVIC_RESET_VALUE;  
}


void SysTick_Init(void)
{

 NVIC_ST_CTRL_R = 0;			/* disable SysTick during setup */
 NVIC_ST_CURRENT_R = 0;		/* any write to current clears it */
 NVIC_SYSPRI3_R |= 0x20000000; /* priority 1 */
 NVIC_SYSPRI3_R |= 0x00200000; /* priority 1 to PEND SV  */
 NVIC_ST_RELOAD_R = OsCfg_SYSTEM_TICK_IN_MS * 16000u; /*TODO: 10 should be a configured value */
 NVIC_ST_CTRL_R = 0x07;		 /* enable, core clock and interrupt arm */

}

void OsCnt_IncrSystemCounter(void)
{
    OsCnt_SystemCounter++;
    counter = OsCnt_SystemCounter;

    if (OsCnt_SystemCounter % 10 == 0)
    {
        WdgM_StatusType status = Rte_Call_WdgM_TriggerWatchdog();
        
        if (status == WDGM_SYSTEM_OK)
        {
					  reset = 0;
            Rte_Call_WdgM_TriggerWatchdog();
        }
        else
        {
           //printf("System Error Detected: Watchdog Not Triggered!\n");
					 uint32_t i;
					 reset = 1;
					 NVIC_SystemReset();
					 
        }
    }
}


uint32_t OsCnt_GetSystemCounter(void)
{
  return OsCnt_SystemCounter;
}