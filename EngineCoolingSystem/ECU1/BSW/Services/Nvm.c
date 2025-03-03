#include "Nvm.h"
#include "Compiler.h"  // Thêm Compiler.h
#include <stdio.h>
#include <string.h>

/* Biến toàn cục mô phỏng dữ liệu NVM */
STATIC VAR(uint8, NVM_VAR) nvm_data[10][100] = {0}; // Tối đa 10 khối, mỗi khối 100 bytes
STATIC VAR(uint16, NVM_VAR) nvm_lengths[10] = {0};  // Độ dài của từng khối
STATIC VAR(uint8, NVM_VAR) is_initialized = 0;      // Trạng thái khởi tạo

/* Hàm khởi tạo module Nvm */
FUNC(void, NVM_CODE) Nvm_Init(
    P2CONST(Nvm_ConfigType, NVM_CONST, AUTOMATIC) config
) {
    if (config == NULL_PTR) {
        Det_ReportError(6, 0, 0, NVM_E_PARAM_POINTER);
        return;
    }

    if (config->isEnabled) {
        is_initialized = 1;
        if (config->blockId < 10 && config->blockSize <= 100) {
            memset(nvm_data[config->blockId], 0, config->blockSize);
            nvm_lengths[config->blockId] = config->blockSize;
        }
        printf("Nvm Module Initialized (Block ID %d, Block Size %d bytes)\n",
               config->blockId, config->blockSize);
    } else {
        is_initialized = 0;
        Det_ReportError(6, 0, 0, NVM_E_PARAM_CONFIG);
    }
}

/* Hàm ghi dữ liệu vào NVM */
FUNC(Std_ReturnType, NVM_CODE) Nvm_WriteBlock(
    VAR(uint8, NVM_VAR) blockId,
    P2CONST(uint8, NVM_CONST, AUTOMATIC) data,
    VAR(uint16, NVM_VAR) length
) {
    if (!is_initialized) {
        Det_ReportError(6, 0, 1, NVM_E_NOT_INITIALIZED);
        return NVM_NOT_OK;
    }

    if (blockId >= 10 || data == NULL_PTR || length > 100) {
        Det_ReportError(6, 0, 1, NVM_E_PARAM_BLOCK);
        return NVM_NOT_OK;
    }

    memcpy(nvm_data[blockId], data, length);
    nvm_lengths[blockId] = length;
    printf("Nvm: Wrote Block %d - Length = %d, Data = ", blockId, length);
    for (VAR(uint16, AUTOMATIC) i = 0; i < length; i++) {
        printf("0x%02X ", data[i]);
    }
    printf("\n");
    return NVM_OK;
}

/* Hàm đọc dữ liệu từ NVM */
FUNC(Std_ReturnType, NVM_CODE) Nvm_ReadBlock(
    VAR(uint8, NVM_VAR) blockId,
    P2VAR(uint8, NVM_VAR, AUTOMATIC) data,
    P2VAR(uint16, NVM_VAR, AUTOMATIC) length
) {
    if (!is_initialized) {
        Det_ReportError(6, 0, 2, NVM_E_NOT_INITIALIZED);
        return NVM_NOT_OK;
    }

    if (blockId >= 10 || data == NULL_PTR || length == NULL_PTR) {
        Det_ReportError(6, 0, 2, NVM_E_PARAM_BLOCK);
        return NVM_NOT_OK;
    }

    *length = nvm_lengths[blockId];
    memcpy(data, nvm_data[blockId], *length);
    printf("Nvm: Read Block %d - Length = %d, Data = ", blockId, *length);
    for (VAR(uint16, AUTOMATIC) i = 0; i < *length; i++) {
        printf("0x%02X ", data[i]);
    }
    printf("\n");
    return NVM_OK;
}

/* Hàm main để kiểm tra */
#ifdef TEST_NVM
FUNC(int, NVM_CODE) main(void) {
    VAR(Nvm_ConfigType, AUTOMATIC) config = {0, 10, 1};
    VAR(uint8, AUTOMATIC) write_data[10] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};
    VAR(uint8, AUTOMATIC) read_data[10];
    VAR(uint16, AUTOMATIC) read_length;

    Nvm_Init(&config);

    if (Nvm_WriteBlock(0, write_data, 10) == NVM_OK) {
        printf("Data written successfully\n");
    }

    if (Nvm_ReadBlock(0, read_data, &read_length) == NVM_OK) {
        printf("Data read successfully\n");
    }

    return 0;
}
#endif