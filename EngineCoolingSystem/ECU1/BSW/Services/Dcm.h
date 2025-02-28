#ifndef DCM_H
#define DCM_H

#include "Std_Types.h" // Bao gồm các kiểu dữ liệu AUTOSAR
#include "Det.h"       // Báo lỗi phát triển

// Trạng thái trả về cho Dcm
#define DCM_OK       E_OK
#define DCM_NOT_OK   E_NOT_OK

// Định nghĩa các mã lỗi cho Dcm
#define DCM_E_PARAM_POINTER    0x01U  // Lỗi con trỏ NULL
#define DCM_E_PARAM_CONFIG     0x02U  // Lỗi cấu hình
#define DCM_E_NOT_INITIALIZED  0x03U  // Lỗi chưa khởi tạo
#define DCM_E_MEMORY           0x04U  // Lỗi bộ nhớ

// Định nghĩa cấu hình cho Dcm
typedef struct {
    uint8 sessionId;     // ID phiên chẩn đoán
    uint8 protocol;      // Giao thức chẩn đoán (ví dụ: UDS, KWP2000)
    boolean isEnabled;   // Trạng thái bật/tắt
} Dcm_ConfigType;

// Định nghĩa kiểu dữ liệu cho yêu cầu chẩn đoán
typedef struct {
    uint8 requestId;     // ID yêu cầu chẩn đoán (ví dụ: 0x10 - Diagnostic Session Control)
    uint8 dataLength;    // Độ dài dữ liệu
    uint8* data;         // Dữ liệu yêu cầu
} Dcm_RequestType;

// Định nghĩa kiểu dữ liệu cho phản hồi chẩn đoán
typedef struct {
    uint8 responseId;    // ID phản hồi
    uint8 dataLength;    // Độ dài dữ liệu phản hồi
    uint8* data;         // Dữ liệu phản hồi
} Dcm_ResponseType;

// Hàm khởi tạo module Dcm
void Dcm_Init(const Dcm_ConfigType* config);

// Hàm xử lý yêu cầu chẩn đoán (mô phỏng)
Std_ReturnType Dcm_ProcessRequest(const Dcm_RequestType* request, Dcm_ResponseType* response);

#endif // DCM_H