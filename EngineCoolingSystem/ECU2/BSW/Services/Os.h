#ifndef OS_H
#define OS_H

#include "Std_Types.h"  // Kiểu dữ liệu chuẩn AUTOSAR
#include <stdint.h>     // uint32 cho EventMaskType
#include "Rte_EngineTemperatureActuator.h"  // Giao tiếp với RTE

/* Định nghĩa Task ID */
#define TASK_ACTUATOR         0  // Task xử lý actuator (quạt, bơm, đèn cảnh báo)
#define TASK_READ_CONTROL     1  // Task đọc tín hiệu điều khiển
#define TASK_COUNT            2  // Số lượng task

/* Định nghĩa Event ID */
#define BE_CONTROL_SIGNAL_READ      (1 << 0)  // Sự kiện tín hiệu điều khiển được đọc
#define BE_TEMPERATURE_UPDATE       (1 << 1)  // Sự kiện cập nhật nhiệt độ
#define BE_PUMP_SPEED_CHANGED       (1 << 2)  // Sự kiện bơm đã được điều chỉnh
#define BE_FAN_SPEED_CHANGED        (1 << 3)  // Sự kiện quạt đã được điều chỉnh
#define BE_WARNING_LIGHT_CHANGED    (1 << 4)  // Sự kiện đèn cảnh báo đã được điều khiển

/* Định nghĩa kiểu EventMask */
typedef uint32 EventMaskType; 

#endif /* OS_H */