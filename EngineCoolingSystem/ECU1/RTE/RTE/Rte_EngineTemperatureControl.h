/******************************************************************************/  
/* Copyright   : SCSK Corporation                                             */  
/* System Name : AUTOSAR BSW                                                  */  
/* File Name   : Rte_EngineTemperatureControl.h                               */  
/* Version     : v2.2.2                                                       */  
/* Contents    : RTE Interface for Engine Temperature Control SWC              */  
/* Author      : QINeS Ecuc Generator 2019.12 (Java)                          */  
/* Note        : Interface for interaction between Application & BSW          */  
/******************************************************************************/  

#ifndef RTE_ENGINETEMPERATURECONTROL_H
#define RTE_ENGINETEMPERATURECONTROL_H

/*----------------------------------------------------------------------------*/  
/* Include headers                                                            */  
/*----------------------------------------------------------------------------*/  
// #include "Rte_EngineTemperatureControl_Type.h"
#include "Common/Std_Types.h"
#include "Common/Compiler.h"
#include "Common/Compiler_Cfg.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*----------------------------------------------------------------------------*/  
/* Định nghĩa hằng số nếu chưa có                                            */  
/*----------------------------------------------------------------------------*/  
#ifndef RTE_CONST
#define RTE_CONST const
#endif

/*----------------------------------------------------------------------------*/  
/* RTE Instance Structure                                                     */  
/*----------------------------------------------------------------------------*/  
struct Rte_CDS_EngineTemperatureControl {
    VAR(uint8, AUTOMATIC) Rte_Dummy;
};

extern RTE_CONST P2CONST(struct Rte_CDS_EngineTemperatureControl, RTE_CONST, RTE_CONST) Rte_Inst_EngineTemperatureControl;

/*----------------------------------------------------------------------------*/  
/* API để Application gọi xuống BSW                                          */  
/*----------------------------------------------------------------------------*/  

/* Đọc giá trị nhiệt độ động cơ từ cảm biến */
extern FUNC(Std_ReturnType, RTE_CODE)  
Rte_Read_EngineTemperatureControl_Temperature( P2VAR(float, AUTOMATIC, RTE_APPL_DATA) temperature );

/* Ghi tốc độ quạt làm mát */
extern FUNC(Std_ReturnType, RTE_CODE)  
Rte_Write_EngineTemperatureControl_CoolingSpeed( VAR(uint8, AUTOMATIC) speed );

/* Đọc dữ liệu hiệu chỉnh */
extern FUNC(Std_ReturnType, RTE_CODE)  
Rte_Read_EngineTemperatureControl_CalibrationData( P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) calibrationData );

/* Báo lỗi DTC */
extern FUNC(Std_ReturnType, RTE_CODE)  
Rte_Call_EngineTemperatureControl_Dem_ReportErrorStatus( VAR(uint32, AUTOMATIC) DTC, VAR(uint8, AUTOMATIC) status );

/* Ghi log lỗi vào NvM */
extern FUNC(Std_ReturnType, RTE_CODE)  
Rte_Call_EngineTemperatureControl_NvM_WriteErrorLog( VAR(uint32, AUTOMATIC) errorCode );

/* Đọc log lỗi từ NvM */
extern FUNC(Std_ReturnType, RTE_CODE)  
Rte_Call_EngineTemperatureControl_NvM_ReadErrorLog( P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) errorCode );

/*----------------------------------------------------------------------------*/  
/* API để OS (BSW) gọi lên Application (Runnable)                                 */  
/*----------------------------------------------------------------------------*/  

#define EngineTemperatureControl_START_SEC_CODE


/* Runnable API được Application gọi */
extern FUNC(void, EngineTemperatureControl_CODE) Rte_Run_CalcCoolingSpeed(void);
extern FUNC(void, EngineTemperatureControl_CODE) Rte_Run_SendControlSignal(void);

#define EngineTemperatureControl_STOP_SEC_CODE


#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* RTE_ENGINETEMPERATURECONTROL_H */

/* End of Rte_EngineTemperatureControl.h */
