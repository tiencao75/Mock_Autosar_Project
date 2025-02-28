#include "IoHwAb_AirTempSensor.h"
#include "Adc.h" // Gọi MCAL để đọc giá trị ADC
#include <stdio.h>

// Biến toàn cục mô phỏng giá trị nhiệt độ không khí
static uint16 simulated_air_temp = 25; // Giá trị nhiệt độ không khí ban đầu (độ C)
static uint8 is_initialized = 0;       // Trạng thái khởi tạo

// Hàm khởi tạo cảm biến nhiệt độ không khí
void IoHwAb_AirTempSensor_Init(const IoHwAb_AirTempConfigType* config) {
    if (config == NULL_PTR) {
        Det_ReportError(1, 0, 0, IOHWAB_E_PARAM_POINTER); // Báo lỗi AUTOSAR
        return;
    }

    if (config->isEnabled) {
        // Mô phỏng khởi tạo bằng cách gọi MCAL (Adc_Init)
        Adc_ConfigType adc_config = {
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

// Hàm đọc giá trị nhiệt độ không khí
Std_ReturnType IoHwAb_AirTempSensor_Read(uint16* airTempValue) {
    if (!is_initialized) {
        Det_ReportError(1, 0, 1, IOHWAB_E_NOT_INITIALIZED);
        return IOHWAB_NOT_OK;
    }

    if (airTempValue == NULL_PTR) {
        Det_ReportError(1, 0, 1, IOHWAB_E_PARAM_POINTER);
        return IOHWAB_NOT_OK;
    }

    // Gọi MCAL (Adc) để đọc giá trị từ kênh ADC (mô phỏng)
    uint16 adc_value;
    if (Adc_ReadChannel(0, &adc_value) == E_OK) {
        *airTempValue = simulated_air_temp; // Sử dụng giá trị mô phỏng
        printf("IoHwAb: Air Temperature Read = %d°C\n", *airTempValue);
        return IOHWAB_OK;
    } else {
        Det_ReportError(1, 0, 1, IOHWAB_E_READ_FAILED);
        return IOHWAB_NOT_OK;
    }
}

// Hàm mô phỏng thay đổi giá trị nhiệt độ không khí (cho mục đích kiểm tra)
void IoHwAb_AirTempSensor_SimulateNewTemperature(uint16 new_temp) {
    simulated_air_temp = new_temp;
    printf("IoHwAb: Air Temperature Simulated to %d°C\n", simulated_air_temp);
}