#include "Dem.h"
#include <stdio.h>

// Biến toàn cục mô phỏng danh sách sự kiện chẩn đoán
static Dem_EventType events[10] = {0}; // Mảng mô phỏng tối đa 10 sự kiện, ban đầu tất cả là 0
static uint8 is_initialized = 0;        // Trạng thái khởi tạo

// Hàm khởi tạo module Dem
void Dem_Init(const Dem_ConfigType* config) {
    if (config == NULL_PTR) {
        Det_ReportError(5, 0, 0, DEM_E_PARAM_POINTER); // Báo lỗi AUTOSAR
        return;
    }

    if (config->isEnabled) {
        is_initialized = 1;
        // Mô phỏng khởi tạo sự kiện với ID và mức độ nghiêm trọng
        for (uint8 i = 0; i < 10; i++) {
            events[i].eventId = i;
            events[i].status = 0; // Chưa xảy ra
            events[i].occurrence = 0;
        }
        printf("Dem Module Initialized (Event ID %d, Severity %d)\n",
               config->eventId, config->severity);
    } else {
        is_initialized = 0;
        Det_ReportError(5, 0, 0, DEM_E_PARAM_CONFIG);
    }
}

// Hàm báo cáo sự kiện chẩn đoán (mô phỏng)
Std_ReturnType Dem_ReportEvent(uint8 eventId, uint8 status) {
    if (!is_initialized) {
        Det_ReportError(5, 0, 1, DEM_E_NOT_INITIALIZED);
        return DEM_NOT_OK;
    }

    if (eventId >= 10) { // Kiểm tra giới hạn mảng
        Det_ReportError(5, 0, 1, DEM_E_PARAM_EVENT_ID);
        return DEM_NOT_OK;
    }

    // Cập nhật trạng thái và số lần xảy ra sự kiện
    events[eventId].status = status;
    if (status == 1) { // Sự kiện đã xảy ra
        events[eventId].occurrence++;
    }
    printf("Dem: Reported Event - ID = %d, Status = %d, Occurrences = %d\n",
           eventId, status, events[eventId].occurrence);
    return DEM_OK;
}

// Hàm đọc trạng thái sự kiện (mô phỏng)
Std_ReturnType Dem_GetEventStatus(uint8 eventId, uint8* status) {
    if (!is_initialized) {
        Det_ReportError(5, 0, 2, DEM_E_NOT_INITIALIZED);
        return DEM_NOT_OK;
    }

    if (eventId >= 10) {
        Det_ReportError(5, 0, 2, DEM_E_PARAM_EVENT_ID);
        return DEM_NOT_OK;
    }

    if (status == NULL_PTR) {
        Det_ReportError(5, 0, 2, DEM_E_PARAM_POINTER);
        return DEM_NOT_OK;
    }

    *status = events[eventId].status;
    printf("Dem: Get Event Status - ID = %d, Status = %d\n", eventId, *status);
    return DEM_OK;
}

// Hàm main để kiểm tra (chỉ dùng khi compile riêng)
#ifdef TEST_DEM
int main(void) {
    Dem_ConfigType config = {0, 1, 1}; // Event ID 0, Severity 1, bật
    uint8 status;

    Dem_Init(&config);

    if (Dem_ReportEvent(0, 1) == DEM_OK) { // Báo cáo sự kiện xảy ra
        printf("Event reported successfully\n");
    }

    if (Dem_GetEventStatus(0, &status) == DEM_OK) {
        printf("Event Status = %d\n", status);
    }

    return 0;
}
#endif