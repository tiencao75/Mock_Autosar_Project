#ifndef RTE_ENGINETEMPERATURESENSOR_H
#define RTE_ENGINETEMPERATURESENSOR_H

#include "Std_Types.h"
#include "Compiler.h"
#include "Compiler_Cfg.h"
#include "IoHwAb_EngineTempSensor.h"
#include "IoHwAb_AirTempSensor.h"

extern uint16 EngineTemperature;
extern uint16 AirTemperature; 
/*----------------------------------------------------------------------------*/
/* API để Application gọi xuống BSW                                                      */
/*----------------------------------------------------------------------------*/

/* API để đọc nhiệt độ động cơ */
FUNC(Std_ReturnType, RTE_CODE)
Rte_Call_RP_EngineTemperatureSensor_EngineTemperature(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) temperature);

/* API để đọc nhiệt độ không khí */
FUNC(Std_ReturnType, RTE_CODE)
Rte_Call_RP_EngineTemperatureSensor_AirTemperature(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) airTemperature);

/* API để ghi dữ liệu nhiệt độ động cơ đến SWC khác */
FUNC(Std_ReturnType, RTE_CODE)
Rte_Write_PP_EngineTemperatureSensor_EngineTemperature(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) temperature);

/* API để ghi dữ liệu nhiệt độ không khí đến SWC khác */
FUNC(Std_ReturnType, RTE_CODE)
Rte_Write_PP_EngineTemperatureSensor_AirTemperature(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) airTemperature);

/*----------------------------------------------------------------------------*/
/* API để OS (BSW) gọi lên Application (Runnable)                                                  */
/*----------------------------------------------------------------------------*/

/* Runnable để lấy dữ liệu nhiệt độ động cơ */
FUNC(void, RTE_CODE) Rte_Call_PP_GetEngineTemperature(void);

/* Runnable để lấy dữ liệu nhiệt độ không khí */
FUNC(void, RTE_CODE) Rte_Call_PP_GetAirTemperature(void);

#endif /* RTE_ENGINETEMPERATURESENSOR_H */
