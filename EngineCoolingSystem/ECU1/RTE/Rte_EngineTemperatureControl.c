#include "Rte_EngineTemperatureControl.h"
#include <stdio.h>

// Biến toàn cục mô phỏng cấu hình và trạng thái
static uint8 is_initialized = 0;         // Trạng thái khởi tạo

// Hàm khởi tạo RTE cho EngineTemperatureControl
void Rte_EngineTempControl_Init(const Rte_EngineTempControlConfigType* config) {
    if (config == NULL_PTR) {
        Det_ReportError(9, 0, 0, RTE_E_PARAM_POINTER); // Báo lỗi AUTOSAR
        return;
    }

    if (config->isEnabled) {
        is_initialized = 1;
        // Mô phỏng khởi tạo module Com để gửi tín hiệu
        Com_ConfigType com_config = {0, 1, 1}; // Channel 0, Signal ID 1, bật
        Com_Init(&com_config);
        printf("Rte: EngineTemperatureControl Initialized\n");
    } else {
        is_initialized = 0;
        Det_ReportError(9, 0, 0, RTE_E_PARAM_CONFIG);
    }
}

// Hàm đọc nhiệt độ động cơ từ EngineTemperatureSensor (nhận qua RTE)
Std_ReturnType Rte_ReadEngineTemperature(Rte_EngineTempValueType* engineTemp) {
    if (!is_initialized) {
        Det_ReportError(9, 0, 1, RTE_E_NOT_INITIALIZED);
        return RTE_NOT_OK;
    }

    if (engineTemp == NULL_PTR) {
        Det_ReportError(9, 0, 1, RTE_E_PARAM_POINTER);
        return RTE_NOT_OK;
    }

    // Gọi RTE của EngineTemperatureSensor để đọc nhiệt độ (mô phỏng)
    uint16 temp_value;
    if (Rte_ReadEngineTemperature(&temp_value) == RTE_OK) {
        *engineTemp = temp_value;
        printf("Rte: Read Engine Temperature = %d°C\n", *engineTemp);
        // Kiểm tra lỗi (nếu nhiệt độ quá cao, báo cáo sự kiện qua Dem)
        if (*engineTemp > 100) {
            Dem_ReportEvent(1, 1); // Báo cáo sự kiện lỗi nhiệt độ quá cao
        }
        return RTE_OK;
    } else {
        Det_ReportError(9, 0, 1, RTE_E_READ_FAILED);
        return RTE_NOT_OK;
    }
}

// Hàm gửi tín hiệu điều khiển qua RTE (đến EngineTemperatureActuator)
Std_ReturnType Rte_SendControlSignal(Rte_ControlSignalType controlSignal) {
    if (!is_initialized) {
        Det_ReportError(9, 0, 2, RTE_E_NOT_INITIALIZED);
        return RTE_NOT_OK;
    }

    // Mô phỏng gửi tín hiệu qua Com (CAN)
    Com_SignalType com_signal = {controlSignal, 1}; // Giá trị điều khiển, Signal ID 1
    if (Com_SendSignal(&com_signal) == COM_OK) {
        printf("Rte: Sent Control Signal = %d\n", controlSignal);
        return RTE_OK;
    } else {
        Det_ReportError(9, 0, 2, RTE_E_SEND_FAILED);
        return RTE_NOT_OK;
    }
}

// Hàm main để kiểm tra (chỉ dùng khi compile riêng)
#ifdef TEST_RTE_CONTROL
int main(void) {
    Rte_EngineTempControlConfigType config = {1}; // Bật
    Rte_EngineTempValueType engine_temp;
    Rte_ControlSignalType control_signal = 1; // Tín hiệu bật

    Rte_EngineTempControl_Init(&config);

    if (Rte_ReadEngineTemperature(&engine_temp) == RTE_OK) {
        printf("Engine Temperature = %d°C\n", engine_temp);
    }

    if (Rte_SendControlSignal(control_signal) == RTE_OK) {
        printf("Control Signal sent successfully\n");
    }

    // Kiểm tra lỗi (giả lập nhiệt độ quá cao)
    Rte_SimulateNewEngineTemperature(110); // Tăng nhiệt độ để kiểm tra
    if (Rte_ReadEngineTemperature(&engine_temp) == RTE_OK) {
        printf("Updated Engine Temperature = %d°C\n", engine_temp);
    }

    return 0;
}
#endif