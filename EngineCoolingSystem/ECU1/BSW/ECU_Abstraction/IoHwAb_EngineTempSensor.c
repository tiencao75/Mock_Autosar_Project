#include "IoHwAb_EngineTempSensor.h"
#include "Adc.h" // Gọi MCAL để đọc giá trị ADC
#include <stdio.h>

// Biến toàn cục mô phỏng giá trị nhiệt độ động cơ
static uint16 simulated_engine_temp = 75; // Giá trị nhiệt độ động cơ ban đầu (độ C)
static uint8 is_initialized = 0;         // Trạng thái khởi tạo

// Hàm khởi tạo cảm biến nhiệt độ động cơ
void IoHwAb_EngineTempSensor_Init(const IoHwAb_EngineTempConfigType* config) {
    if (config == NULL_PTR) {
        Det_ReportError(2, 0, 0, IOHWAB_E_PARAM_POINTER); // Báo lỗi AUTOSAR
        return;
    }

    if (config->isEnabled) {
        // Mô phỏng khởi tạo bằng cách gọi MCAL (Adc_Init)
        Adc_ConfigType adc_config = {
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

// Hàm đọc giá trị nhiệt độ động cơ
Std_ReturnType IoHwAb_EngineTempSensor_Read(uint16* engineTempValue) {
    if (!is_initialized) {
        Det_ReportError(2, 0, 1, IOHWAB_E_NOT_INITIALIZED);
        return IOHWAB_NOT_OK;
    }

    if (engineTempValue == NULL_PTR) {
        Det_ReportError(2, 0, 1, IOHWAB_E_PARAM_POINTER);
        return IOHWAB_NOT_OK;
    }

    // Gọi MCAL (Adc) để đọc giá trị từ kênh ADC (mô phỏng)
    uint16 adc_value;
    if (Adc_ReadChannel(0, &adc_value) == E_OK) {
        *engineTempValue = simulated_engine_temp; // Sử dụng giá trị mô phỏng
        printf("IoHwAb: Engine Temperature Read = %d°C\n", *engineTempValue);
        return IOHWAB_OK;
    } else {
        Det_ReportError(2, 0, 1, IOHWAB_E_READ_FAILED);
        return IOHWAB_NOT_OK;
    }
}

// Hàm mô phỏng thay đổi giá trị nhiệt độ động cơ (cho mục đích kiểm tra)
void IoHwAb_EngineTempSensor_SimulateNewTemperature(uint16 new_temp) {
    simulated_engine_temp = new_temp;
    printf("IoHwAb: Engine Temperature Simulated to %d°C\n", simulated_engine_temp);
}