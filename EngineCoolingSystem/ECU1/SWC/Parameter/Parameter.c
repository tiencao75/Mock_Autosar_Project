#include "Rte_Parameter.h"
#include <stdio.h>

/******************************************************************************/  
/* Runnable: ProvideCalibrationData                                           */
/* Cung cấp dữ liệu hiệu chỉnh từ RTE                                         */  
/******************************************************************************/  
FUNC(void, AUTOMATIC) ProvideCalibrationData(void) {
    uint16 calibrationDataEngine =105 ;  // Giá trị hiệu chỉnh cho nhiệt độ động cơ
    uint16 calibrationDataAir = 40;     // Giá trị hiệu chỉnh cho nhiệt độ không khí

    // Ghi dữ liệu hiệu chỉnh cho nhiệt độ động cơ và nhiệt độ không khí xuống RTE
    if (Rte_Write_PP_Parameter_ProvideCalibrationData(&calibrationDataEngine, &calibrationDataAir) == E_OK) {
        //printf("Parameter: Provided Calibration Data for Engine Temperature = %d\n", calibrationDataEngine);
        //printf("Parameter: Provided Calibration Data for Air Temperature = %d\n", calibrationDataAir);
    } else {
        //printf("Failed to write calibration data to RTE.\n");
    }
}
