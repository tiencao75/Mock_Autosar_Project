#include "EngineTemperatureSensor.h"
#include "Rte_EngineTemperatureSensor.h" // Giao tiếp với RTE
#include "IoHwAb_EngineTempSensor.h"     // Giao tiếp với ECU Abstraction
#include "Std_Types.h"                   // Kiểu dữ liệu AUTOSAR
#include "Det.h"                        // Báo lỗi AUTOSAR
#include <stdio.h>

// Biến toàn cục mô phỏng trạng thái
static uint8 is_initialized = 0;

// Hàm khởi tạo SWC EngineTemperatureSensor
void EngineTemperatureSensor_Init(void) {
    Rte_EngineTempSensorConfigType config = {1}; // Bật
    if (&config == NULL_PTR) { // Sửa lỗi: kiểm tra con trỏ config
        Det_ReportError(10, 0, 0, RTE_E_PARAM_POINTER); // Báo lỗi AUTOSAR
        return;
    }

    Rte_EngineTempSensor_Init(&config);
    is_initialized = 1;
    printf("EngineTemperatureSensor: Initialized\n");

    // Mô phỏng khởi tạo cảm biến qua ECU Abstraction
    IoHwAb_EngineTempConfigType io_config = {0, 10, 1}; // Kênh 0, SamplingTime 10, bật
    IoHwAb_EngineTempSensor_Init(&io_config);
}

// Hàm đọc nhiệt độ động cơ
Std_ReturnType EngineTemperatureSensor_GetTemperature(uint16* engineTemp) {
    if (!is_initialized) {
        Det_ReportError(10, 0, 1, RTE_E_NOT_INITIALIZED);
        return RTE_NOT_OK;
    }

    if (engineTemp == NULL_PTR) {
        Det_ReportError(10, 0, 1, RTE_E_PARAM_POINTER);
        return RTE_NOT_OK;
    }

    // Gọi RTE để đọc nhiệt độ động cơ
    Rte_EngineTempValueType temp_value;
    if (Rte_ReadEngineTemperature(&temp_value) == RTE_OK) {
        *engineTemp = temp_value;
        printf("EngineTemperatureSensor: Read Engine Temperature = %d°C\n", *engineTemp);
        return RTE_OK;
    } else {
        Det_ReportError(10, 0, 1, RTE_E_READ_FAILED);
        return RTE_NOT_OK;
    }
}

// Hàm mô phỏng thay đổi giá trị nhiệt độ động cơ (cho mục đích kiểm tra)
void EngineTemperatureSensor_SimulateNewTemperature(uint16 new_temp) {
    Rte_SimulateNewEngineTemperature(new_temp);
    printf("EngineTemperatureSensor: Simulated Engine Temperature to %d°C\n", new_temp);
}

// Hàm main để kiểm tra (chỉ dùng khi compile riêng)
#ifdef TEST_ENGINE_SENSOR
int main(void) {
    uint16 engine_temp;

    EngineTemperatureSensor_Init();

    if (EngineTemperatureSensor_GetTemperature(&engine_temp) == RTE_OK) {
        printf("Engine Temperature = %d°C\n", engine_temp);
    }

    EngineTemperatureSensor_SimulateNewTemperature(85);

    if (EngineTemperatureSensor_GetTemperature(&engine_temp) == RTE_OK) {
        printf("Updated Engine Temperature = %d°C\n", engine_temp);
    }

    return 0;
}
#endif