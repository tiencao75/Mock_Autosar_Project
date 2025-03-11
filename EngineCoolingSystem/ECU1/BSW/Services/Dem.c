#include "Dem.h"

/* Khởi tạo mảng chứa các lỗi với trạng thái mặc định PASSED */
Dem_ErrorEventType eventArray[] = {
    {EVENT_01, DEM_EVENT_STATUS_PASSED},
    {EVENT_02, DEM_EVENT_STATUS_PASSED},
    {EVENT_03, DEM_EVENT_STATUS_PASSED},
    {EVENT_04, DEM_EVENT_STATUS_PASSED},
    {EVENT_05, DEM_EVENT_STATUS_PASSED},
    {EVENT_06, DEM_EVENT_STATUS_PASSED},
    {EVENT_07, DEM_EVENT_STATUS_PASSED}
};

/* Cập nhật trạng thái sự kiện trong hệ thống DEM */
FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventStatus(
    Dem_EventIdType EventId,
    Dem_EventStatusType EventStatus
) {
		uint8 i;
    for (i = 0; i < MAX_EVENTS; i++) {
        if (eventArray[i].EventId == EventId) {
            eventArray[i].EventStatus = EventStatus;
            return E_OK;
        }
    }
    return E_NOT_OK;
}