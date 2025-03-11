#ifndef DET_H
#define DET_H

#include "Compiler.h"    // Thêm Compiler.h
#include "Std_Types.h"

/* Macro báo lỗi */
#define DET_REPORT_ERROR(moduleId, instanceId, apiId, errorId) \
    Det_ReportError(moduleId, instanceId, apiId, errorId)

/* Khai báo hàm */
FUNC(void, DET_CODE) Det_ReportError(
    VAR(uint8, DET_VAR) ModuleId,
    VAR(uint8, DET_VAR) InstanceId,
    VAR(uint8, DET_VAR) ApiId,
    VAR(uint8, DET_VAR) ErrorId
);

#endif /* DET_H */