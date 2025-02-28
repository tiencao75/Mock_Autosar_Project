#include "Det.h"
#include <stdio.h>

/* Hàm báo lỗi phát triển (mô phỏng bằng cách in thông báo) */
void Det_ReportError(uint8 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId) {
    printf("DET Error: Module = %u, Instance = %u, API = %u, Error = %u\n",
           ModuleId, InstanceId, ApiId, ErrorId);
}