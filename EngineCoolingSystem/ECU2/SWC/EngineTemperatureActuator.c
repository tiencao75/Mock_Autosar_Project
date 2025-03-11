#include "EngineTemperatureActuator.h"
#include "Compiler.h"
#include <stdio.h>

/* Biến toàn cục mô phỏng trạng thái */
STATIC VAR(EngineTempActuatorConfigType, SWC_VAR) swc_config = {0};
STATIC VAR(uint8, SWC_VAR) is_initialized = 0;
STATIC VAR(uint16, SWC_VAR) current_engine_temp = 75; /* Giả lập nhiệt độ động cơ */

/* Hàm khởi tạo SWC */
FUNC(void, SWC_CODE) EngineTemperatureActuator_Init(
    P2CONST(EngineTempActuatorConfigType, SWC_CONST, AUTOMATIC) config
) {
    if (config == NULL_PTR) {
        Det_ReportError(14, 0, 0, SWC_E_PARAM_POINTER);
        return;
    }
    if (config->isEnabled) {
        is_initialized = 1;
        swc_config = *config;
        current_engine_temp = 75;
    } else {
        is_initialized = 0;
        Det_ReportError(14, 0, 0, SWC_E_PARAM_CONFIG);
    }
}

/* Điều chỉnh tốc độ bơm */
FUNC(Std_ReturnType, SWC_CODE) ChangeSpeedEnginePump(
    VAR(Pwm_ChannelType, SWC_APPL_DATA) channelId,  // Thêm channelId
    VAR(uint8, SWC_APPL_DATA) dutyCycle
) {
    // if (!is_initialized) {
    //     Det_ReportError(14, 0, 1, SWC_E_NOT_INITIALIZED);
    //     return SWC_NOT_OK;
    // }
    // if (dutyCycle > PWM_DUTY_MAX) {
    //     Det_ReportError(14, 0, 1, SWC_E_PARAM_DUTYCYCLE);
    //     return SWC_NOT_OK;
    // }
    if (channelId >= 2) {  // Giả định chỉ hỗ trợ 2 kênh PWM, khớp với Pwm.c
        Det_ReportError(14, 0, 1, SWC_E_PARAM_CHANNEL);
        return SWC_NOT_OK;
    }
    if (Rte_ChangeSpeedEnginePump(channelId, dutyCycle) == RTE_OK) {
        // printf("SWC: Changed Pump Speed on Channel %d to %d%%\n", channelId, dutyCycle);
        return SWC_OK;
    } else {
        Det_ReportError(14, 0, 1, SWC_E_PARAM_DUTYCYCLE);
        return SWC_NOT_OK;
    }
}

/* Điều chỉnh tốc độ quạt */
FUNC(Std_ReturnType, SWC_CODE) ChangeSpeedEngineFan(
    VAR(Pwm_ChannelType, SWC_APPL_DATA) channelId,  // Thêm channelId
    VAR(uint8, SWC_APPL_DATA) dutyCycle
) {
    // if (!is_initialized) {
    //     Det_ReportError(14, 0, 2, SWC_E_NOT_INITIALIZED);
    //     return SWC_NOT_OK;
    // }
    // if (dutyCycle > PWM_DUTY_MAX) {
    //     Det_ReportError(14, 0, 2, SWC_E_PARAM_DUTYCYCLE);
    //     return SWC_NOT_OK;
    // }
    if (channelId >= 2) {  // Giả định chỉ hỗ trợ 2 kênh PWM, khớp với Pwm.c
        Det_ReportError(14, 0, 2, SWC_E_PARAM_CHANNEL);
        return SWC_NOT_OK;
    }
    if (Rte_ChangeSpeedEngineFan(channelId, dutyCycle) == RTE_OK) {
        // printf("SWC: Changed Fan Speed on Channel %d to %d%%\n", channelId, dutyCycle);
        return SWC_OK;
    } else {
        Det_ReportError(14, 0, 2, SWC_E_PARAM_DUTYCYCLE);
        return SWC_NOT_OK;
    }
}

/* Điều khiển đèn cảnh báo */
FUNC(Std_ReturnType, SWC_CODE) ChangeEngineTemperatureWarningLight(
    VAR(Dio_ChannelType, SWC_APPL_DATA) channelId,  // Thêm channelId
    VAR(Dio_LevelType, SWC_APPL_DATA) level
) {
    if (!is_initialized) {
        Det_ReportError(14, 0, 3, SWC_E_NOT_INITIALIZED);
        return SWC_NOT_OK;
    }
    if (level != DIO_LOW && level != DIO_HIGH) {
        Det_ReportError(14, 0, 3, SWC_E_PARAM_LEVEL);
        return SWC_NOT_OK;
    }
    if (channelId >= 8) {  // Giả định hỗ trợ 8 kênh DIO, khớp với Dio.c
        Det_ReportError(14, 0, 3, SWC_E_PARAM_CHANNEL);
        return SWC_NOT_OK;
    }
    if (Rte_ChangeEngineTemperatureWarningLight(channelId, level) == RTE_OK) {
        if (level == DIO_HIGH) {
            Dem_ReportEvent(3, 1);
        }
        printf("SWC: Set Warning Light on Channel %d to %s\n", channelId, (level == DIO_HIGH) ? "ON" : "OFF");
        return SWC_OK;
    } else {
        Det_ReportError(14, 0, 3, SWC_E_PARAM_LEVEL);
        return SWC_NOT_OK;
    }
}

/* Đọc tín hiệu điều khiển */
FUNC(Std_ReturnType, SWC_CODE) ReadControlSignal(
    P2VAR(Rte_ControlDataType, SWC_APPL_DATA, AUTOMATIC) data
) {
    if (data == NULL_PTR) {
        Det_ReportError(14, 0, 4, SWC_E_PARAM_SIGNAL);
        return SWC_NOT_OK;
    }
    if (Rte_ReadControlSignal(data) != RTE_OK) {
        Det_ReportError(14, 0, 4, SWC_E_PARAM_SIGNAL);
        return SWC_NOT_OK;
    }
    current_engine_temp = (data->warningStatus == 1) ? 90 : 50;  /* Giả lập nhiệt độ */
    return SWC_OK;
}