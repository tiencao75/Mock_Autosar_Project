#include "Com.h"
#include <stdio.h>

// Biến toàn cục mô phỏng trạng thái
STATIC VAR(uint8, COM_VAR) is_initialized = 0;  // Trạng thái khởi tạo
P2VAR(PduInfoType, AUTOMATIC, RTE_APPL_DATA) PduInfo;
STATIC VAR(Com_SignalType, COM_VAR) shared_signal = {0, 0};

/******************************************************************************
 * Name       : Com_Init
 * Param      : config : Pointer to the configuration for the COM module
 * Return     : None
 * Contents   : Initializes the COM module with the provided configuration
 * Author     : 
 * Note       : This function checks if the configuration is valid and initializes
 *              the COM module accordingly. It also reports errors if the config
 *              is invalid or NULL.
 ******************************************************************************/
FUNC(void, COM_CODE)
Com_Init(P2CONST(Com_ConfigType, AUTOMATIC, RTE_APPL_DATA) config) {
    if (config == NULL_PTR) {
        Det_ReportError(3, 0, 0, COM_E_PARAM_POINTER);
        return;
    }

    if (config->isEnabled) {
        is_initialized = 1;
    } else {
        is_initialized = 0;
        Det_ReportError(3, 0, 0, COM_E_PARAM_CONFIG);
    }
}


/******************************************************************************
 * Name       : Com_SendSignal
 * Param      : SignalId      : ID của tín hiệu cần gửi
 *              SignalDataPtr : Con trỏ đến dữ liệu tín hiệu cần gửi
 * Return     : Status        : COM_OK nếu gửi tín hiệu thành công, COM_NOT_OK nếu thất bại
 * Contents   : Gửi tín hiệu được cung cấp bằng cách sử dụng module COM
 * Author     : 
 * Note       : Hàm này kiểm tra trạng thái khởi tạo của COM module và xác minh tính hợp lệ 
 *              của con trỏ dữ liệu tín hiệu. Sau đó, hàm mô phỏng việc gửi tín hiệu và lưu 
 *              tín hiệu trong biến shared_signal.
 ******************************************************************************/
FUNC(Std_ReturnType, COM_CODE)
Com_SendSignal(Com_SignalIdType SignalId, P2CONST(void, AUTOMATIC, RTE_APPL_DATA) SignalDataPtr) {
 
    if (SignalDataPtr == NULL_PTR) {
        Det_ReportError(3, 0, 1, COM_E_PARAM_POINTER);  // Báo lỗi nếu con trỏ dữ liệu tín hiệu bị NULL
        return COM_NOT_OK;
    }

  // Chuẩn bị dữ liệu tín hiệu cho PDU Router
    PduInfoType PduInfo;
    PduInfo.SduLength = sizeof(SignalDataPtr);  // Độ dài dữ liệu tín hiệu
    PduInfo.SduDataPtr = (uint8*)SignalDataPtr;  // Trỏ đến dữ liệu tín hiệu trong SignalDataPtr

    // Gọi PDU Router để xử lý truyền dữ liệu
    // Giả sử PduId sẽ được tự động xử lý hoặc có thể bỏ qua nếu không cần thiết
    if (PduR_UserUpTransmit(SignalId, &PduInfo) == E_OK) {  // Sử dụng 0 hoặc một giá trị mặc định cho PDU ID
        // printf("Com: Sent Signal - ID = %d, Value = %d\n", shared_signal.signalId, shared_signal.signalValue);
        return COM_OK;
    } else {
        Det_ReportError(3, 0, 3, COM_E_PARAM_CONFIG);  // Báo lỗi nếu có sự cố với PDU Router
        return COM_NOT_OK;
    }
}


/******************************************************************************
 * Tên        : Com_ReceiveSignal
 * Tham số    : SignalId : ID của tín hiệu cần nhận
 *              SignalDataPtr : Con trỏ đến vị trí nơi dữ liệu tín hiệu nhận được sẽ được lưu trữ
 * Trả về     : COM_OK nếu tín hiệu được nhận thành công
 *              COM_NOT_OK nếu có lỗi (ví dụ: chưa được khởi tạo hoặc con trỏ không hợp lệ)
 * Nội dung   : Nhận tín hiệu và lưu trữ nó tại vị trí chỉ định
 * Tác giả    : 
 * Ghi chú    : Hàm này kiểm tra xem module COM đã được khởi tạo chưa và xác minh
 *              tính hợp lệ của con trỏ tín hiệu. Sau đó, hàm mô phỏng việc nhận tín hiệu
 *              và sao chép dữ liệu tín hiệu vào vị trí được chỉ định bởi SignalDataPtr.
 ******************************************************************************/
Std_ReturnType Com_ReceiveSignal(Com_SignalIdType SignalId, void* SignalDataPtr) {
    if (!is_initialized) {
        Det_ReportError(3, 0, 2, COM_E_NOT_INITIALIZED);  // Báo lỗi nếu COM chưa được khởi tạo
        return COM_NOT_OK;
    }

    if (SignalDataPtr == NULL_PTR) {
        Det_ReportError(3, 0, 2, COM_E_PARAM_POINTER);  // Báo lỗi nếu con trỏ dữ liệu tín hiệu bị NULL
        return COM_NOT_OK;
    }

    // Mô phỏng việc nhận tín hiệu và sao chép dữ liệu vào con trỏ được cung cấp
    ((Com_SignalType*)SignalDataPtr)->signalId = shared_signal.signalId;
    ((Com_SignalType*)SignalDataPtr)->signalValue = shared_signal.signalValue;



    return COM_OK;
}


