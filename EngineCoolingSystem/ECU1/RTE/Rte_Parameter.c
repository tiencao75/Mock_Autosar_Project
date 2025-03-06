#include "Rte_Parameter.h"
#include <stdio.h>

/*----------------------------------------------------------------------------*/
/* Biến toàn cục lưu trữ dữ liệu hiệu chỉnh                                  */
/*----------------------------------------------------------------------------*/

uint16 CalibrationDataEngine = 0;  //  giá trị hiệu chỉnh cho nhiệt độ động cơ là 100
uint16 CalibrationDataAir = 0;     // giá trị hiệu chỉnh cho nhiệt độ không khí là 90

/******************************************************************************/  
/* API: Rte_Write_PP_Parameter_ProvideCalibrationData                         */
/* Ghi dữ liệu hiệu chỉnh xuống RTE                                           */  
/******************************************************************************/ 

FUNC(Std_ReturnType, RTE_CODE)  
Rte_Write_PP_Parameter_ProvideCalibrationData(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) calibrationDataEngine, 
                                             P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) calibrationDataAir) {
    if (calibrationDataEngine == NULL_PTR || calibrationDataAir == NULL_PTR) {
        return E_NOT_OK;  // Kiểm tra con trỏ NULL
    }

    // Ghi dữ liệu hiệu chỉnh cho nhiệt độ động cơ
    CalibrationDataEngine = *calibrationDataEngine;
   
    // Ghi dữ liệu hiệu chỉnh cho nhiệt độ không khí
    CalibrationDataAir = *calibrationDataAir;
    

    return E_OK;
}

FUNC(void, RTE_CODE) Rte_Call_PP_Calibration_CalibrationData(void){
	ProvideCalibrationData();
}