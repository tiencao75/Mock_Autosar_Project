#ifndef DEM_H
#define DEM_H

#include "Compiler.h"    // Thêm Compiler.h
#include "Std_Types.h"   // Kiểu dữ liệu chuẩn AUTOSAR
/* Mã lỗi (EventId) */
#define EVENT_01 1  // Engine Temperature Sensor Circuit Malfunction
#define EVENT_02 2   // Unstable Engine Temperature Sensor Signal
#define EVENT_03 3   // No Engine Temperature Sensor Signal
#define EVENT_04 4   // Cooling Fan Control Malfunction
#define EVENT_05 5   // Water Pump Control Malfunction
#define EVENT_06 6   // Lost Communication with Engine Temperature Sensor via CAN
#define EVENT_07 7   // Cooling System ECU Memory Failure

/* Trạng thái sự kiện (EventStatus) */
#define DEM_EVENT_STATUS_PASSED 0x00  // Sự kiện thành công
#define DEM_EVENT_STATUS_FAILED 0x01  // Sự kiện thất bại

typedef uint16 Dem_EventIdType;
typedef uint8 Dem_EventStatusType;
/* Cấu trúc lưu trữ thông tin lỗi */
typedef struct {
    Dem_EventIdType EventId;
    Dem_EventStatusType EventStatus;
} Dem_ErrorEventType;
/* Kích thước mảng chứa các lỗi */
#define MAX_EVENTS 7

/* Mảng chứa các event, tất cả các event mặc định có EventStatus là DEM_EVENT_STATUS_PASSED */
extern Dem_ErrorEventType eventArray[MAX_EVENTS];

FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventStatus(
    Dem_EventIdType EventId,
    Dem_EventStatusType EventStatus
);
#endif /* DEM_H */