#ifndef RTE_ENGINETEMPSENSOR_H
#define RTE_ENGINETEMPSENSOR_H

#include "Std_Types.h" // Bao gồm các kiểu dữ liệu AUTOSAR
#include "Det.h"       // Báo lỗi phát triển
#include "IoHwAb_EngineTempSensor.h" // Giao tiếp với ECU Abstraction

// Trạng thái trả về cho RTE
#define RTE_OK       E_OK
#define RTE_NOT_OK   E_NOT_OK

// Định nghĩa các mã lỗi cho RTE EngineTemperatureSensor
#define RTE_E_PARAM_POINTER    0x01U  // Lỗi con trỏ NULL
#define RTE_E_PARAM_CONFIG     0x02U  // Lỗi cấu hình
#define RTE_E_NOT_INITIALIZED  0x03U  // Lỗi chưa khởi tạo
#define RTE_E_READ_FAILED      0x04U  // Lỗi đọc dữ liệu

// Định nghĩa cấu hình cho RTE EngineTemperatureSensor
typedef struct {
    boolean isEnabled;   // Trạng thái bật/tắt
} Rte_EngineTempSensorConfigType;

// Định nghĩa kiểu dữ liệu cho tín hiệu nhiệt độ động cơ
typedef uint16 Rte_EngineTempValueType;

// Hàm khởi tạo RTE cho EngineTemperatureSensor
void Rte_EngineTempSensor_Init(const Rte_EngineTempSensorConfigType* config);

// Hàm đọc nhiệt độ động cơ (gửi qua RTE)
Std_ReturnType Rte_ReadEngineTemperature(Rte_EngineTempValueType* engineTemp);

#endif // RTE_ENGINETEMPSENSOR_H