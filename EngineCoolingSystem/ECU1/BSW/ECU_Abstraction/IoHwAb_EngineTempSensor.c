#include "IoHwAb_EngineTempSensor.h"
#include "Compiler.h"
#include "Adc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Hàm đọc giá trị nhiệt độ động cơ */
FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_EngineTempSensor_Read(
    P2VAR(uint16, IOHWAB_VAR, AUTOMATIC) engineTempValue
) {
    if (engineTempValue == NULL_PTR) {
        Det_ReportError(2, 0, 1, IOHWAB_E_PARAM_POINTER);
        return IOHWAB_NOT_OK;
    }
    if (Adc_ReadChannel(1, engineTempValue) == E_OK) {
        return IOHWAB_OK;
    } else {
        Det_ReportError(2, 0, 1, IOHWAB_E_READ_FAILED);
        return IOHWAB_NOT_OK;
    }
}
