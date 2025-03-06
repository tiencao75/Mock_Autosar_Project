/******************************************************************************/  
/* Copyright   : SCSK Corporation                                             */  
/* System Name : AUTOSAR BSW                                                  */  
/* File Name   : Rte_EngineTemperatureSensor.c                                */  
/* Version     : v2.2.2                                                       */  
/* Contents    : RTE Implementation for Engine Temperature Sensor SWC         */  
/* Author      : QINeS Ecuc Generator 2019.12 (Java)                          */  
/* Note        : Implementation of RTE API for SWC and BSW Communication      */  
/******************************************************************************/  

/*----------------------------------------------------------------------------*/  
/* Include headers                                                            */  
/*----------------------------------------------------------------------------*/  
#include "Rte_EngineTemperatureSensor.h"
#include <stdio.h>

#define RTE_START_SEC_VAR
/*----------------------------------------------------------------------------*/
/* Biến toàn cục lưu trữ dữ liệu nhiệt độ                                     */
/*----------------------------------------------------------------------------*/
uint16 EngineTemperature = 0;  /* Nhiệt độ động cơ */
uint16 AirTemperature = 0;     /* Nhiệt độ không khí */
#define RTE_STOP_SEC_VAR

#define RTE_START_SEC_CODE
/******************************************************************************/  
/* API: Rte_Read_EngineTemperatureSensor_EngineTemperature                    */
/* Đọc giá trị nhiệt độ động cơ từ IoHwAb                                    */  
/******************************************************************************/  
FUNC(Std_ReturnType, RTE_CODE)  
Rte_Call_RP_EngineTemperatureSensor_EngineTemperature(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) temperature) {
    if (temperature == NULL_PTR) {
        return E_NOT_OK;
    }

    /* Gọi API từ IoHwAb để lấy nhiệt độ động cơ */
    Std_ReturnType status = IoHwAb_EngineTempSensor_Read(temperature);
    
    // /* Trả kết quả về biến được truyền vào */
    // *temperature = EngineTemperature;

    return status;
}

/******************************************************************************/  
/* API: Rte_Read_EngineTemperatureSensor_AirTemperature                       */
/* Đọc giá trị nhiệt độ không khí từ IoHwAb                                  */  
/******************************************************************************/  
FUNC(Std_ReturnType, RTE_CODE)  
Rte_Call_RP_EngineTemperatureSensor_AirTemperature(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) airTemperature) {
    if (airTemperature == NULL_PTR) {
        return E_NOT_OK;
    }

    /* Gọi API từ IoHwAb để lấy nhiệt độ không khí */
    Std_ReturnType status = IoHwAb_AirTempSensor_Read(&AirTemperature);
    
    /* Trả kết quả về biến được truyền vào */
    *airTemperature = AirTemperature;

    return status;
}

/******************************************************************************/  
/* API: Rte_Write_EngineTemperatureSensor_EngineTemperature                    */
/* Ghi giá trị nhiệt độ động cơ vào SWC khác                                 */  
/******************************************************************************/  
FUNC(Std_ReturnType, RTE_CODE)  
Rte_Write_PP_EngineTemperatureSensor_EngineTemperature(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) temperature) {
    if (temperature == NULL_PTR) {
        return E_NOT_OK;
    }

    /* Cập nhật giá trị nhiệt độ động cơ toàn cục */
    EngineTemperature = *temperature;

    return E_OK;
}

/******************************************************************************/  
/* API: Rte_Write_EngineTemperatureSensor_AirTemperature                      */
/* Ghi giá trị nhiệt độ không khí vào SWC khác                               */  
/******************************************************************************/  
FUNC(Std_ReturnType, RTE_CODE)  
Rte_Write_PP_EngineTemperatureSensor_AirTemperature(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) airTemperature) {
    if (airTemperature == NULL_PTR) {
        return E_NOT_OK;
    }

    /* Cập nhật giá trị nhiệt độ không khí toàn cục */
    AirTemperature = *airTemperature;

    return E_OK;
}
/*----------------------------------------------------------------------------*/  
/* Runnable API Implementations (Được Application gọi)                        */  
/*----------------------------------------------------------------------------*/  

FUNC(void, RTE_CODE) Rte_Call_PP_GetEngineTemperature(void) {
    GetEngineTemperature();
}

FUNC(void, RTE_CODE) Rte_Call_PP_GetAirTemperature(void) {
    GetAirTemperature();
}

#define RTE_STOP_SEC_CODE
/* End of Rte_EngineTemperatureSensor.c */
