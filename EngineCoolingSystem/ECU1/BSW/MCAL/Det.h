#ifndef DET_H
#define DET_H

#include "Compiler.h"    // Thêm Compiler.h
#include "Std_Types.h"

/* Macro báo lỗi */
#define DET_REPORT_ERROR(moduleId, instanceId, apiId, errorId) \
    Det_ReportError(moduleId, instanceId, apiId, errorId)

    
#define PDUR_E_PARAM_POINTER        0x09  /* Lỗi: Con trỏ NULL truyền vào hàm */
#define PDUR_E_NOT_INITIALIZED      0x0A  /* Lỗi: PDU Router chưa được khởi tạo */
#define PDUR_E_TRANSMIT_FAILED      0x0B
#define CANIF_E_PARAM_POINTER       0x11  /* Lỗi: Con trỏ NULL trong CAN */
#define CANIF_E_NOT_INITIALIZED     0x12  /* Lỗi: CAN Interface chưa được khởi tạo */
#define CAN_E_PARAM_POINTER         0x21  /* Lỗi: Con trỏ NULL trong CAN driver */
#define CAN_E_NOT_INITIALIZED       0x22  /* Lỗi: CAN driver chưa được khởi tạo */
#define CAN_E_PARAM_CONFIG 0x01  // Mã lỗi cho cấu hình không hợp lệ
#define CANIF_E_SEND_FAILED 0x02 
// Định nghĩa các mã lỗi cho RTE EngineTemperatureControl
#define RTE_E_PARAM_POINTER    0x01U  // Lỗi con trỏ NULL
#define RTE_E_PARAM_CONFIG     0x02U  // Lỗi cấu hình
#define RTE_E_NOT_INITIALIZED  0x03U  // Lỗi chưa khởi tạo
#define RTE_E_READ_FAILED      0x04U  // Lỗi đọc dữ liệu
#define RTE_E_SEND_FAILED      0x05U  // Lỗi gửi dữ liệu

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