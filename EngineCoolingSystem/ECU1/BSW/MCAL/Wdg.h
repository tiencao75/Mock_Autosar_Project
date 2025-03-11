#ifndef WDG_H_
#define WDG_H_

#include "Std_Types.h"
#include "Compiler.h"
#include <stdio.h>

// Chế độ Watchdog
typedef enum {
    WDGIF_OFF_MODE,
    WDGIF_SLOW_MODE,
    WDGIF_FAST_MODE
} WdgIf_ModeType;

void Wdg_Init(void);

void Wdg_Trigger(void);

void Wdg_SetMode(WdgIf_ModeType Mode);

void Wdg_CheckTimeout(void);

#endif /* WDG_H_ */