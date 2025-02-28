#ifndef NVM_H
#define NVM_H

#include "Std_Types.h" // Bao gồm các kiểu dữ liệu AUTOSAR
#include "Det.h"       // Báo lỗi phát triển

// Trạng thái trả về cho Nvm
#define NVM_OK       E_OK
#define NVM_NOT_OK   E_NOT_OK

// Định nghĩa các mã lỗi cho Nvm
#define NVM_E_PARAM_POINTER    0x01U  // Lỗi con trỏ NULL
#define NVM_E_PARAM_CONFIG     0x02U  // Lỗi cấu hình
#define NVM_E_NOT_INITIALIZED  0x03U  // Lỗi chưa khởi tạo
#define NVM_E_PARAM_BLOCK      0x04U  // Lỗi khối dữ liệu không hợp lệ

// Định nghĩa cấu hình cho Nvm
typedef struct {
    uint8 blockId;       // ID khối dữ liệu trong NVM
    uint16 blockSize;    // Kích thước khối dữ liệu (bytes)
    boolean isEnabled;   // Trạng thái bật/tắt
} Nvm_ConfigType;

// Định nghĩa kiểu dữ liệu cho khối dữ liệu NVM
typedef struct {
    uint8* data;         // Dữ liệu lưu trong NVM
    uint16 length;       // Độ dài dữ liệu
} Nvm_DataType;

// Hàm khởi tạo module Nvm
void Nvm_Init(const Nvm_ConfigType* config);

// Hàm ghi dữ liệu vào NVM (mô phỏng)
Std_ReturnType Nvm_WriteBlock(uint8 blockId, const uint8* data, uint16 length);

// Hàm đọc dữ liệu từ NVM (mô phỏng)
Std_ReturnType Nvm_ReadBlock(uint8 blockId, uint8* data, uint16* length);

#endif // NVM_H