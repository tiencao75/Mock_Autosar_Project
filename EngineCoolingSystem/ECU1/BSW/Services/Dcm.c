#include "Dcm.h"
#include <stdio.h>
#include <string.h>

// Biến toàn cục mô phỏng trạng thái Dcm
static uint8 is_initialized = 0;         // Trạng thái khởi tạo
static uint8 current_session = 0;        // Phiên chẩn đoán hiện tại

// Hàm khởi tạo module Dcm
void Dcm_Init(const Dcm_ConfigType* config) {
    if (config == NULL_PTR) {
        Det_ReportError(4, 0, 0, DCM_E_PARAM_POINTER); // Báo lỗi AUTOSAR
        return;
    }

    if (config->isEnabled) {
        is_initialized = 1;
        current_session = config->sessionId;
        printf("Dcm Module Initialized (Session ID %d, Protocol %d)\n",
               config->sessionId, config->protocol);
    } else {
        is_initialized = 0;
        Det_ReportError(4, 0, 0, DCM_E_PARAM_CONFIG);
    }
}

// Hàm xử lý yêu cầu chẩn đoán (mô phỏng)
Std_ReturnType Dcm_ProcessRequest(const Dcm_RequestType* request, Dcm_ResponseType* response) {
    if (!is_initialized) {
        Det_ReportError(4, 0, 1, DCM_E_NOT_INITIALIZED);
        return DCM_NOT_OK;
    }

    if (request == NULL_PTR || response == NULL_PTR) {
        Det_ReportError(4, 0, 1, DCM_E_PARAM_POINTER);
        return DCM_NOT_OK;
    }

    // Mô phỏng xử lý yêu cầu chẩn đoán
    printf("Dcm: Processing Request - ID = 0x%02X, Length = %d, Data = ",
           request->requestId, request->dataLength);
    for (uint8 i = 0; i < request->dataLength; i++) {
        printf("0x%02X ", request->data[i]);
    }
    printf("\n");

    // Mô phỏng phản hồi (giả định phản hồi đơn giản)
    response->responseId = request->requestId + 0x40; // Ví dụ: 0x10 -> 0x50
    response->dataLength = 2;
    response->data = (uint8*)malloc(response->dataLength * sizeof(uint8));
    if (response->data == NULL_PTR) {
        Det_ReportError(4, 0, 1, DCM_E_MEMORY);
        return DCM_NOT_OK;
    }

    response->data[0] = 0x01; // Dữ liệu phản hồi giả lập
    response->data[1] = 0x00;

    printf("Dcm: Response - ID = 0x%02X, Length = %d, Data = ",
           response->responseId, response->dataLength);
    for (uint8 i = 0; i < response->dataLength; i++) {
        printf("0x%02X ", response->data[i]);
    }
    printf("\n");

    return DCM_OK;
}

// Hàm main để kiểm tra (chỉ dùng khi compile riêng)
#ifdef TEST_DCM
int main(void) {
    Dcm_ConfigType config = {1, 1, 1}; // Session ID 1, Protocol 1, bật
    Dcm_RequestType request;
    Dcm_ResponseType response;

    // Khởi tạo dữ liệu yêu cầu
    request.requestId = 0x10; // Diagnostic Session Control
    request.dataLength = 1;
    request.data = (uint8*)malloc(request.dataLength * sizeof(uint8));
    request.data[0] = 0x01; // Dữ liệu giả lập

    Dcm_Init(&config);

    if (Dcm_ProcessRequest(&request, &response) == DCM_OK) {
        printf("DCM Request processed successfully\n");
    }

    // Giải phóng bộ nhớ
    free(request.data);
    free(response.data);

    return 0;
}
#endif