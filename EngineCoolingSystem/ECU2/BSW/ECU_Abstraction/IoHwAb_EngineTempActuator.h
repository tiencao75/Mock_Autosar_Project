#ifndef IOHWAB_ENGINETEMPACTUATOR_H
#define IOHWAB_ENGINETEMPACTUATOR_H

#include "Compiler.h"    // Thêm Compiler.h
#include "Std_Types.h"   // Kiểu dữ liệu chuẩn AUTOSAR
#include "Det.h"         // Báo lỗi phát triển
#include "Pwm.h"         // Giao tiếp với MCAL PWM (cho quạt và bơm)
#include "Dio.h"         // Giao tiếp với MCAL DIO (cho đèn cảnh báo)

#define IOHWAB_ACTUATOR_OK       E_OK
#define IOHWAB_ACTUATOR_NOT_OK   E_NOT_OK

/* Định nghĩa các mã lỗi */
#define IOHWAB_ACTUATOR_E_PARAM_POINTER    0x01U  // Lỗi con trỏ NULL
#define IOHWAB_ACTUATOR_E_PARAM_CONFIG     0x02U  // Lỗi cấu hình
#define IOHWAB_ACTUATOR_E_NOT_INITIALIZED  0x03U  // Lỗi chưa khởi tạo
#define IOHWAB_ACTUATOR_E_PARAM_DUTYCYCLE  0x04U  // Lỗi duty cycle không hợp lệ
#define IOHWAB_ACTUATOR_E_PARAM_STATE      0x05U  // Lỗi trạng thái không hợp lệ
#define IOHWAB_ACTUATOR_E_PARAM_CHANNEL    0x06U  // Thêm lỗi cho channelId không hợp lệ

/* Cấu trúc cấu hình cho actuator nhiệt độ động cơ */
typedef struct {
    VAR(uint8, IOHWAB_VAR) initialFanDuty;    // Duty cycle ban đầu cho quạt (0-100%)
    VAR(uint8, IOHWAB_VAR) initialPumpDuty;   // Duty cycle ban đầu cho bơm (0-100%)
    VAR(boolean, IOHWAB_VAR) isEnabled;       // Trạng thái bật/tắt
} IoHwAb_EngineTempActuatorConfigType;

/* Khai báo hàm */
FUNC(void, IOHWAB_CODE) IoHwAb_InitEngineTempActuator(
    P2CONST(IoHwAb_EngineTempActuatorConfigType, IOHWAB_CONST, AUTOMATIC) config
);

// Thêm channelId vào các hàm điều khiển
FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_ChangeSpeedEngineFan(
    VAR(Pwm_ChannelType, IOHWAB_VAR) channelId,  // Thêm channelId
    VAR(uint8, IOHWAB_VAR) dutyCycle
);

FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_ChangeSpeedEnginePump(
    VAR(Pwm_ChannelType, IOHWAB_VAR) channelId,  // Thêm channelId
    VAR(uint8, IOHWAB_VAR) dutyCycle
);

FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_ChangeEngineTemperatureWarningLight(
    VAR(Dio_ChannelType, IOHWAB_VAR) channelId,  // Thêm channelId
    VAR(uint8, IOHWAB_VAR) state
);

FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_ReadControlSignal(
    P2VAR(uint8, IOHWAB_VAR, AUTOMATIC) signal
);

#endif /* IOHWAB_ENGINETEMPACTUATOR_H */