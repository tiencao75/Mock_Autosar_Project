#ifndef RTE_NV_BLOCK_H
#define RTE_NV_BLOCK_H

#include "Std_Types.h"
#include "Compiler.h"
#include "Compiler_Cfg.h"
#include "Nvm.h"

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
Rte_Call_NVManager_StoreError(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) errorData);

/*API goi tu Os*/
FUNC(void, RTE_CODE) Rte_Call_PP_HandleErrorToNVM(void);
#endif /* RTE_NV_BLOCK_H */
