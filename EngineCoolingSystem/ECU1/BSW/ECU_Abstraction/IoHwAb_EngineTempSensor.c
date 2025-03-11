#include "IoHwAb_EngineTempSensor.h"
#include "Compiler.h"
#include "Adc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/* Biến toàn cục mô phỏng */
STATIC VAR(uint16, IOHWAB_VAR) simulated_engine_temp = 75; // Nhiệt độ ban đầu
STATIC VAR(uint8, IOHWAB_VAR) is_initialized = 0;          // Trạng thái khởi tạo


/* Hàm khởi tạo cảm biến nhiệt độ động cơ */
FUNC(void, IOHWAB_CODE) IoHwAb_EngineTempSensor_Init(
    P2CONST(IoHwAb_EngineTempConfigType, IOHWAB_CONST, AUTOMATIC) config
) {
    if (config == NULL_PTR) {
        Det_ReportError(2, 0, 0, IOHWAB_E_PARAM_POINTER);
        return;
    }

    if (config->isEnabled) {
        VAR(Adc_ConfigType, AUTOMATIC) adc_config = {
            config->channel, 1, config->samplingTime, 1 // Rank 1, bật
        };
        Adc_Init(&adc_config);
        is_initialized = 1;
        printf("IoHwAb: Engine Temperature Sensor Initialized (Channel %d, Sampling Time %d)\n",
               config->channel, config->samplingTime);
    } else {
        is_initialized = 0;
        Det_ReportError(2, 0, 0, IOHWAB_E_PARAM_CONFIG);
    }
}

/* Hàm đọc giá trị nhiệt độ động cơ */
FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_EngineTempSensor_Read(
    P2VAR(uint16, IOHWAB_VAR, AUTOMATIC) engineTempValue
) {
    if (engineTempValue == NULL_PTR) {
        Det_ReportError(2, 0, 1, IOHWAB_E_PARAM_POINTER);
        return IOHWAB_NOT_OK;
    }

    VAR(uint16, AUTOMATIC) adc_value;
    if (Adc_ReadChannel(0, &adc_value) == E_OK) {
        *engineTempValue = IoHwAb_EngineTempSensor_SimulateNewTemperature();
        // printf("IoHwAb: Engine Temperature Read = %d°C\n", *engineTempValue);
        return IOHWAB_OK;
    } else {
        Det_ReportError(2, 0, 1, IOHWAB_E_READ_FAILED);
        return IOHWAB_NOT_OK;
    }
}

/* Hàm mô phỏng thay đổi giá trị nhiệt độ động cơ */
FUNC(uint16, IOHWAB_CODE) IoHwAb_EngineTempSensor_SimulateNewTemperature(void) {
    return simulated_engine_temp = MIN_TEMP + (rand() % (MAX_TEMP - MIN_TEMP + 1));;
    
}