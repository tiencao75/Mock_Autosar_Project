#ifndef WDGM_H_
#define WDGM_H_

#include "WdgIf.h"

typedef enum {
    WDGM_SYSTEM_OK,     
    WDGM_SYSTEM_WARNING,  
    WDGM_SYSTEM_ERROR     
} WdgM_StatusType;

void WdgM_Init(void);

WdgM_StatusType WdgM_CheckStatus(void);

void WdgM_MainFunction(void);

#endif /* WDGM_H_ */