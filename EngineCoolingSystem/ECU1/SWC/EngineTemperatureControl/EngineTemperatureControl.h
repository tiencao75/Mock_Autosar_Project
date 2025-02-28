#ifndef ENGINETEMPCONTROL_H
#define ENGINETEMPCONTROL_H

#include "Std_Types.h" // Bao gồm các kiểu dữ liệu AUTOSAR
#include "Det.h"       // Báo lỗi phát triển
#include "Rte_EngineTemperatureControl.h" // Giao tiếp với RTE

// Trạng thái trả về (sử dụng từ RTE)
#define RTE_OK       E_OK
#define RTE_NOT_OK   E_NOT_OK

// Định nghĩa kiểu dữ liệu cho nhiệt độ động cơ
typedef uint16 EngineTempValueType;

// Định nghĩa kiểu dữ liệu cho tín hiệu điều khiển
typedef uint8 ControlSignalType;

// Hàm khởi tạo SWC EngineTemperatureControl
void EngineTemperatureControl_Init(void);

// Hàm đọc nhiệt độ động cơ từ EngineTemperatureSensor
Std_ReturnType EngineTemperatureControl_GetEngineTemperature(EngineTempValueType* engineTemp);

// Hàm gửi tín hiệu điều khiển
Std_ReturnType EngineTemperatureControl_SendControlSignal(ControlSignalType controlSignal);

// Hàm điều khiển logic (mô phỏng)
void EngineTemperatureControl_Process(void);

#endif // ENGINETEMPCONTROL_H