#ifndef DCM_H
#define DCM_H

#include "Compiler.h"    // Thêm Compiler.h
#include "Std_Types.h"   // Kiểu dữ liệu chuẩn AUTOSAR
#include "Det.h"         // Báo lỗi phát triển

/* Trạng thái trả về cho Dcm */
#define DCM_OK       E_OK
#define DCM_NOT_OK   E_NOT_OK

/* Định nghĩa các mã lỗi */
#define DCM_E_PARAM_POINTER    0x01U  // Lỗi con trỏ NULL
#define DCM_E_PARAM_CONFIG     0x02U  // Lỗi cấu hình
#define DCM_E_NOT_INITIALIZED  0x03U  // Lỗi chưa khởi tạo
#define DCM_E_MEMORY           0x04U  // Lỗi bộ nhớ

/* Cấu trúc cấu hình cho Dcm */
typedef struct {
    VAR(uint8, DCM_VAR) sessionId;     // ID phiên chẩn đoán
    VAR(uint8, DCM_VAR) protocol;      // Giao thức chẩn đoán
    VAR(boolean, DCM_VAR) isEnabled;   // Trạng thái bật/tắt
} Dcm_ConfigType;

/* Kiểu dữ liệu cho yêu cầu chẩn đoán */
typedef struct {
    VAR(uint8, DCM_VAR) requestId;     // ID yêu cầu chẩn đoán
    VAR(uint8, DCM_VAR) dataLength;    // Độ dài dữ liệu
    P2VAR(uint8, DCM_VAR, AUTOMATIC) data; // Dữ liệu yêu cầu
} Dcm_RequestType;

/* Kiểu dữ liệu cho phản hồi chẩn đoán */
typedef struct {
    VAR(uint8, DCM_VAR) responseId;    // ID phản hồi
    VAR(uint8, DCM_VAR) dataLength;    // Độ dài dữ liệu phản hồi
    P2VAR(uint8, DCM_VAR, AUTOMATIC) data; // Dữ liệu phản hồi
} Dcm_ResponseType;

/* Khai báo hàm */
FUNC(void, DCM_CODE) Dcm_Init(
    P2CONST(Dcm_ConfigType, DCM_CONST, AUTOMATIC) config
);

FUNC(Std_ReturnType, DCM_CODE) Dcm_ProcessRequest(
    P2CONST(Dcm_RequestType, DCM_CONST, AUTOMATIC) request,
    P2VAR(Dcm_ResponseType, DCM_VAR, AUTOMATIC) response
);

#endif /* DCM_H */