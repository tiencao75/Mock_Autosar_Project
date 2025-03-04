#include "Rte_Parameter.h"
#include <stdio.h>

/******************************************************************************/  
/* Runnable: ProvideCalibrationData                                           */
/* Cung cấp dữ liệu hiệu chỉnh từ RTE                                         */  
/******************************************************************************/  
FUNC(void, AUTOMATIC) ProvideCalibrationData(void) {
    uint16 calibrationData;

    if (Rte_Write_PP_Parameter_ProvideCalibrationData(&calibrationData) == E_OK) {
        printf("Parameter: Provided Calibration Data = %d\n", calibrationData);
    }
}
