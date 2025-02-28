#include "Com.h"
#include <stdio.h>

// Biến toàn cục mô phỏng tín hiệu giao tiếp
static Com_SignalType shared_signal = {0, 0}; // Giá trị ban đầu: 0, ID 0
static uint8 is_initialized = 0;              // Trạng thái khởi tạo

// Hàm khởi tạo module Com
void Com_Init(const Com_ConfigType* config) {
    if (config == NULL_PTR) {
        Det_ReportError(3, 0, 0, COM_E_PARAM_POINTER); // Báo lỗi AUTOSAR
        return;
    }

    if (config->isEnabled) {
        is_initialized = 1;
        printf("Com Module Initialized (Channel %d, Signal ID %d)\n",
               config->comChannel, config->signalId);
    } else {
        is_initialized = 0;
        Det_ReportError(3, 0, 0, COM_E_PARAM_CONFIG);
    }
}

// Hàm gửi tín hiệu giao tiếp (mô phỏng)
Std_ReturnType Com_SendSignal(Com_SignalType* signal) {
    if (!is_initialized) {
        Det_ReportError(3, 0, 1, COM_E_NOT_INITIALIZED);
        return COM_NOT_OK;
    }

    if (signal == NULL_PTR) {
        Det_ReportError(3, 0, 1, COM_E_PARAM_POINTER);
        return COM_NOT_OK;
    }

    // Mô phỏng gửi tín hiệu qua CAN (lưu vào biến toàn cục)
    shared_signal = *signal;
    printf("Com: Sent Signal - ID = %d, Value = %d\n",
           shared_signal.signalId, shared_signal.signalValue);
    return COM_OK;
}

// Hàm nhận tín hiệu giao tiếp (mô phỏng)
Std_ReturnType Com_ReceiveSignal(Com_SignalType* signal) {
    if (!is_initialized) {
        Det_ReportError(3, 0, 2, COM_E_NOT_INITIALIZED);
        return COM_NOT_OK;
    }

    if (signal == NULL_PTR) {
        Det_ReportError(3, 0, 2, COM_E_PARAM_POINTER);
        return COM_NOT_OK;
    }

    // Mô phỏng nhận tín hiệu từ CAN (đọc từ biến toàn cục)
    *signal = shared_signal;
    printf("Com: Received Signal - ID = %d, Value = %d\n",
           signal->signalId, signal->signalValue);
    return COM_OK;
}

// Hàm main để kiểm tra (chỉ dùng khi compile riêng)
#ifdef TEST_COM
int main(void) {
    Com_ConfigType config = {0, 1, 1}; // Channel 0, Signal ID 1, bật
    Com_SignalType send_signal = {75, 1}; // Giá trị 75, ID 1
    Com_SignalType receive_signal;

    Com_Init(&config);

    if (Com_SendSignal(&send_signal) == COM_OK) {
        printf("Signal sent successfully\n");
    }

    if (Com_ReceiveSignal(&receive_signal) == COM_OK) {
        printf("Signal received successfully: ID = %d, Value = %d\n",
               receive_signal.signalId, receive_signal.signalValue);
    }

    return 0;
}
#endif