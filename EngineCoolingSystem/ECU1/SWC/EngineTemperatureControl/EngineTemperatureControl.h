#ifndef ENGINE_TEMPERATURE_CONTROL_H
#define ENGINE_TEMPERATURE_CONTROL_H

#include "Std_Types.h"
#include "Compiler.h"
#include "Compiler_Cfg.h"
#include "Com.h"  // Giao tiếp với ECU 2

/*----------------------------------------------------------------------------*/
/* API Declarations (Hàm được gọi từ Scheduler hoặc SWC khác)                 */
/*----------------------------------------------------------------------------*/

/* Khởi tạo bộ điều khiển nhiệt độ động cơ */
FUNC(void, AUTOMATIC) EngineTemperatureControl_Init(void);

/* Runnable API - Tính toán tốc độ quạt và bơm */
FUNC(void, AUTOMATIC) CalcCoolingSpeed(void);

/* Runnable API - Gửi tín hiệu điều khiển qua Com */
FUNC(void, AUTOMATIC) SendControlSignal(void);

#endif /* ENGINE_TEMPERATURE_CONTROL_H */
