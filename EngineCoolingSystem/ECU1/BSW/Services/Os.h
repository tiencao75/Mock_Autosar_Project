#ifndef OS_H
#define OS_H

#include "Std_Types.h" // Bao gồm các kiểu dữ liệu AUTOSAR
#include "Det.h"       // Báo lỗi phát triển

// Trạng thái trả về cho Os
#define OS_OK       E_OK
#define OS_NOT_OK   E_NOT_OK

// Định nghĩa các mã lỗi cho Os
#define OS_E_PARAM_POINTER    0x01U  // Lỗi con trỏ NULL
#define OS_E_PARAM_CONFIG     0x02U  // Lỗi cấu hình
#define OS_E_NOT_INITIALIZED  0x03U  // Lỗi chưa khởi tạo
#define OS_E_PARAM_TASK       0x04U  // Lỗi task không hợp lệ

// Định nghĩa cấu hình cho Os
typedef struct {
    uint8 taskPriority;  // Ưu tiên task
    uint16 taskPeriod;   // Chu kỳ thực thi task (ms)
    boolean isEnabled;   // Trạng thái bật/tắt
} Os_ConfigType;

// Định nghĩa kiểu dữ liệu cho task
typedef void (*Os_TaskFunc)(void); // Con trỏ đến hàm task

// Định nghĩa ID task
typedef uint8 Os_TaskIdType;

// Hàm khởi tạo module Os
void Os_Init(const Os_ConfigType* config);

// Hàm tạo và khởi chạy task (mô phỏng)
Std_ReturnType Os_CreateTask(Os_TaskIdType taskId, Os_TaskFunc taskFunc);

// Hàm khởi chạy scheduler (mô phỏng)
Std_ReturnType Os_StartScheduler(void);

#endif // OS_H