#include "Nvm.h"
#include <stdio.h>

Nvm_Error_Type errorArray[MAX_ERRORS] = {
    {NVM_E_PARAM_BLOCK_ID, 0},
    {NVM_E_PARAM_BLOCK_ID, 0},
    {NVM_E_PARAM_BLOCK_ID, 0},
    {NVM_E_PARAM_BLOCK_ID, 0},
    {NVM_E_PARAM_BLOCK_ID, 0},
};

FUNC(Std_ReturnType, NVM_CODE) NvM_ReadBlock(
    VAR(uint16 , NvM_BlockIdType) BlockId,
    P2VAR(void, AUTOMATIC, NVM_APPL_DATA) DataBuffer)
{
    if (BlockId == 0 || DataBuffer == NULL_PTR) {
        return E_NOT_OK;
    }

    /* Giả lập đọc dữ liệu từ NVM */


    return E_OK;
}

FUNC(Std_ReturnType, NVM_CODE) NvM_WriteBlock(
    VAR(uint16 , NvM_BlockIdType) BlockId,
    CONSTP2VAR(void, AUTOMATIC, NVM_APPL_DATA) DataBuffer) 
{
    if (BlockId == 0 || DataBuffer == NULL_PTR) {
        return E_NOT_OK;
    }
/* Ép kiểu DataBuffer thành uint16* để lấy mã DTC */
    uint16 dtcCode = *(CONSTP2VAR(uint16, AUTOMATIC, NVM_APPL_DATA))DataBuffer;

/* Ghi vào mảng lỗi */
    uint8 k;
    for (k = 0; k < MAX_ERRORS; k++) {
    if (errorArray[k].BlockId == BlockId) {
        errorArray[k].DataBuffer = dtcCode; // Ghi mã DTC vào mảng
        return E_OK;
        }
    }
    return E_OK;
}
