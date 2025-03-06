#ifndef RTE_ENGINETEMPERATURECONTROL_H
#define RTE_ENGINETEMPERATURECONTROL_H

#include "Std_Types.h"
#include "Compiler.h"
#include "Compiler_Cfg.h"
#include "Com.h"
#include "Rte_Parameter.h"
#include "Rte_EngineTemperatureSensor.h"

/*----------------------------------------------------------------------------*/
/* API để Application gọi xuống BSW hoặc SWC khác                             */
/*----------------------------------------------------------------------------*/

/* API để đọc nhiệt độ động cơ */
FUNC(Std_ReturnType, RTE_CODE)
Rte_Read_RP_EngineTemperatureControl_EngineTemperature(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) temperature);

/* API để đọc nhiệt độ không khí */
FUNC(Std_ReturnType, RTE_CODE)
Rte_Read_RP_EngineTemperatureControl_AirTemperature(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) airTemperature);

/* API để ghi tín hiệu điều khiển quạt làm mát */
FUNC(Std_ReturnType, RTE_CODE)
Rte_Write_PP_EngineTemperatureControl_FanSpeed(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) fanSpeed);

/* API để ghi tín hiệu điều khiển bơm nước */
FUNC(Std_ReturnType, RTE_CODE)
Rte_Write_PP_EngineTemperatureControl_PumpSpeed(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) pumpSpeed);

/* API để ghi cảnh báo nhiệt độ */
FUNC(Std_ReturnType, RTE_CODE)
Rte_Write_PP_EngineTemperatureControl_WarningLight(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) warningStatus);

/* API ghi lỗi xuống RTE */
FUNC(Std_ReturnType, RTE_CODE)
Rte_Write_PP_NVBlock_StoreErrorToRTE(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) errorData);

/* API đọc tham số hiệu chỉnh từ RTE */
FUNC(Std_ReturnType, RTE_CODE)
Rte_Read_RP_Parameter_GetCalibrationData(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) calibrationDataEngine, 
                                         P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) calibrationDataAir);

FUNC(Std_ReturnType, RTE_CODE)
Rte_Call_EngineTemperatureControl_ReportToDem(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) EventId,
                                         P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) EventStatus);
                                         

/*----------------------------------------------------------------------------*/
/* API để OS (BSW) gọi lên Application (Runnable)                             */
/*----------------------------------------------------------------------------*/

/* Runnable để tính toán tốc độ quạt làm mát */
FUNC(void, RTE_CODE) Rte_Call_PP_CalcCoolingSpeed(CoolingData* data);

/* Runnable để gửi tín hiệu điều khiển */
FUNC(void, RTE_CODE) Rte_Call_PP_SendControlSignal(void);

#endif /* RTE_ENGINETEMPERATURECONTROL_H */
