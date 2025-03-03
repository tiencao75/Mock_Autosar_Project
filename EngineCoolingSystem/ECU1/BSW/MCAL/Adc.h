#ifndef ADC_H
#define ADC_H

#include "Compiler.h"    // Thêm Compiler.h để dùng macro
#include "Std_Types.h"   // Kiểu dữ liệu chuẩn AUTOSAR
#include "Det.h"         // Báo lỗi phát triển

/* Cấu trúc cấu hình ADC */
typedef struct {
    VAR(Adc_ChannelType, ADC_VAR) Adc_Channel;     // Kênh ADC
    VAR(uint8, ADC_VAR) Adc_Rank;                  // Thứ tự kênh
    VAR(uint8, ADC_VAR) Adc_SamplingTime;          // Thời gian lấy mẫu
    VAR(boolean, ADC_VAR) isEnabled;               // Trạng thái bật/tắt
} Adc_ConfigType;

/* Định nghĩa kiểu kênh ADC */
typedef VAR(uint8, ADC_VAR) Adc_ChannelType;

/* Trạng thái trả về của ADC */
#define ADC_OK       E_OK
#define ADC_NOT_OK   E_NOT_OK

/* Khai báo hàm */
FUNC(void, ADC_CODE) Adc_Init(
    P2CONST(Adc_ConfigType, ADC_CONST, AUTOMATIC) ConfigPtr
);

FUNC(Std_ReturnType, ADC_CODE) Adc_ReadChannel(
    VAR(Adc_ChannelType, ADC_VAR) Adc_Channel,
    P2VAR(uint16, ADC_VAR, AUTOMATIC) Adc_Value
);

FUNC(void, ADC_CODE) Adc_SimulateNewTemperature(
    VAR(uint16, ADC_VAR) new_temp
);

#endif /* ADC_H */