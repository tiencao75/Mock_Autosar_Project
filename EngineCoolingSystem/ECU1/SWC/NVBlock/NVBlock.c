#include "Rte_NVBlock.h"
#include <stdio.h>

uint16 errorCode;
/******************************************************************************/  
/* Runnable: WriteErrorToNVM                                                  */
/* Ghi lỗi vào NVM                                                             */  
/******************************************************************************/  
FUNC(void, AUTOMATIC) HandleErrorToNVM(void) {
    Rte_Read_PP_NVBlock_GetErrorData(&errorCode);
    Rte_Call_NVManager_StoreError(&errorCode);
}
