#ifndef ADC_H
#define ADC_H

#include "Std_Types.h" // Bao gồm các kiểu dữ liệu AUTOSAR
#include "Det.h"       // Báo lỗi phát triển

// Cấu trúc cấu hình ADC
typedef struct {
    Adc_ChannelType Adc_Channel;     // Kênh ADC (0-15 cho STM32F103)
    uint8_t Adc_Rank;               // Thứ tự kênh (1-16)
    uint8_t Adc_SamplingTime;       // Thời gian lấy mẫu
    uint8_t isEnabled;              // Trạng thái bật/tắt
} Adc_ConfigType;

// Định nghĩa kênh ADC
typedef uint8_t Adc_ChannelType;

// Trạng thái của ADC (sử dụng Std_ReturnType của AUTOSAR)
#define ADC_OK       E_OK
#define ADC_NOT_OK   E_NOT_OK

// Hàm khởi tạo ADC
void Adc_Init(const Adc_ConfigType *ConfigPtr);

// Hàm đọc giá trị từ kênh ADC
Std_ReturnType Adc_ReadChannel(Adc_ChannelType Adc_Channel, uint16_t *Adc_Value);

// Hàm mô phỏng thay đổi giá trị (thêm cho kiểm tra)
void Adc_SimulateNewTemperature(uint16_t new_temp);

#endif // ADC_H