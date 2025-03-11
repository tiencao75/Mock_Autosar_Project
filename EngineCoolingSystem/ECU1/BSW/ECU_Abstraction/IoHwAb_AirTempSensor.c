#include "IoHwAb_AirTempSensor.h"
#include "Compiler.h"  // Thêm Compiler.h
#include "Adc.h"       // Gọi MCAL để đọc giá trị ADC
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Biến toàn cục mô phỏng */
STATIC VAR(uint16, IOHWAB_VAR) simulated_air_temp = 25; // Nhiệt độ ban đầu
STATIC VAR(uint8, IOHWAB_VAR) is_initialized = 0;       // Trạng thái khởi tạo

/* Hàm khởi tạo cảm biến nhiệt độ không khí */
FUNC(void, IOHWAB_CODE) IoHwAb_AirTempSensor_Init(
    P2CONST(IoHwAb_AirTempConfigType, IOHWAB_CONST, AUTOMATIC) config
) {
    if (config == NULL_PTR) {
        Det_ReportError(1, 0, 0, IOHWAB_E_PARAM_POINTER);
        return;
    }

    if (config->isEnabled) {
        VAR(Adc_ConfigType, AUTOMATIC) adc_config = {
            config->channel, 1, config->samplingTime, 1 // Rank 1, bật
        };
        Adc_Init(&adc_config);
        is_initialized = 1;
        printf("IoHwAb: Air Temperature Sensor Initialized (Channel %d, Sampling Time %d)\n",
               config->channel, config->samplingTime);
    } else {
        is_initialized = 0;
        Det_ReportError(1, 0, 0, IOHWAB_E_PARAM_CONFIG);
    }
}

/* Hàm đọc giá trị nhiệt độ không khí */
FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_AirTempSensor_Read(
    P2VAR(uint16, IOHWAB_VAR, AUTOMATIC) airTempValue
) {
    if (airTempValue == NULL_PTR) {
        Det_ReportError(1, 0, 1, IOHWAB_E_PARAM_POINTER);
        return IOHWAB_NOT_OK;
    }

    VAR(uint16, AUTOMATIC) adc_value;
    if (Adc_ReadChannel(0, &adc_value) == E_OK) {
        *airTempValue = IoHwAb_AirTempSensor_SimulateNewTemperature();
        //printf("IoHwAb: Air Temperature Read = %d°C\n", *airTempValue);
        return IOHWAB_OK;
    } else {
        Det_ReportError(1, 0, 1, IOHWAB_E_READ_FAILED);
        return IOHWAB_NOT_OK;
    }
}

/* Hàm mô phỏng thay đổi giá trị nhiệt độ động cơ */
FUNC(uint16, IOHWAB_CODE) IoHwAb_AirTempSensor_SimulateNewTemperature(void) {
    return simulated_air_temp = MIN_AIR_TEMP + (rand() % (MAX_AIR_TEMP - MIN_AIR_TEMP + 1));;
    
}