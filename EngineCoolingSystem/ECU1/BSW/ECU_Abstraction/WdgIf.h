#ifndef WDGIF_H_
#define WDGIF_H_

#include "Wdg.h"

void WdgIf_Init(void);
void WdgIf_Trigger(void);
void WdgIf_SetMode(WdgIf_ModeType Mode);
void WdgIf_CheckTimeout(void);

#endif /* WDGIF_H_ */