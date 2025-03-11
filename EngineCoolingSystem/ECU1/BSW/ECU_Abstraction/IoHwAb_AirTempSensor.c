#include "IoHwAb_AirTempSensor.h"
#include "Compiler.h"  // Thêm Compiler.h
#include "Adc.h"       // Gọi MCAL để đọc giá trị ADC
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Hàm đọc giá trị nhiệt độ không khí */
FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_AirTempSensor_Read(
    P2VAR(uint16, IOHWAB_VAR, AUTOMATIC) airTempValue
) {
    if (airTempValue == NULL_PTR) {
        Det_ReportError(1, 0, 1, IOHWAB_E_PARAM_POINTER);
        return IOHWAB_NOT_OK;
    }
    if (Adc_ReadChannel(0, airTempValue) == E_OK) {
        return IOHWAB_OK;
    } else {
        Det_ReportError(1, 0, 1, IOHWAB_E_READ_FAILED);
        return IOHWAB_NOT_OK;
    }
}
