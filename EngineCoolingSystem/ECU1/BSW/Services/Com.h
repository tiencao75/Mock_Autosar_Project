#ifndef COM_H
#define COM_H

#include "Compiler.h"    // Thêm Compiler.h
#include "Std_Types.h"   // Kiểu dữ liệu chuẩn AUTOSAR
#include "Det.h"         // Báo lỗi phát triển

/* Trạng thái trả về cho Com */
#define COM_OK       E_OK
#define COM_NOT_OK   E_NOT_OK

/* Định nghĩa các mã lỗi */
#define COM_E_PARAM_POINTER    0x01U  // Lỗi con trỏ NULL
#define COM_E_PARAM_CONFIG     0x02U  // Lỗi cấu hình
#define COM_E_NOT_INITIALIZED  0x03U  // Lỗi chưa khởi tạo

/* Cấu trúc cấu hình cho Com */
typedef struct {
    VAR(uint8, COM_VAR) comChannel;    // Kênh giao tiếp
    VAR(uint8, COM_VAR) signalId;      // ID tín hiệu
    VAR(boolean, COM_VAR) isEnabled;   // Trạng thái bật/tắt
} Com_ConfigType;

/* Kiểu dữ liệu cho tín hiệu giao tiếp */
typedef struct {
    VAR(uint16, COM_VAR) signalValue;  // Giá trị tín hiệu
    VAR(uint8, COM_VAR) signalId;      // ID của tín hiệu
} Com_SignalType;

/* Khai báo hàm */
FUNC(void, COM_CODE) Com_Init(
    P2CONST(Com_ConfigType, COM_CONST, AUTOMATIC) config
);

FUNC(Std_ReturnType, COM_CODE) Com_SendSignal(
    P2VAR(Com_SignalType, COM_VAR, AUTOMATIC) signal
);

FUNC(Std_ReturnType, COM_CODE) Com_ReceiveSignal(
    P2VAR(Com_SignalType, COM_VAR, AUTOMATIC) signal
);

#endif /* COM_H */