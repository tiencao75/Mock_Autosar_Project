#include "Dcm.h"
#include "Compiler.h"  // Thêm Compiler.h
#include <stdio.h>
#include <string.h>

/* Biến toàn cục mô phỏng trạng thái */
STATIC VAR(uint8, DCM_VAR) is_initialized = 0;
STATIC VAR(uint8, DCM_VAR) current_session = 0;

/* Hàm khởi tạo module Dcm */
FUNC(void, DCM_CODE) Dcm_Init(
    P2CONST(Dcm_ConfigType, DCM_CONST, AUTOMATIC) config
) {
    if (config == NULL_PTR) {
        Det_ReportError(4, 0, 0, DCM_E_PARAM_POINTER);
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

/* Hàm xử lý yêu cầu chẩn đoán */
FUNC(Std_ReturnType, DCM_CODE) Dcm_ProcessRequest(
    P2CONST(Dcm_RequestType, DCM_CONST, AUTOMATIC) request,
    P2VAR(Dcm_ResponseType, DCM_VAR, AUTOMATIC) response
) {
    if (!is_initialized) {
        Det_ReportError(4, 0, 1, DCM_E_NOT_INITIALIZED);
        return DCM_NOT_OK;
    }

    if (request == NULL_PTR || response == NULL_PTR) {
        Det_ReportError(4, 0, 1, DCM_E_PARAM_POINTER);
        return DCM_NOT_OK;
    }

    printf("Dcm: Processing Request - ID = 0x%02X, Length = %d, Data = ",
           request->requestId, request->dataLength);
    for (VAR(uint8, AUTOMATIC) i = 0; i < request->dataLength; i++) {
        printf("0x%02X ", request->data[i]);
    }
    printf("\n");

    response->responseId = request->requestId + 0x40;
    response->dataLength = 2;
    response->data = (P2VAR(uint8, DCM_VAR, AUTOMATIC))malloc(response->dataLength * sizeof(uint8));
    if (response->data == NULL_PTR) {
        Det_ReportError(4, 0, 1, DCM_E_MEMORY);
        return DCM_NOT_OK;
    }

    response->data[0] = 0x01;
    response->data[1] = 0x00;

    printf("Dcm: Response - ID = 0x%02X, Length = %d, Data = ",
           response->responseId, response->dataLength);
    for (VAR(uint8, AUTOMATIC) i = 0; i < response->dataLength; i++) {
        printf("0x%02X ", response->data[i]);
    }
    printf("\n");

    return DCM_OK;
}

/* Hàm main để kiểm tra */
#ifdef TEST_DCM
FUNC(int, DCM_CODE) main(void) {
    VAR(Dcm_ConfigType, AUTOMATIC) config = {1, 1, 1};
    VAR(Dcm_RequestType, AUTOMATIC) request;
    VAR(Dcm_ResponseType, AUTOMATIC) response;

    request.requestId = 0x10;
    request.dataLength = 1;
    request.data = (P2VAR(uint8, DCM_VAR, AUTOMATIC))malloc(request.dataLength * sizeof(uint8));
    request.data[0] = 0x01;

    Dcm_Init(&config);

    if (Dcm_ProcessRequest(&request, &response) == DCM_OK) {
        printf("DCM Request processed successfully\n");
    }

    free(request.data);
    free(response.data);

    return 0;
}
#endif