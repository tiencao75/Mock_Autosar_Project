#include "Os.h"
#include <stdio.h>
#include <unistd.h> // Để sử dụng sleep cho mô phỏng thời gian

// Biến toàn cục mô phỏng danh sách task
static Os_TaskFunc tasks[10] = {NULL}; // Mảng mô phỏng tối đa 10 task
static uint8 is_initialized = 0;       // Trạng thái khởi tạo

// Hàm khởi tạo module Os
void Os_Init(const Os_ConfigType* config) {
    if (config == NULL_PTR) {
        Det_ReportError(7, 0, 0, OS_E_PARAM_POINTER); // Báo lỗi AUTOSAR
        return;
    }

    if (config->isEnabled) {
        is_initialized = 1;
        printf("Os Module Initialized (Task Priority %d, Period %d ms)\n",
               config->taskPriority, config->taskPeriod);
    } else {
        is_initialized = 0;
        Det_ReportError(7, 0, 0, OS_E_PARAM_CONFIG);
    }
}

// Hàm tạo và khởi chạy task (mô phỏng)
Std_ReturnType Os_CreateTask(Os_TaskIdType taskId, Os_TaskFunc taskFunc) {
    if (!is_initialized) {
        Det_ReportError(7, 0, 1, OS_E_NOT_INITIALIZED);
        return OS_NOT_OK;
    }

    if (taskId >= 10 || taskFunc == NULL) {
        Det_ReportError(7, 0, 1, OS_E_PARAM_TASK);
        return OS_NOT_OK;
    }

    tasks[taskId] = taskFunc;
    printf("Os: Created Task %d\n", taskId);
    return OS_OK;
}

// Hàm khởi chạy scheduler (mô phỏng)
Std_ReturnType Os_StartScheduler(void) {
    if (!is_initialized) {
        Det_ReportError(7, 0, 2, OS_E_NOT_INITIALIZED);
        return OS_NOT_OK;
    }

    printf("Os: Starting Scheduler...\n");
    while (1) {
        // Mô phỏng chạy các task theo thứ tự
        for (uint8 i = 0; i < 10; i++) {
            if (tasks[i] != NULL) {
                printf("Os: Executing Task %d\n", i);
                tasks[i](); // Thực thi task
                sleep(1);   // Mô phỏng thời gian thực thi (1 giây)
            }
        }
    }
    return OS_OK; // Không bao giờ đạt đến đây trong mô phỏng
}

// Hàm ví dụ cho task (mô phỏng)
void SampleTask(void) {
    printf("Sample Task: Running...\n");
}

// Hàm main để kiểm tra (chỉ dùng khi compile riêng)
#ifdef TEST_OS
int main(void) {
    Os_ConfigType config = {1, 100, 1}; // Priority 1, Period 100ms, bật

    Os_Init(&config);

    if (Os_CreateTask(0, SampleTask) == OS_OK) {
        printf("Task created successfully\n");
    }

    if (Os_StartScheduler() == OS_OK) {
        printf("Scheduler started successfully\n");
    }

    return 0;
}
#endif