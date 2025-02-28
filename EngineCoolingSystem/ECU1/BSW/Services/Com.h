#ifndef COM_H
#define COM_H

#include "Std_Types.h" // Bao gồm các kiểu dữ liệu AUTOSAR
#include "Det.h"       // Báo lỗi phát triển

// Trạng thái trả về cho Com
#define COM_OK       E_OK
#define COM_NOT_OK   E_NOT_OK

// Định nghĩa các mã lỗi cho Com
#define COM_E_PARAM_POINTER    0x01U  // Lỗi con trỏ NULL
#define COM_E_PARAM_CONFIG     0x02U  // Lỗi cấu hình
#define COM_E_NOT_INITIALIZED  0x03U  // Lỗi chưa khởi tạo

// Định nghĩa cấu hình cho Com
typedef struct {
    uint8 comChannel;    // Kênh giao tiếp (ví dụ: CAN channel)
    uint8 signalId;      // ID tín hiệu
    boolean isEnabled;   // Trạng thái bật/tắt
} Com_ConfigType;

// Định nghĩa kiểu dữ liệu cho tín hiệu giao tiếp
typedef struct {
    uint16 signalValue;  // Giá trị tín hiệu (ví dụ: nhiệt độ động cơ)
    uint8 signalId;      // ID của tín hiệu
} Com_SignalType;

// Hàm khởi tạo module Com
void Com_Init(const Com_ConfigType* config);

// Hàm gửi tín hiệu giao tiếp (mô phỏng)
Std_ReturnType Com_SendSignal(Com_SignalType* signal);

// Hàm nhận tín hiệu giao tiếp (mô phỏng)
Std_ReturnType Com_ReceiveSignal(Com_SignalType* signal);

#endif // COM_H