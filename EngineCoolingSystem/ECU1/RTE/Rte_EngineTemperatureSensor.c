#include "Rte_EngineTemperatureSensor.h"
#include <stdio.h>

// Biến toàn cục mô phỏng cấu hình và trạng thái
static uint8 is_initialized = 0;         // Trạng thái khởi tạo

// Hàm khởi tạo RTE cho EngineTemperatureSensor
void Rte_EngineTempSensor_Init(const Rte_EngineTempSensorConfigType* config) {
    if (config == NULL_PTR) {
        Det_ReportError(8, 0, 0, RTE_E_PARAM_POINTER); // Báo lỗi AUTOSAR
        return;
    }

    if (config->isEnabled) {
        is_initialized = 1;
        // Mô phỏng khởi tạo cảm biến nhiệt độ động cơ qua ECU Abstraction
        IoHwAb_EngineTempConfigType io_config = {0, 10, 1}; // Kênh 0, SamplingTime 10, bật
        IoHwAb_EngineTempSensor_Init(&io_config);
        printf("Rte: EngineTemperatureSensor Initialized\n");
    } else {
        is_initialized = 0;
        Det_ReportError(8, 0, 0, RTE_E_PARAM_CONFIG);
    }
}

// Hàm đọc nhiệt độ động cơ (gửi qua RTE)
Std_ReturnType Rte_ReadEngineTemperature(Rte_EngineTempValueType* engineTemp) {
    if (!is_initialized) {
        Det_ReportError(8, 0, 1, RTE_E_NOT_INITIALIZED);
        return RTE_NOT_OK;
    }

    if (engineTemp == NULL_PTR) {
        Det_ReportError(8, 0, 1, RTE_E_PARAM_POINTER);
        return RTE_NOT_OK;
    }

    // Gọi ECU Abstraction để đọc nhiệt độ động cơ (mô phỏng)
    uint16 temp_value;
    if (IoHwAb_EngineTempSensor_Read(&temp_value) == IOHWAB_OK) {
        *engineTemp = temp_value;
        printf("Rte: Read Engine Temperature = %d°C\n", *engineTemp);
        return RTE_OK;
    } else {
        Det_ReportError(8, 0, 1, RTE_E_READ_FAILED);
        return RTE_NOT_OK;
    }
}

// Hàm mô phỏng thay đổi giá trị nhiệt độ động cơ (cho mục đích kiểm tra)
void Rte_SimulateNewEngineTemperature(uint16 new_temp) {
    IoHwAb_EngineTempSensor_SimulateNewTemperature(new_temp);
    printf("Rte: Engine Temperature Simulated to %d°C\n", new_temp);
}

// Hàm main để kiểm tra (chỉ dùng khi compile riêng)
#ifdef TEST_RTE_SENSOR
int main(void) {
    Rte_EngineTempSensorConfigType config = {1}; // Bật
    Rte_EngineTempValueType engine_temp;

    Rte_EngineTempSensor_Init(&config);

    if (Rte_ReadEngineTemperature(&engine_temp) == RTE_OK) {
        printf("Engine Temperature = %d°C\n", engine_temp);
    }

    Rte_SimulateNewEngineTemperature(85);

    if (Rte_ReadEngineTemperature(&engine_temp) == RTE_OK) {
        printf("Updated Engine Temperature = %d°C\n", engine_temp);
    }

    return 0;
}
#endif