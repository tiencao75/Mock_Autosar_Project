#ifndef ENGINE_TEMPERATURE_CONTROL_H
#define ENGINE_TEMPERATURE_CONTROL_H

#include "Std_Types.h"
#include "Compiler.h"
#include "Compiler_Cfg.h"
#include "Com.h"  // Giao tiếp với ECU 2
#include "Nvm.h"
#include "Rte_EngineTemperatureControl.h"

/*----------------------------------------------------------------------------*/
/* Định nghĩa hằng số được sử dụng trong CalcCoolingSpeed                     */
/*----------------------------------------------------------------------------*/
#define TEMP_FAN_START      85U   /* Nhiệt độ bắt đầu làm mát */
#define TEMP_MAX_SPEED     110U   /* Nhiệt độ đạt tốc độ tối đa */
#define AIR_TEMP_HOT         5U   /* Ngưỡng không khí nóng */
#define SPEED_MAX          100U   /* Tốc độ tối đa (%) */
#define SPEED_MIN            0U   /* Tốc độ tối thiểu (%) */
#define SPEED_ADJUST        10U   /* Hệ số điều chỉnh (%) */
/*----------------------------------------------------------------------------*/
/* API Declarations (Hàm được gọi từ Scheduler hoặc SWC khác)                 */
/*----------------------------------------------------------------------------*/

/* Khởi tạo bộ điều khiển nhiệt độ động cơ */
FUNC(void, AUTOMATIC) EngineTemperatureControl_Init(void);

/* Runnable API - Tính toán tốc độ quạt và bơm */
FUNC(Std_ReturnType, AUTOMATIC) CalcCoolingSpeed(P2VAR(CoolingData, AUTOMATIC, RTE_APPL_DATA) data);

/* Runnable API - Gửi tín hiệu điều khiển qua Com */
FUNC(Std_ReturnType, AUTOMATIC) SendControlSignal(void);

#endif /* ENGINE_TEMPERATURE_CONTROL_H */
