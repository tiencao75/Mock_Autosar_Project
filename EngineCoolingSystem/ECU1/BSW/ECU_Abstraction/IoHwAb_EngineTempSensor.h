#ifndef IOHWAB_ENGINETEMPSENSOR_H
#define IOHWAB_ENGINETEMPSENSOR_H

#include "Compiler.h"    // Thêm Compiler.h
#include "Std_Types.h"   // Kiểu dữ liệu chuẩn AUTOSAR
#include "Det.h"         // Báo lỗi phát triển

/* Trạng thái trả về cho IoHwAb */
#define IOHWAB_OK       E_OK
#define IOHWAB_NOT_OK   E_NOT_OK

/* Định nghĩa các mã lỗi */
#define IOHWAB_E_PARAM_POINTER    0x01U  // Lỗi con trỏ NULL
#define IOHWAB_E_PARAM_CONFIG     0x02U  // Lỗi cấu hình
#define IOHWAB_E_NOT_INITIALIZED  0x03U  // Lỗi chưa khởi tạo
#define IOHWAB_E_READ_FAILED      0x04U  // Lỗi đọc dữ liệu

/* Cấu trúc cấu hình cho cảm biến nhiệt độ động cơ */
typedef struct {
    VAR(uint8, IOHWAB_VAR) channel;         // Kênh ADC
    VAR(uint8, IOHWAB_VAR) samplingTime;    // Thời gian lấy mẫu
    VAR(boolean, IOHWAB_VAR) isEnabled;     // Trạng thái bật/tắt
} IoHwAb_EngineTempConfigType;

/* Khai báo hàm */
FUNC(void, IOHWAB_CODE) IoHwAb_EngineTempSensor_Init(
    P2CONST(IoHwAb_EngineTempConfigType, IOHWAB_CONST, AUTOMATIC) config
);

FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_EngineTempSensor_Read(
    P2VAR(uint16, IOHWAB_VAR, AUTOMATIC) engineTempValue
);

#endif /* IOHWAB_ENGINETEMPSENSOR_H */