#include "Com.h"
#include "Compiler.h"  // Thêm Compiler.h
#include <stdio.h>

/* Biến toàn cục mô phỏng tín hiệu */
STATIC VAR(Com_SignalType, COM_VAR) shared_signal = {0, 0};
STATIC VAR(uint8, COM_VAR) is_initialized = 0;

/* Hàm khởi tạo module Com */
FUNC(void, COM_CODE) Com_Init(
    P2CONST(Com_ConfigType, COM_CONST, AUTOMATIC) config
) {
    if (config == NULL_PTR) {
        Det_ReportError(3, 0, 0, COM_E_PARAM_POINTER);
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

/* Hàm gửi tín hiệu giao tiếp */
FUNC(Std_ReturnType, COM_CODE) Com_SendSignal(
    P2VAR(Com_SignalType, COM_VAR, AUTOMATIC) signal
) {
    if (!is_initialized) {
        Det_ReportError(3, 0, 1, COM_E_NOT_INITIALIZED);
        return COM_NOT_OK;
    }

    if (signal == NULL_PTR) {
        Det_ReportError(3, 0, 1, COM_E_PARAM_POINTER);
        return COM_NOT_OK;
    }

    shared_signal = *signal;
    printf("Com: Sent Signal - ID = %d, Value = %d\n",
           shared_signal.signalId, shared_signal.signalValue);
    return COM_OK;
}

/* Hàm nhận tín hiệu giao tiếp */
FUNC(Std_ReturnType, COM_CODE) Com_ReceiveSignal(
    P2VAR(Com_SignalType, COM_VAR, AUTOMATIC) signal
) {
    if (!is_initialized) {
        Det_ReportError(3, 0, 2, COM_E_NOT_INITIALIZED);
        return COM_NOT_OK;
    }

    if (signal == NULL_PTR) {
        Det_ReportError(3, 0, 2, COM_E_PARAM_POINTER);
        return COM_NOT_OK;
    }

    *signal = shared_signal;
    printf("Com: Received Signal - ID = %d, Value = %d\n",
           signal->signalId, signal->signalValue);
    return COM_OK;
}

/* Hàm main để kiểm tra */
#ifdef TEST_COM
FUNC(int, COM_CODE) main(void) {
    VAR(Com_ConfigType, AUTOMATIC) config = {0, 1, 1};
    VAR(Com_SignalType, AUTOMATIC) send_signal = {75, 1};
    VAR(Com_SignalType, AUTOMATIC) receive_signal;

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