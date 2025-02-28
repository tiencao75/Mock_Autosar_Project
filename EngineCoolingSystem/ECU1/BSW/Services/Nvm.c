#include "Nvm.h"
#include <stdio.h>
#include <string.h>

// Biến toàn cục mô phỏng dữ liệu NVM (tối đa 10 khối, mỗi khối 100 bytes)
static uint8 nvm_data[10][100] = {0}; // Dữ liệu ban đầu là 0
static uint16 nvm_lengths[10] = {0};  // Độ dài của từng khối
static uint8 is_initialized = 0;      // Trạng thái khởi tạo

// Hàm khởi tạo module Nvm
void Nvm_Init(const Nvm_ConfigType* config) {
    if (config == NULL_PTR) {
        Det_ReportError(6, 0, 0, NVM_E_PARAM_POINTER); // Báo lỗi AUTOSAR
        return;
    }

    if (config->isEnabled) {
        is_initialized = 1;
        // Mô phỏng khởi tạo khối dữ liệu với ID và kích thước
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

// Hàm ghi dữ liệu vào NVM (mô phỏng)
Std_ReturnType Nvm_WriteBlock(uint8 blockId, const uint8* data, uint16 length) {
    if (!is_initialized) {
        Det_ReportError(6, 0, 1, NVM_E_NOT_INITIALIZED);
        return NVM_NOT_OK;
    }

    if (blockId >= 10 || data == NULL_PTR || length > 100) {
        Det_ReportError(6, 0, 1, NVM_E_PARAM_BLOCK);
        return NVM_NOT_OK;
    }

    // Mô phỏng ghi dữ liệu vào NVM
    memcpy(nvm_data[blockId], data, length);
    nvm_lengths[blockId] = length;
    printf("Nvm: Wrote Block %d - Length = %d, Data = ", blockId, length);
    for (uint16 i = 0; i < length; i++) {
        printf("0x%02X ", data[i]);
    }
    printf("\n");
    return NVM_OK;
}

// Hàm đọc dữ liệu từ NVM (mô phỏng)
Std_ReturnType Nvm_ReadBlock(uint8 blockId, uint8* data, uint16* length) {
    if (!is_initialized) {
        Det_ReportError(6, 0, 2, NVM_E_NOT_INITIALIZED);
        return NVM_NOT_OK;
    }

    if (blockId >= 10 || data == NULL_PTR || length == NULL_PTR) {
        Det_ReportError(6, 0, 2, NVM_E_PARAM_BLOCK);
        return NVM_NOT_OK;
    }

    // Mô phỏng đọc dữ liệu từ NVM
    *length = nvm_lengths[blockId];
    memcpy(data, nvm_data[blockId], *length);
    printf("Nvm: Read Block %d - Length = %d, Data = ", blockId, *length);
    for (uint16 i = 0; i < *length; i++) {
        printf("0x%02X ", data[i]);
    }
    printf("\n");
    return NVM_OK;
}

// Hàm main để kiểm tra (chỉ dùng khi compile riêng)
#ifdef TEST_NVM
int main(void) {
    Nvm_ConfigType config = {0, 10, 1}; // Block ID 0, Size 10 bytes, bật
    uint8 write_data[10] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};
    uint8 read_data[10];
    uint16 read_length;

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