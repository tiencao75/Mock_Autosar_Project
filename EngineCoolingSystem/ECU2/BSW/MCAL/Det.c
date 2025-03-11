#include "Det.h"
#include "Compiler.h"  // Thêm Compiler.h
#include <stdio.h>

/* Hàm báo lỗi phát triển (mô phỏng) */
FUNC(void, DET_CODE) Det_ReportError(
    VAR(uint8, DET_VAR) ModuleId,
    VAR(uint8, DET_VAR) InstanceId,
    VAR(uint8, DET_VAR) ApiId,
    VAR(uint8, DET_VAR) ErrorId
) {
    /*printf("DET Error: Module = %u, Instance = %u, API = %u, Error = %u\n",
           ModuleId, InstanceId, ApiId, ErrorId);*/
}