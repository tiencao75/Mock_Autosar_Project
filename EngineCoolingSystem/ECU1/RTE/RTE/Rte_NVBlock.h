#ifndef RTE_NV_BLOCK_H
#define RTE_NV_BLOCK_H

#include "Std_Types.h"
#include "Compiler.h"
#include "Compiler_Cfg.h"

/*----------------------------------------------------------------------------*/
/* API Declarations                                                           */
/*----------------------------------------------------------------------------*/
extern uint16 StoredErrorCode;
extern uint16 CalibrationData;
/* API đọc dữ liệu lỗi từ RTE */
FUNC(Std_ReturnType, RTE_CODE)
Rte_Read_PP_NVBlock_GetErrorData(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) errorData);

/* API gọi xuống NVM Manager để lưu lỗi */
FUNC(Std_ReturnType, RTE_CODE)
Rte_Write_PP_NVManager_StoreError(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) errorData);

#endif /* RTE_NV_BLOCK_H */
