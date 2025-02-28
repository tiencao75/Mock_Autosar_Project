#ifndef DEM_H
#define DEM_H

#include "Std_Types.h" // Bao gồm các kiểu dữ liệu AUTOSAR
#include "Det.h"       // Báo lỗi phát triển

// Trạng thái trả về cho Dem
#define DEM_OK       E_OK
#define DEM_NOT_OK   E_NOT_OK

// Định nghĩa các mã lỗi cho Dem
#define DEM_E_PARAM_POINTER    0x01U  // Lỗi con trỏ NULL
#define DEM_E_PARAM_CONFIG     0x02U  // Lỗi cấu hình
#define DEM_E_NOT_INITIALIZED  0x03U  // Lỗi chưa khởi tạo
#define DEM_E_PARAM_EVENT_ID   0x04U  // Lỗi ID sự kiện không hợp lệ

// Định nghĩa cấu hình cho Dem
typedef struct {
    uint8 eventId;       // ID sự kiện chẩn đoán
    uint8 severity;      // Độ nghiêm trọng (ví dụ: 0 - không nghiêm trọng, 1 - nghiêm trọng)
    boolean isEnabled;   // Trạng thái bật/tắt
} Dem_ConfigType;

// Định nghĩa kiểu dữ liệu cho sự kiện chẩn đoán
typedef struct {
    uint8 eventId;       // ID sự kiện
    uint8 status;        // Trạng thái sự kiện (ví dụ: 0 - chưa xảy ra, 1 - đã xảy ra)
    uint16 occurrence;   // Số lần xảy ra sự kiện
} Dem_EventType;

// Hàm khởi tạo module Dem
void Dem_Init(const Dem_ConfigType* config);

// Hàm báo cáo sự kiện chẩn đoán (mô phỏng)
Std_ReturnType Dem_ReportEvent(uint8 eventId, uint8 status);

// Hàm đọc trạng thái sự kiện (mô phỏng)
Std_ReturnType Dem_GetEventStatus(uint8 eventId, uint8* status);

#endif // DEM_H