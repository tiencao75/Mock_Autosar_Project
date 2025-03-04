#include "Rte_NVBlock.h"
#include <stdio.h>

/*----------------------------------------------------------------------------*/
/* Biến toàn cục lưu trữ lỗi NVM                                              */
/*----------------------------------------------------------------------------*/
uint16 StoredErrorCode = 0;
uint16 CalibrationData = 75;

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
    printf("RTE: Retrieved Error Code = %d from RTE\n", StoredErrorCode);
    return E_OK;
}

/******************************************************************************/  
/* API: Rte_Call_NVManager_StoreError                                         */
/* Gọi xuống NVM Manager để lưu lỗi                                           */  
/******************************************************************************/  
FUNC(Std_ReturnType, RTE_CODE)  
Rte_Write_PP_NVManager_StoreError(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) errorData) {
    if (errorData == NULL_PTR) {
        return E_NOT_OK;
    }

    StoredErrorCode = *errorData;  // Lưu lỗi vào bộ nhớ nội bộ

    // Gọi xuống NVM Manager để ghi vào bộ nhớ vĩnh viễn
    printf("RTE: Storing Error Code = %d in NVM Manager\n", StoredErrorCode);
    
    return E_OK;
}
