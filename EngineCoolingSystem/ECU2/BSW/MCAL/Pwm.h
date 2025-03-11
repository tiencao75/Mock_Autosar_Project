#ifndef PWM_H
#define PWM_H

#include "Compiler.h"    // Thêm Compiler.h
#include "Std_Types.h"   // Kiểu dữ liệu chuẩn AUTOSAR
#include "Det.h"  
#include "Dio.h"// Báo lỗi phát triển

/* Trạng thái trả về cho Pwm */
#define PWM_OK       E_OK
#define PWM_NOT_OK   E_NOT_OK

/* Định nghĩa các mã lỗi */
#define PWM_E_PARAM_POINTER    0x01U  // Lỗi con trỏ NULL
#define PWM_E_PARAM_CONFIG     0x02U  // Lỗi cấu hình
#define PWM_E_NOT_INITIALIZED  0x03U  // Lỗi chưa khởi tạo
#define PWM_E_PARAM_CHANNEL    0x04U  // Lỗi kênh không hợp lệ
#define PWM_E_PARAM_DUTYCYCLE  0x05U  // Lỗi duty cycle không hợp lệ

/* Cấu trúc cấu hình cho Pwm */
typedef struct {
    VAR(Dio_ChannelType, PWM_VAR) channelId;    // ID kênh PWM (liên kết với Dio cho chân GPIO)
    VAR(uint16, PWM_VAR) frequency;             // Tần số PWM (Hz)
    VAR(uint8, PWM_VAR) initialDutyCycle;       // Duty cycle ban đầu (0-100%)
    VAR(boolean, PWM_VAR) isEnabled;            // Trạng thái bật/tắt
} Pwm_ConfigType;

/* Định nghĩa kiểu kênh Pwm (sử dụng Dio_ChannelType) */
typedef VAR(Dio_ChannelType, PWM_VAR) Pwm_ChannelType;

/* Định nghĩa phạm vi duty cycle */
#define PWM_DUTY_MIN 0U    // Duty cycle tối thiểu
#define PWM_DUTY_MAX 100U  // Duty cycle tối đa

/* Khai báo hàm */
FUNC(void, PWM_CODE) Pwm_Init(
    P2CONST(Pwm_ConfigType, PWM_CONST, AUTOMATIC) config
);

FUNC(Std_ReturnType, PWM_CODE) Pwm_SetDutyCycle(
    VAR(Pwm_ChannelType, PWM_VAR) channelId,
    VAR(uint8, PWM_VAR) dutyCycle
);

FUNC(uint8, PWM_CODE) Pwm_GetDutyCycle(
    VAR(Pwm_ChannelType, PWM_VAR) channelId
);

#endif /* PWM_H */