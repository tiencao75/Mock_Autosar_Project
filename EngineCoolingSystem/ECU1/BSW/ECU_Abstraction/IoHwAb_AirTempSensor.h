#ifndef IOHWAB_AIRTEMPSENSOR_H
#define IOHWAB_AIRTEMPSENSOR_H

#include "Std_Types.h" // Bao gồm các kiểu dữ liệu AUTOSAR
#include "Det.h"       // Báo lỗi phát triển

// Trạng thái trả về cho IoHwAb
#define IOHWAB_OK       E_OK
#define IOHWAB_NOT_OK   E_NOT_OK

// Định nghĩa các mã lỗi cho IoHwAb_AirTempSensor
#define IOHWAB_E_PARAM_POINTER    0x01U  // Lỗi con trỏ NULL
#define IOHWAB_E_PARAM_CONFIG     0x02U  // Lỗi cấu hình
#define IOHWAB_E_NOT_INITIALIZED  0x03U  // Lỗi chưa khởi tạo
#define IOHWAB_E_READ_FAILED      0x04U  // Lỗi đọc dữ liệu

// Định nghĩa cấu hình cho cảm biến nhiệt độ không khí
typedef struct {
    uint8 channel;         // Kênh ADC cho cảm biến nhiệt độ không khí
    uint8 samplingTime;    // Thời gian lấy mẫu
    boolean isEnabled;     // Trạng thái bật/tắt
} IoHwAb_AirTempConfigType;

// Hàm khởi tạo cảm biến nhiệt độ không khí
void IoHwAb_AirTempSensor_Init(const IoHwAb_AirTempConfigType* config);

// Hàm đọc giá trị nhiệt độ không khí
Std_ReturnType IoHwAb_AirTempSensor_Read(uint16* airTempValue);

#endif // IOHWAB_AIRTEMPSENSOR_H