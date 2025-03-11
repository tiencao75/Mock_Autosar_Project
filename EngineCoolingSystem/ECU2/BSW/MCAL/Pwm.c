#include "Pwm.h"
#include "Compiler.h"  // Thêm Compiler.h

/* Biến toàn cục mô phỏng trạng thái PWM */
STATIC VAR(uint8, PWM_VAR) pwm_duty_cycles[2] = {0};        // Mô phỏng 2 kênh (quạt và bơm), duty cycle mặc định 0
STATIC VAR(uint8, PWM_VAR) is_initialized = 0;              // Trạng thái khởi tạo
volatile VAR(uint8, PWM_VAR) last_pwm_duty_cycle_channel0 = 0; // Biến toàn cục lưu giá trị trước đó của kênh 0
volatile VAR(uint8, PWM_VAR) last_pwm_duty_cycle_channel1 = 0; // Biến toàn cục lưu giá trị trước đó của kênh 1

/* Hàm khởi tạo module Pwm */
FUNC(void, PWM_CODE) Pwm_Init(
    P2CONST(Pwm_ConfigType, PWM_CONST, AUTOMATIC) config
) {
    if (config == NULL_PTR) {
        Det_ReportError(11, 0, 0, PWM_E_PARAM_POINTER);
        return;
    }

    if (config->isEnabled) {
        is_initialized = 1;
        if (config->channelId < 2) { // Giả định chỉ hỗ trợ 2 kênh (quạt và bơm)
            pwm_duty_cycles[config->channelId] = config->initialDutyCycle;
            if (config->channelId == 0) {
                last_pwm_duty_cycle_channel0 = pwm_duty_cycles[0]; // Lưu giá trị ban đầu cho kênh 0
            } else {
                last_pwm_duty_cycle_channel1 = pwm_duty_cycles[1]; // Lưu giá trị ban đầu cho kênh 1
            }
        } else {
            Det_ReportError(11, 0, 0, PWM_E_PARAM_CHANNEL);
        }
    } else {
        is_initialized = 0;
        Det_ReportError(11, 0, 0, PWM_E_PARAM_CONFIG);
    }
}

/* Hàm đặt duty cycle cho kênh PWM */
FUNC(Std_ReturnType, PWM_CODE) Pwm_SetDutyCycle(
    VAR(Pwm_ChannelType, PWM_VAR) channelId,
    VAR(uint8, PWM_VAR) dutyCycle
) {
    // if (!is_initialized) {
    //     Det_ReportError(11, 0, 1, PWM_E_NOT_INITIALIZED);
    //     return PWM_NOT_OK;
    // }

    // if (channelId >= 2) {
    //     Det_ReportError(11, 0, 1, PWM_E_PARAM_CHANNEL);
    //     return PWM_NOT_OK;
    // }

    // if (dutyCycle < PWM_DUTY_MIN || dutyCycle > PWM_DUTY_MAX) {
    //     Det_ReportError(11, 0, 1, PWM_E_PARAM_DUTYCYCLE);
    //     return PWM_NOT_OK;
    // }

    // Lưu giá trị hiện tại vào biến tương ứng trước khi cập nhật
    if (channelId == 0) {
        last_pwm_duty_cycle_channel0 = dutyCycle;
    } else {
        last_pwm_duty_cycle_channel1 = dutyCycle;
    }
    pwm_duty_cycles[channelId] = dutyCycle; // Cập nhật duty cycle mới

    return PWM_OK;
}

/* Hàm đọc duty cycle của kênh PWM */
FUNC(uint8, PWM_CODE) Pwm_GetDutyCycle(
    VAR(Pwm_ChannelType, PWM_VAR) channelId
) {
    if (!is_initialized) {
        Det_ReportError(11, 0, 2, PWM_E_NOT_INITIALIZED);
        return PWM_DUTY_MIN; // Trả về 0 nếu lỗi
    }

    if (channelId >= 2) {
        Det_ReportError(11, 0, 2, PWM_E_PARAM_CHANNEL);
        return PWM_DUTY_MIN;
    }

    return pwm_duty_cycles[channelId];
}

/* Hàm đọc duty cycle trước đó */
FUNC(uint8, PWM_CODE) Pwm_GetLastDutyCycle(
    VAR(Pwm_ChannelType, PWM_VAR) channelId
) {
    if (!is_initialized) {
        Det_ReportError(11, 0, 3, PWM_E_NOT_INITIALIZED);
        return PWM_DUTY_MIN; // Trả về 0 nếu lỗi
    }

    if (channelId >= 2) {
        Det_ReportError(11, 0, 3, PWM_E_PARAM_CHANNEL);
        return PWM_DUTY_MIN;
    }

    return (channelId == 0) ? last_pwm_duty_cycle_channel0 : last_pwm_duty_cycle_channel1;
}

/* Hàm main để kiểm tra */
#ifdef TEST_PWM
FUNC(int, PWM_CODE) main(void) {
    VAR(Pwm_ConfigType, AUTOMATIC) config = {0, 1000, 50, 1}; // Channel 0, Freq 1000 Hz, Duty 50%, bật
    VAR(uint8, AUTOMATIC) duty;
    VAR(uint8, AUTOMATIC) last_duty;

    Pwm_Init(&config);

    // Đặt duty cycle 80% cho kênh 0
    Pwm_SetDutyCycle(0, 80);

    // Đọc duty cycle hiện tại
    duty = Pwm_GetDutyCycle(0);
    // Đọc duty cycle trước đó
    last_duty = Pwm_GetLastDutyCycle(0);

    // In kết quả để kiểm tra (giả định)
    // printf("Current Duty: %d, Last Duty: %d\n", duty, last_duty);

    return 0;
}
#endif