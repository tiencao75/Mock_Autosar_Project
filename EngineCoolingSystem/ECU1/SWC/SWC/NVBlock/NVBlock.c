#include "Rte_NVBlock.h"
#include <stdio.h>

/******************************************************************************/  
/* Runnable: WriteErrorToNVM                                                  */
/* Ghi lỗi vào NVM                                                             */  
/******************************************************************************/  
FUNC(void, AUTOMATIC) WriteErrorToNVM(void) {
    uint16 errorCode;
        Rte_Write_PP_NVManager_StoreError(&errorCode);
        printf("NVBlock: Stored Error Code = %d into NVM\n", errorCode);
}

/******************************************************************************/  
/* Runnable: ReadErrorToNVM                                                   */
/* Đọc lỗi từ NVM                                                              */  
/******************************************************************************/  
FUNC(void, AUTOMATIC) ReadErrorToNVM(void) {
    uint16 errorCode;

    if (Rte_Read_PP_NVBlock_GetErrorData(&errorCode) == E_OK) {
        printf("NVBlock: Retrieved Error Code = %d from NVM\n", errorCode);
    }
}
