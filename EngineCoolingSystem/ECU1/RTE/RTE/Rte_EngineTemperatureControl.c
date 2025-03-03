/******************************************************************************/  
/* Copyright   : SCSK Corporation                                             */  
/* System Name : AUTOSAR BSW                                                  */  
/* File Name   : Rte_EngineTemperatureControl.c                               */  
/* Version     : v2.2.2                                                       */  
/* Contents    : RTE Implementation for Engine Temperature Control SWC         */  
/* Author      : QINeS Ecuc Generator 2019.12 (Java)                          */  
/* Note        : Implementation of RTE API for SWC and BSW Communication      */  
/******************************************************************************/  

/*----------------------------------------------------------------------------*/  
/* Include headers                                                            */  
/*----------------------------------------------------------------------------*/  
#include "Rte_EngineTemperatureControl.h"
#include "Com.h"
#include "Dem.h"
#include "NvM.h"

/*----------------------------------------------------------------------------*/  
/* Implementation of RTE API                                                  */  
/*----------------------------------------------------------------------------*/  

#define RTE_START_SEC_CODE


/******************************************************************************/  
/* API: Rte_Read_EngineTemperatureControl_Temperature                         */
/* Đọc giá trị nhiệt độ động cơ từ cảm biến                                  */  
/******************************************************************************/  
FUNC(Std_ReturnType, RTE_CODE)  
Rte_Read_EngineTemperatureControl_Temperature( P2VAR(float, AUTOMATIC, RTE_APPL_DATA) temperature ) {
    return Rte_Call_Internal_ReadTemperature(temperature);
}

/******************************************************************************/  
/* API: Rte_Write_EngineTemperatureControl_CoolingSpeed                       */
/* Ghi tốc độ quạt làm mát                                                   */  
/******************************************************************************/  
FUNC(Std_ReturnType, RTE_CODE)  
Rte_Write_EngineTemperatureControl_CoolingSpeed( VAR(uint8, AUTOMATIC) speed ) {
    return Rte_Call_Internal_SetCoolingSpeed(speed);
}

/******************************************************************************/  
/* API: Rte_Read_EngineTemperatureControl_CalibrationData                     */
/* Đọc dữ liệu hiệu chỉnh từ NvM                                             */  
/******************************************************************************/  
FUNC(Std_ReturnType, RTE_CODE)  
Rte_Read_EngineTemperatureControl_CalibrationData( P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) calibrationData ) {
    return Rte_Call_Internal_ReadCalibration(calibrationData);
}

/******************************************************************************/  
/* API: Rte_Call_EngineTemperatureControl_Dem_ReportErrorStatus               */
/* Báo lỗi DTC lên DEM                                                        */  
/******************************************************************************/  
FUNC(Std_ReturnType, RTE_CODE)  
Rte_Call_EngineTemperatureControl_Dem_ReportErrorStatus( VAR(uint32, AUTOMATIC) DTC, VAR(uint8, AUTOMATIC) status ) {
    return Dem_ReportErrorStatus(DTC, status);
}

/******************************************************************************/  
/* API: Rte_Call_EngineTemperatureControl_NvM_WriteErrorLog                   */
/* Ghi lỗi vào bộ nhớ NvM                                                     */  
/******************************************************************************/  
FUNC(Std_ReturnType, RTE_CODE)  
Rte_Call_EngineTemperatureControl_NvM_WriteErrorLog( VAR(uint32, AUTOMATIC) errorCode ) {
    return NvM_WriteBlock(&errorCode);
}

/******************************************************************************/  
/* API: Rte_Call_EngineTemperatureControl_NvM_ReadErrorLog                    */
/* Đọc lỗi từ bộ nhớ NvM                                                      */  
/******************************************************************************/  
FUNC(Std_ReturnType, RTE_CODE)  
Rte_Call_EngineTemperatureControl_NvM_ReadErrorLog( P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) errorCode ) {
    return NvM_ReadBlock(errorCode);
}

/*----------------------------------------------------------------------------*/  
/* Runnable API Implementations (Được Application gọi)                        */  
/*----------------------------------------------------------------------------*/  

FUNC(void, RTE_CODE) Rte_Run_CalcCoolingSpeed(void) {
    Application_CalcCoolingSpeed();
}

FUNC(void, RTE_CODE) Rte_Run_SendControlSignal(void) {
    Application_SendControlSignal();
}

#define RTE_STOP_SEC_CODE
/* End of Rte_EngineTemperatureControl.c */
