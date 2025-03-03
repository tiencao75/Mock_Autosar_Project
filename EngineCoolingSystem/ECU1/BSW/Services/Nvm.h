#ifndef NVM_H
#define NVM_H

#include "Compiler.h"    // Thêm Compiler.h
#include "Std_Types.h"   // Kiểu dữ liệu chuẩn AUTOSAR
#include "Det.h"         // Báo lỗi phát triển

/* Trạng thái trả về cho Nvm */
#define NVM_OK       E_OK
#define NVM_NOT_OK   E_NOT_OK

/* Định nghĩa các mã lỗi */
#define NVM_E_PARAM_POINTER    0x01U  // Lỗi con trỏ NULL
#define NVM_E_PARAM_CONFIG     0x02U  // Lỗi cấu hình
#define NVM_E_NOT_INITIALIZED  0x03U  // Lỗi chưa khởi tạo
#define NVM_E_PARAM_BLOCK      0x04U  // Lỗi khối dữ liệu không hợp lệ

/* Cấu trúc cấu hình cho Nvm */
typedef struct {
    VAR(uint8, NVM_VAR) blockId;       // ID khối dữ liệu
    VAR(uint16, NVM_VAR) blockSize;    // Kích thước khối (bytes)
    VAR(boolean, NVM_VAR) isEnabled;   // Trạng thái bật/tắt
} Nvm_ConfigType;

/* Kiểu dữ liệu cho khối dữ liệu NVM */
typedef struct {
    P2VAR(uint8, NVM_VAR, AUTOMATIC) data; // Dữ liệu lưu trong NVM
    VAR(uint16, NVM_VAR) length;           // Độ dài dữ liệu
} Nvm_DataType;

/* Khai báo hàm */
FUNC(void, NVM_CODE) Nvm_Init(
    P2CONST(Nvm_ConfigType, NVM_CONST, AUTOMATIC) config
);

FUNC(Std_ReturnType, NVM_CODE) Nvm_WriteBlock(
    VAR(uint8, NVM_VAR) blockId,
    P2CONST(uint8, NVM_CONST, AUTOMATIC) data,
    VAR(uint16, NVM_VAR) length
);

FUNC(Std_ReturnType, NVM_CODE) Nvm_ReadBlock(
    VAR(uint8, NVM_VAR) blockId,
    P2VAR(uint8, NVM_VAR, AUTOMATIC) data,
    P2VAR(uint16, NVM_VAR, AUTOMATIC) length
);

#endif /* NVM_H */