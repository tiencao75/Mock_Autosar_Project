#ifndef DET_H
#define DET_H

#include "Std_Types.h"

/* Định nghĩa các mã lỗi */
#define DET_REPORT_ERROR(moduleId, instanceId, apiId, errorId) \
    Det_ReportError(moduleId, instanceId, apiId, errorId)

/* Hàm báo lỗi phát triển (mô phỏng) */
void Det_ReportError(uint8 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);

#endif // DET_H