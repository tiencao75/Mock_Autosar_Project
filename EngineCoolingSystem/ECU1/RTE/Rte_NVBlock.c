#include "Rte_NVBlock.h"
#include <stdio.h>

/*----------------------------------------------------------------------------*/
/* Biến toàn cục lưu trữ lỗi NVM                                              */
/*----------------------------------------------------------------------------*/
uint16 StoredErrorCode = 0; 

/******************************************************************************/  
/* API: Rte_Read_PP_NVBlock_GetErrorData                                      */
/* Đọc lỗi từ RTE                                                             */  
/******************************************************************************/  
FUNC(Std_ReturnType, RTE_CODE)  
Rte_Read_PP_NVBlock_GetErrorData(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) errorData) {
    if (errorData == NULL_PTR) {
        return E_NOT_OK;
    }
    *errorData = StoredErrorCode;
    return E_OK;
}

/******************************************************************************/  
/* API: Rte_Call_NVManager_StoreError                                         */
/* Gọi xuống NVM Manager để lưu lỗi                                           */  
/******************************************************************************/  
FUNC(Std_ReturnType, RTE_CODE)  
Rte_Call_NVManager_StoreError(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) errorData) {
    if (errorData == NULL_PTR) {
        return E_NOT_OK;
    }

    // Gọi xuống NVM Manager để ghi vào bộ nhớ vĩnh viễn
    NvM_WriteBlock(NVM_E_PARAM_BLOCK_ID, errorData);
    
    return E_OK;
}

FUNC(void, RTE_CODE) Rte_Call_PP_HandleErrorToNVM(void){
    HandleErrorToNVM();
}