#include "IoHwAb_EngineTempActuator.h"
#include "Compiler.h"  // Thêm Compiler.h
#include "Pwm.h"       // Giao tiếp với MCAL PWM
#include "Com.h"
#include <stdio.h>

/* Biến toàn cục mô phỏng trạng thái */
STATIC VAR(IoHwAb_EngineTempActuatorConfigType, IOHWAB_VAR) actuator_config = {0};
STATIC VAR(uint8, IOHWAB_VAR) is_initialized = 0;

/* Hàm khởi tạo actuator nhiệt độ động cơ */
FUNC(void, IOHWAB_CODE) IoHwAb_InitEngineTempActuator(
    P2CONST(IoHwAb_EngineTempActuatorConfigType, IOHWAB_CONST, AUTOMATIC) config
) {
    if (config == NULL_PTR) {
        Det_ReportError(12, 0, 0, IOHWAB_ACTUATOR_E_PARAM_POINTER);
        return;
    }

    if (config->isEnabled) {
        is_initialized = 1;
        actuator_config = *config;

        // Không cần khởi tạo kênh cố định nữa, vì channelId sẽ được truyền từ SWC
        // printf("IoHwAb: Engine Temperature Actuator Initialized (Initial Fan Duty %d%%, Initial Pump Duty %d%%)\n",
            //    config->initialFanDuty, config->initialPumpDuty);
    } else {
        is_initialized = 0;
        Det_ReportError(12, 0, 0, IOHWAB_ACTUATOR_E_PARAM_CONFIG);
    }
}

/* Hàm điều chỉnh tốc độ quạt */
FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_ChangeSpeedEngineFan(
    VAR(Pwm_ChannelType, IOHWAB_VAR) channelId,  // Thêm channelId
    VAR(uint8, IOHWAB_VAR) dutyCycle
) {
    // if (!is_initialized) {
    //     Det_ReportError(12, 0, 1, IOHWAB_ACTUATOR_E_NOT_INITIALIZED);
    //     return IOHWAB_ACTUATOR_NOT_OK;
    // }

    if (dutyCycle < PWM_DUTY_MIN || dutyCycle > PWM_DUTY_MAX) {
        Det_ReportError(12, 0, 1, IOHWAB_ACTUATOR_E_PARAM_DUTYCYCLE);
        return IOHWAB_ACTUATOR_NOT_OK;
    }

    if (Pwm_SetDutyCycle(channelId, dutyCycle) == PWM_OK) {
        // printf("IoHwAb: Changed Engine Fan Speed on Channel %d to %d%%\n", channelId, dutyCycle);
        return IOHWAB_ACTUATOR_OK;
    } else {
        Det_ReportError(12, 0, 1, IOHWAB_ACTUATOR_E_PARAM_CHANNEL);
        return IOHWAB_ACTUATOR_NOT_OK;
    }
}

/* Hàm điều chỉnh tốc độ bơm */
FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_ChangeSpeedEnginePump(
    VAR(Pwm_ChannelType, IOHWAB_VAR) channelId,  // Thêm channelId
    VAR(uint8, IOHWAB_VAR) dutyCycle
) {
    // if (!is_initialized) {
    //     Det_ReportError(12, 0, 2, IOHWAB_ACTUATOR_E_NOT_INITIALIZED);
    //     return IOHWAB_ACTUATOR_NOT_OK;
    // }

    if (dutyCycle < PWM_DUTY_MIN || dutyCycle > PWM_DUTY_MAX) {
        Det_ReportError(12, 0, 2, IOHWAB_ACTUATOR_E_PARAM_DUTYCYCLE);
        return IOHWAB_ACTUATOR_NOT_OK;
    }

    if (Pwm_SetDutyCycle(channelId, dutyCycle) == PWM_OK) {
        // printf("IoHwAb: Changed Engine Pump Speed on Channel %d to %d%%\n", channelId, dutyCycle);
        return IOHWAB_ACTUATOR_OK;
    } else {
        Det_ReportError(12, 0, 2, IOHWAB_ACTUATOR_E_PARAM_CHANNEL);
        return IOHWAB_ACTUATOR_NOT_OK;
    }
}

/* Hàm thay đổi trạng thái đèn cảnh báo nhiệt độ động cơ */
FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_ChangeEngineTemperatureWarningLight(
    VAR(Dio_ChannelType, IOHWAB_VAR) channelId,  // Thêm channelId
    VAR(uint8, IOHWAB_VAR) state
) {
    // if (!is_initialized) {
    //     Det_ReportError(12, 0, 3, IOHWAB_ACTUATOR_E_NOT_INITIALIZED);
    //     return IOHWAB_ACTUATOR_NOT_OK;
    // }

    // Điều khiển đèn cảnh báo bằng DIO: HIGH (bật) hoặc LOW (tắt)
    Dio_LevelType level = (state == 1) ? STD_HIGH : STD_LOW;

    // Ghi trạng thái vào kênh DIO
    if (Dio_WriteChannel(channelId, level) == DIO_OK) {
        // printf("IoHwAb: Engine Temperature Warning Light on Channel %d %s\n", channelId, (state == 1) ? "ON" : "OFF");
        return IOHWAB_ACTUATOR_OK;
    } else {
        Det_ReportError(12, 0, 3, IOHWAB_ACTUATOR_E_PARAM_CHANNEL);
        return IOHWAB_ACTUATOR_NOT_OK;
    }
}

/* Hàm đọc tín hiệu điều khiển từ phần cứng */
FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_ReadControlSignal(
    P2VAR(uint8, IOHWAB_VAR, AUTOMATIC) signal
) {
    // if (!is_initialized) {
    //     Det_ReportError(12, 0, 4, IOHWAB_ACTUATOR_E_NOT_INITIALIZED);
    //     return IOHWAB_ACTUATOR_NOT_OK;
    // }

    if (signal == NULL_PTR) {
        Det_ReportError(12, 0, 4, IOHWAB_ACTUATOR_E_PARAM_POINTER);
        return IOHWAB_ACTUATOR_NOT_OK;
    }

    // Giả lập tín hiệu điều khiển (thay bằng đọc thực tế từ ADC/DIO nếu cần)
    *signal = 50; // Giá trị giả lập (0-100%)
    // printf("IoHwAb: Read Control Signal = %d%%\n", *signal);
    return IOHWAB_ACTUATOR_OK;
}