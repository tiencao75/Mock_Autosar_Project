#ifndef ADC_H
#define ADC_H

#include "Compiler.h"    // Thêm Compiler.h để dùng macro
#include "Std_Types.h"   // Kiểu dữ liệu chuẩn AUTOSAR
#include "Det.h"         // Báo lỗi phát triển
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_ENGINE_TEMP 30   // Điều chỉnh MIN_TEMP thành 100
#define MAX_ENGINE_TEMP 150   // Điều chỉnh MAX_TEMP thành 300
#define MIN_AIR_TEMP 0
#define MAX_AIR_TEMP 55
/* Định nghĩa kiểu kênh ADC */
typedef VAR(uint8, ADC_VAR) Adc_ChannelType;

/* Cấu trúc cấu hình ADC */
typedef struct {
    VAR(Adc_ChannelType, ADC_VAR) Adc_Channel;     // Kênh ADC
    VAR(uint8, ADC_VAR) Adc_Rank;                  // Thứ tự kênh
    VAR(uint8, ADC_VAR) Adc_SamplingTime;          // Thời gian lấy mẫu
    VAR(boolean, ADC_VAR) isEnabled;               // Trạng thái bật/tắt
} Adc_ConfigType;


/* Trạng thái trả về của ADC */
#define ADC_OK       E_OK
#define ADC_NOT_OK   E_NOT_OK

FUNC(Std_ReturnType, ADC_CODE) Adc_ReadChannel(
    VAR(Adc_ChannelType, ADC_VAR) Adc_Channel,
    P2VAR(uint16, ADC_VAR, AUTOMATIC) Adc_Value
);

FUNC(Std_ReturnType, ADC_CODE) Adc_SimulateEngineTemperature();
FUNC(Std_ReturnType, ADC_CODE) Adc_SimulateAirTemperature();
#endif /* ADC_H */