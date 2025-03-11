#include "Dio.h"
#include "Compiler.h"  // Thêm Compiler.h
#include <stdio.h>

/* Biến toàn cục mô phỏng trạng thái Dio */
STATIC VAR(uint8, DIO_VAR) dio_channels[8] = {DIO_LOW}; // Mô phỏng 8 kênh, mặc định LOW
STATIC VAR(uint8, DIO_VAR) is_initialized = 0;          // Trạng thái khởi tạo

/* Hàm khởi tạo module Dio */
FUNC(void, DIO_CODE) Dio_Init(
    P2CONST(Dio_ConfigType, DIO_CONST, AUTOMATIC) config
) {
    if (config == NULL_PTR) {
        Det_ReportError(10, 0, 0, DIO_E_PARAM_POINTER);
        return;
    }

    if (config->isEnabled) {
        is_initialized = 1;
        if (config->channelId < 8) { // Giả định chỉ hỗ trợ 8 kênh
            dio_channels[config->channelId] = config->isOutput ? DIO_LOW : DIO_LOW;
            printf("Dio: Initialized Channel %d (Output: %d)\n",
                   config->channelId, config->isOutput);
        } else {
            Det_ReportError(10, 0, 0, DIO_E_PARAM_CHANNEL);
        }
    } else {
        is_initialized = 0;
        Det_ReportError(10, 0, 0, DIO_E_PARAM_CONFIG);
    }
}

/* Hàm đọc trạng thái kênh */
FUNC(Dio_LevelType, DIO_CODE) Dio_ReadChannel(
    VAR(Dio_ChannelType, DIO_VAR) channelId
) {
    if (!is_initialized) {
        Det_ReportError(10, 0, 1, DIO_E_NOT_INITIALIZED);
        return DIO_LOW; // Giá trị mặc định khi lỗi
    }

    if (channelId >= 8) {
        Det_ReportError(10, 0, 1, DIO_E_PARAM_CHANNEL);
        return DIO_LOW;
    }

    printf("Dio: Read Channel %d = %d\n", channelId, dio_channels[channelId]);
    return (Dio_LevelType)dio_channels[channelId];
}

/* Hàm ghi giá trị vào kênh */
FUNC(Std_ReturnType, DIO_CODE) Dio_WriteChannel(
    VAR(Dio_ChannelType, DIO_VAR) channelId,
    VAR(Dio_LevelType, DIO_VAR) level
) {
    if (!is_initialized) {
        Det_ReportError(10, 0, 2, DIO_E_NOT_INITIALIZED);
        return DIO_NOT_OK;
    }

    if (channelId >= 8) {
        Det_ReportError(10, 0, 2, DIO_E_PARAM_CHANNEL);
        return DIO_NOT_OK;
    }

    if (level != DIO_LOW && level != DIO_HIGH) {
        Det_ReportError(10, 0, 2, DIO_E_PARAM_LEVEL);
        return DIO_NOT_OK;
    }

    dio_channels[channelId] = level;
    printf("Dio: Wrote Channel %d = %d\n", channelId, level);
    return DIO_OK;
}

/* Hàm main để kiểm tra */
#ifdef TEST_DIO
FUNC(int, DIO_CODE) main(void) {
    VAR(Dio_ConfigType, AUTOMATIC) config = {0, 1, 1}; // Channel 0, Output, bật
    VAR(Dio_LevelType, AUTOMATIC) level;

    Dio_Init(&config);

    // Đọc trạng thái kênh
    level = Dio_ReadChannel(0);
    printf("Channel 0 State = %d\n", level);

    // Ghi mức HIGH vào kênh 0
    if (Dio_WriteChannel(0, DIO_HIGH) == DIO_OK) {
        printf("Channel 0 set to HIGH successfully\n");
    }

    // Đọc lại trạng thái
    level = Dio_ReadChannel(0);
    printf("Updated Channel 0 State = %d\n", level);

    return 0;
}
#endif