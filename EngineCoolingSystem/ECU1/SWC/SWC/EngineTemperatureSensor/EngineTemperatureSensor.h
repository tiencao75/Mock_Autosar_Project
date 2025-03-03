#ifndef ENGINE_TEMPERATURE_SENSOR_H
#define ENGINE_TEMPERATURE_SENSOR_H

#include "Common/Std_Types.h"
#include "Common/Compiler.h"
#include "Common/Compiler_Cfg.h"

/*----------------------------------------------------------------------------*/
/* API Declarations (Hàm được gọi từ Scheduler hoặc SWC khác)                 */
/*----------------------------------------------------------------------------*/

/* Khởi tạo cảm biến nhiệt độ động cơ */
FUNC(void, AUTOMATIC) EngineTemperatureSensor_Init(void);

/* Runnable API - Đọc nhiệt độ động cơ */
FUNC(void, AUTOMATIC) GetEngineTemperature(void);

/* Runnable API - Đọc nhiệt độ không khí */
FUNC(void, AUTOMATIC) GetAirTemperature(void);

#endif /* ENGINE_TEMPERATURE_SENSOR_H */
