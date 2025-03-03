#ifndef RTE_ENGINETEMPERATURESENSOR_H
#define RTE_ENGINETEMPERATURESENSOR_H

#include "Common/Std_Types.h"
#include "Common/Compiler.h"
#include "Common/Compiler_Cfg.h"
#include "IoHwAb_EngineTempSensor.h"
#include "IoHwAb_AirTempSensor.h"

/*----------------------------------------------------------------------------*/
/* API để Application gọi xuống BSW                                                      */
/*----------------------------------------------------------------------------*/

/* API để đọc nhiệt độ động cơ */
FUNC(Std_ReturnType, RTE_CODE)
Rte_Read_EngineTemperatureSensor_EngineTemperature(P2VAR(float, AUTOMATIC, RTE_APPL_DATA) temperature);

/* API để đọc nhiệt độ không khí */
FUNC(Std_ReturnType, RTE_CODE)
Rte_Read_EngineTemperatureSensor_AirTemperature(P2VAR(float, AUTOMATIC, RTE_APPL_DATA) airTemperature);

/*----------------------------------------------------------------------------*/
/* API để OS (BSW) gọi lên Application (Runnable)                                                  */
/*----------------------------------------------------------------------------*/

/* Runnable để lấy dữ liệu nhiệt độ động cơ */
FUNC(void, RTE_CODE) Rte_Run_GetEngineTemperature(void);

/* Runnable để lấy dữ liệu nhiệt độ không khí */
FUNC(void, RTE_CODE) Rte_Run_GetAirTemperature(void);

#endif /* RTE_ENGINETEMPERATURESENSOR_H */
