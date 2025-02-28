#ifndef RTE_ENGINETEMPCONTROL_H
#define RTE_ENGINETEMPCONTROL_H

#include "Std_Types.h" // Bao gồm các kiểu dữ liệu AUTOSAR
#include "Det.h"       // Báo lỗi phát triển
#include "Com.h"       // Giao tiếp với Services (Com)
#include "Dem.h"       // Giao tiếp với Services (Dem)

 // Trạng thái trả về cho RTE
#define RTE_OK       E_OK
#define RTE_NOT_OK   E_NOT_OK

// Định nghĩa các mã lỗi cho RTE EngineTemperatureControl
#define RTE_E_PARAM_POINTER    0x01U  // Lỗi con trỏ NULL
#define RTE_E_PARAM_CONFIG     0x02U  // Lỗi cấu hình
#define RTE_E_NOT_INITIALIZED  0x03U  // Lỗi chưa khởi tạo
#define RTE_E_READ_FAILED      0x04U  // Lỗi đọc dữ liệu
#define RTE_E_SEND_FAILED      0x05U  // Lỗi gửi dữ liệu

// Định nghĩa cấu hình cho RTE EngineTemperatureControl
typedef struct {
    boolean isEnabled;   // Trạng thái bật/tắt
} Rte_EngineTempControlConfigType;

// Định nghĩa kiểu dữ liệu cho tín hiệu nhiệt độ động cơ (từ EngineTemperatureSensor)
typedef uint16 Rte_EngineTempValueType;

// Định nghĩa kiểu dữ liệu cho tín hiệu điều khiển
typedef uint8 Rte_ControlSignalType;

// Hàm khởi tạo RTE cho EngineTemperatureControl
void Rte_EngineTempControl_Init(const Rte_EngineTempControlConfigType* config);

// Hàm đọc nhiệt độ động cơ từ EngineTemperatureSensor (nhận qua RTE)
Std_ReturnType Rte_ReadEngineTemperature(Rte_EngineTempValueType* engineTemp);

// Hàm gửi tín hiệu điều khiển qua RTE (đến EngineTemperatureActuator)
Std_ReturnType Rte_SendControlSignal(Rte_ControlSignalType controlSignal);

#endif // RTE_ENGINETEMPCONTROL_H