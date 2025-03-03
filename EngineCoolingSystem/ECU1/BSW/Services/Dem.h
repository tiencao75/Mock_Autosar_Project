#ifndef DEM_H
#define DEM_H

#include "Compiler.h"    // Thêm Compiler.h
#include "Std_Types.h"   // Kiểu dữ liệu chuẩn AUTOSAR
#include "Det.h"         // Báo lỗi phát triển

/* Trạng thái trả về cho Dem */
#define DEM_OK       E_OK
#define DEM_NOT_OK   E_NOT_OK

/* Định nghĩa các mã lỗi */
#define DEM_E_PARAM_POINTER    0x01U  // Lỗi con trỏ NULL
#define DEM_E_PARAM_CONFIG     0x02U  // Lỗi cấu hình
#define DEM_E_NOT_INITIALIZED  0x03U  // Lỗi chưa khởi tạo
#define DEM_E_PARAM_EVENT_ID   0x04U  // Lỗi ID sự kiện không hợp lệ

/* Cấu trúc cấu hình cho Dem */
typedef struct {
    VAR(uint8, DEM_VAR) eventId;       // ID sự kiện chẩn đoán
    VAR(uint8, DEM_VAR) severity;      // Độ nghiêm trọng
    VAR(boolean, DEM_VAR) isEnabled;   // Trạng thái bật/tắt
} Dem_ConfigType;

/* Kiểu dữ liệu cho sự kiện chẩn đoán */
typedef struct {
    VAR(uint8, DEM_VAR) eventId;       // ID sự kiện
    VAR(uint8, DEM_VAR) status;        // Trạng thái sự kiện
    VAR(uint16, DEM_VAR) occurrence;   // Số lần xảy ra
} Dem_EventType;

/* Khai báo hàm */
FUNC(void, DEM_CODE) Dem_Init(
    P2CONST(Dem_ConfigType, DEM_CONST, AUTOMATIC) config
);

FUNC(Std_ReturnType, DEM_CODE) Dem_ReportEvent(
    VAR(uint8, DEM_VAR) eventId,
    VAR(uint8, DEM_VAR) status
);

FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventStatus(
    VAR(uint8, DEM_VAR) eventId,
    P2VAR(uint8, DEM_VAR, AUTOMATIC) status
);

#endif /* DEM_H */