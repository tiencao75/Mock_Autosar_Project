#include "Rte_Parameter.h"
#include <stdio.h>

/*----------------------------------------------------------------------------*/
/* Biến toàn cục lưu trữ dữ liệu hiệu chỉnh                                  */
/*----------------------------------------------------------------------------*/
static uint16 CalibrationData = 75;  /* Giá trị mặc định */

/******************************************************************************/  
/* API: Rte_Write_PP_Parameter_ProvideCalibrationData                         */
/* Ghi dữ liệu hiệu chỉnh xuống RTE                                           */  
/******************************************************************************/  
FUNC(Std_ReturnType, RTE_CODE)  
Rte_Write_PP_Parameter_ProvideCalibrationData(P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) calibrationData) {
    if (calibrationData == NULL_PTR) {
        return E_NOT_OK;
    }

    CalibrationData = *calibrationData;
    printf("RTE: Updated Calibration Data = %d\n", CalibrationData);
    return E_OK;
}
