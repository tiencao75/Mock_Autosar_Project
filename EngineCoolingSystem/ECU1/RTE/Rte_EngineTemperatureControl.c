/******************************************************************************/  
/* Copyright   : SCSK Corporation                                             */  
/* System Name : AUTOSAR BSW                                                  */  
/* File Name   : Rte_EngineTemperatureControl.c                               */  
/* Version     : v2.2.2                                                       */  
/* Contents    : RTE Implementation for Engine Temperature Control SWC        */  
/* Author      : QINeS Ecuc Generator 2019.12 (Java)                          */  
/* Note        : Implementation of RTE API for SWC and BSW Communication      */  
/******************************************************************************/  

/*----------------------------------------------------------------------------*/  
/* Include headers                                                            */  
/*----------------------------------------------------------------------------*/  
#include "Rte_EngineTemperatureControl.h"
#include "Rte_EngineTemperatureSensor.h"
#include "Rte_NVBlock.h"
#include <stdio.h>
#include "Rte_Parameter.h"

#define RTE_START_SEC_VAR
/*----------------------------------------------------------------------------*/
/* Biến toàn cục lưu trữ dữ liệu điều khiển nhiệt độ                          */
/*----------------------------------------------------------------------------*/
uint16 FanSpeed = 0;           /* Tốc độ quạt làm mát */
uint16 PumpSpeed = 0;          /* Tốc độ bơm nước */
uint8 WarningLight = 0;        /* Cảnh báo nhiệt độ */
#define RTE_STOP_SEC_VAR

#define RTE_START_SEC_CODE
/******************************************************************************/  
/* API: Rte_Read_RP_EngineTemperatureControl_EngineTemperature                */
/* Đọc giá trị nhiệt độ động cơ từ SWC EngineTemperatureSensor               */  
/******************************************************************************/  
FUNC(Std_ReturnType, RTE_CODE)  
Rte_Read_RP_EngineTemperatureControl_EngineTemperature(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) temperature) {
    if (temperature == NULL_PTR) {
        return E_NOT_OK;
    }

    *temperature = EngineTemperature;  /* Đọc trực tiếp từ biến EngineTemperature */
    return E_OK;
}

/******************************************************************************/  
/* API: Rte_Read_RP_EngineTemperatureControl_AirTemperature                   */
/* Đọc giá trị nhiệt độ không khí từ SWC EngineTemperatureSensor             */  
/******************************************************************************/  
FUNC(Std_ReturnType, RTE_CODE)  
Rte_Read_RP_EngineTemperatureControl_AirTemperature(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) airTemperature) {
    if (airTemperature == NULL_PTR) {
        return E_NOT_OK;
    }
    *airTemperature = AirTemperature;
    return E_OK;
}

/******************************************************************************/  
/* API: Rte_Write_PP_EngineTemperatureControl_FanSpeed                        */
/* Ghi tốc độ quạt làm mát để điều khiển SWC Actuator                        */  
/******************************************************************************/  
FUNC(Std_ReturnType, RTE_CODE)  
Rte_Write_PP_EngineTemperatureControl_FanSpeed(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) fanSpeed) {
    if (fanSpeed == NULL_PTR) {
        return E_NOT_OK;
    }
    FanSpeed = *fanSpeed;

    return E_OK;
}

/******************************************************************************/  
/* API: Rte_Write_PP_EngineTemperatureControl_PumpSpeed                       */
/* Ghi tốc độ bơm nước để điều khiển SWC Actuator                            */  
/******************************************************************************/  
FUNC(Std_ReturnType, RTE_CODE)  
Rte_Write_PP_EngineTemperatureControl_PumpSpeed(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) pumpSpeed) {
    if (pumpSpeed == NULL_PTR) {
        return E_NOT_OK;
    }

    PumpSpeed = *pumpSpeed;
    return E_OK;
}

/******************************************************************************/  
/* API: Rte_Write_PP_EngineTemperatureControl_WarningLight                    */
/* Ghi tín hiệu cảnh báo nhiệt độ động cơ                                    */  
/******************************************************************************/  
FUNC(Std_ReturnType, RTE_CODE)  
Rte_Write_PP_EngineTemperatureControl_WarningLight(P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) warningStatus) {
    if (warningStatus == NULL_PTR) {
        return E_NOT_OK;
    }

    WarningLight = *warningStatus;
    return E_OK;
}

/******************************************************************************/  
/* API: Rte_Write_PP_NVBlock_StoreErrorToRTE                                  */
/* Ghi lỗi xuống RTE                                                          */  
/******************************************************************************/  
FUNC(Std_ReturnType, RTE_CODE)  
Rte_Write_PP_NVBlock_StoreErrorToRTE(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) errorData) {
    if (errorData == NULL_PTR) {
        return E_NOT_OK;
    }

    StoredErrorCode = *errorData;
    return E_OK;
}

/******************************************************************************/  
/* API: Rte_Read_PP_NVBlock_GetCalibrationData                                */
/* Đọc tham số hiệu chỉnh từ RTE                                              */  
/******************************************************************************/  
FUNC(Std_ReturnType, RTE_CODE)  
Rte_Read_RP_Parameter_GetCalibrationData(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) calibrationDataEngine, 
                                         P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) calibrationDataAir) {
    if (calibrationDataEngine == NULL_PTR || calibrationDataAir == NULL_PTR) {
        return E_NOT_OK;  // Kiểm tra con trỏ NULL
    }

    // Trả về dữ liệu hiệu chỉnh cho nhiệt độ động cơ
    *calibrationDataEngine = CalibrationDataEngine;
   

    // Trả về dữ liệu hiệu chỉnh cho nhiệt độ không khí
    *calibrationDataAir = CalibrationDataAir;
   
    return E_OK;
}

FUNC(Std_ReturnType, RTE_CODE)
Rte_Call_EngineTemperatureControl_ReportToDem(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) EventId,
                                         P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) EventStatus){
                                            
}
/*----------------------------------------------------------------------------*/  
/* Runnable API Implementations (Được Application gọi)                        */  
/*----------------------------------------------------------------------------*/  

FUNC(void, RTE_CODE) Rte_Call_PP_CalcCoolingSpeed(CoolingData* data) {
		CalcCoolingSpeed(data);
}

FUNC(void, RTE_CODE) Rte_Call_PP_SendControlSignal(void) {
    SendControlSignal();
}

#define RTE_STOP_SEC_CODE
/* End of Rte_EngineTemperatureControl.c */
