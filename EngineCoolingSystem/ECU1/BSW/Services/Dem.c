#include "Dem.h"
#include "Compiler.h"  // Thêm Compiler.h
#include <stdio.h>

/* Biến toàn cục mô phỏng danh sách sự kiện */
STATIC VAR(Dem_EventType, DEM_VAR) events[10] = {0};
STATIC VAR(uint8, DEM_VAR) is_initialized = 0;

/* Hàm khởi tạo module Dem */
FUNC(void, DEM_CODE) Dem_Init(
    P2CONST(Dem_ConfigType, DEM_CONST, AUTOMATIC) config
) {
    if (config == NULL_PTR) {
        Det_ReportError(5, 0, 0, DEM_E_PARAM_POINTER);
        return;
    }

    if (config->isEnabled) {
        is_initialized = 1;
        for (VAR(uint8, AUTOMATIC) i = 0; i < 10; i++) {
            events[i].eventId = i;
            events[i].status = 0;
            events[i].occurrence = 0;
        }
        printf("Dem Module Initialized (Event ID %d, Severity %d)\n",
               config->eventId, config->severity);
    } else {
        is_initialized = 0;
        Det_ReportError(5, 0, 0, DEM_E_PARAM_CONFIG);
    }
}

/* Hàm báo cáo sự kiện chẩn đoán */
FUNC(Std_ReturnType, DEM_CODE) Dem_ReportEvent(
    VAR(uint8, DEM_VAR) eventId,
    VAR(uint8, DEM_VAR) status
) {
    if (!is_initialized) {
        Det_ReportError(5, 0, 1, DEM_E_NOT_INITIALIZED);
        return DEM_NOT_OK;
    }

    if (eventId >= 10) {
        Det_ReportError(5, 0, 1, DEM_E_PARAM_EVENT_ID);
        return DEM_NOT_OK;
    }

    events[eventId].status = status;
    if (status == 1) {
        events[eventId].occurrence++;
    }
    printf("Dem: Reported Event - ID = %d, Status = %d, Occurrences = %d\n",
           eventId, status, events[eventId].occurrence);
    return DEM_OK;
}

/* Hàm đọc trạng thái sự kiện */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventStatus(
    VAR(uint8, DEM_VAR) eventId,
    P2VAR(uint8, DEM_VAR, AUTOMATIC) status
) {
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

/* Hàm main để kiểm tra */
#ifdef TEST_DEM
FUNC(int, DEM_CODE) main(void) {
    VAR(Dem_ConfigType, AUTOMATIC) config = {0, 1, 1};
    VAR(uint8, AUTOMATIC) status;

    Dem_Init(&config);

    if (Dem_ReportEvent(0, 1) == DEM_OK) {
        printf("Event reported successfully\n");
    }

    if (Dem_GetEventStatus(0, &status) == DEM_OK) {
        printf("Event Status = %d\n", status);
    }

    return 0;
}
#endif