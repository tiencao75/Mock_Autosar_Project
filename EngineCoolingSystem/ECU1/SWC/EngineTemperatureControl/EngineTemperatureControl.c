#include "EngineTemperatureControl.h"
#include "Rte_EngineTemperatureControl.h"   // Giao tiếp với RTE
#include "Rte_EngineTemperatureSensor.h"    // Giao tiếp với EngineTemperatureSensor RTE
#include "Com.h"                           // Giao tiếp với Services (Com)
#include "Std_Types.h"                     // Kiểu dữ liệu AUTOSAR
#include "Det.h"                          // Báo lỗi AUTOSAR
#include <stdio.h>

// Biến toàn cục mô phỏng trạng thái
static uint8 is_initialized = 0;

// Hàm khởi tạo SWC EngineTemperatureControl
void EngineTemperatureControl_Init(void) {
    Rte_EngineTempControlConfigType config = {1}; // Bật
    if (&config == NULL_PTR) { // Sửa lỗi: kiểm tra con trỏ config
        Det_ReportError(11, 0, 0, RTE_E_PARAM_POINTER); // Báo lỗi AUTOSAR
        return;
    }

    Rte_EngineTempControl_Init(&config);
    is_initialized = 1;
    printf("EngineTemperatureControl: Initialized\n");

    // Mô phỏng khởi tạo module Com để gửi tín hiệu
    Com_ConfigType com_config = {0, 1, 1}; // Channel 0, Signal ID 1, bật
    Com_Init(&com_config);
}

// Hàm đọc nhiệt độ động cơ từ EngineTemperatureSensor
Std_ReturnType EngineTemperatureControl_GetEngineTemperature(uint16* engineTemp) {
    if (!is_initialized) {
        Det_ReportError(11, 0, 1, RTE_E_NOT_INITIALIZED);
        return RTE_NOT_OK;
    }

    if (engineTemp == NULL_PTR) {
        Det_ReportError(11, 0, 1, RTE_E_PARAM_POINTER);
        return RTE_NOT_OK;
    }

    // Gọi RTE để đọc nhiệt độ động cơ từ EngineTemperatureSensor
    Rte_EngineTempValueType temp_value;
    if (Rte_ReadEngineTemperature(&temp_value) == RTE_OK) {
        *engineTemp = temp_value;
        printf("EngineTemperatureControl: Read Engine Temperature = %d°C\n", *engineTemp);
        return RTE_OK;
    } else {
        Det_ReportError(11, 0, 1, RTE_E_READ_FAILED);
        return RTE_NOT_OK;
    }
}

// Hàm gửi tín hiệu điều khiển
Std_ReturnType EngineTemperatureControl_SendControlSignal(uint8 controlSignal) {
    if (!is_initialized) {
        Det_ReportError(11, 0, 2, RTE_E_NOT_INITIALIZED);
        return RTE_NOT_OK;
    }

    // Mô phỏng gửi tín hiệu qua RTE và Com
    Rte_ControlSignalType rte_signal = controlSignal;
    if (Rte_SendControlSignal(rte_signal) == RTE_OK) {
        printf("EngineTemperatureControl: Sent Control Signal = %d\n", controlSignal);
        return RTE_OK;
    } else {
        Det_ReportError(11, 0, 2, RTE_E_SEND_FAILED);
        return RTE_NOT_OK;
    }
}

// Hàm điều khiển logic (mô phỏng)
void EngineTemperatureControl_Process(void) {
    uint16 engine_temp;
    if (EngineTemperatureControl_GetEngineTemperature(&engine_temp) == RTE_OK) {
        if (engine_temp > 80) { // Ngưỡng nhiệt độ để bật điều khiển
            EngineTemperatureControl_SendControlSignal(1); // Bật tín hiệu (ON)
        } else if (engine_temp < 60) { // Ngưỡng nhiệt độ để tắt điều khiển
            EngineTemperatureControl_SendControlSignal(0); // Tắt tín hiệu (OFF)
        }
    }
}

// Hàm main để kiểm tra (chỉ dùng khi compile riêng)
#ifdef TEST_ENGINE_CONTROL
int main(void) {
    uint16 engine_temp;

    EngineTemperatureControl_Init();

    if (EngineTemperatureControl_GetEngineTemperature(&engine_temp) == RTE_OK) {
        printf("Engine Temperature = %d°C\n", engine_temp);
    }

    EngineTemperatureControl_Process(); // Thực hiện logic điều khiển

    // Kiểm tra với nhiệt độ cao
    Rte_SimulateNewEngineTemperature(85); // Tăng nhiệt độ để kiểm tra
    if (EngineTemperatureControl_GetEngineTemperature(&engine_temp) == RTE_OK) {
        printf("Updated Engine Temperature = %d°C\n", engine_temp);
    }
    EngineTemperatureControl_Process();

    return 0;
}
#endif