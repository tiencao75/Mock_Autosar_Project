#ifndef ENGINETEMPSENSOR_H
#define ENGINETEMPSENSOR_H

#include "Std_Types.h" // Bao gồm các kiểu dữ liệu AUTOSAR
#include "Det.h"       // Báo lỗi phát triển
#include "Rte_EngineTemperatureSensor.h" // Giao tiếp với RTE

// Trạng thái trả về (sử dụng từ RTE)
#define RTE_OK       E_OK
#define RTE_NOT_OK   E_NOT_OK

// Định nghĩa kiểu dữ liệu cho nhiệt độ động cơ
typedef uint16 EngineTempValueType;

// Hàm khởi tạo SWC EngineTemperatureSensor
void EngineTemperatureSensor_Init(void);

// Hàm đọc nhiệt độ động cơ
Std_ReturnType EngineTemperatureSensor_GetTemperature(EngineTempValueType* engineTemp);

// Hàm mô phỏng thay đổi giá trị nhiệt độ động cơ (cho mục đích kiểm tra)
void EngineTemperatureSensor_SimulateNewTemperature(uint16 new_temp);

#endif // ENGINETEMPSENSOR_H