#ifndef DIO_H
#define DIO_H

#include "Compiler.h"    // Thêm Compiler.h
#include "Std_Types.h"   // Kiểu dữ liệu chuẩn AUTOSAR
#include "Det.h"         // Báo lỗi phát triển

/* Trạng thái trả về cho Dio */
#define DIO_OK       E_OK
#define DIO_NOT_OK   E_NOT_OK

/* Định nghĩa các mã lỗi */
#define DIO_E_PARAM_POINTER    0x01U  // Lỗi con trỏ NULL
#define DIO_E_PARAM_CONFIG     0x02U  // Lỗi cấu hình
#define DIO_E_NOT_INITIALIZED  0x03U  // Lỗi chưa khởi tạo
#define DIO_E_PARAM_CHANNEL    0x04U  // Lỗi kênh không hợp lệ
#define DIO_E_PARAM_LEVEL      0x05U  // Lỗi mức tín hiệu không hợp lệ

/* Định nghĩa cấu hình cho Dio */
typedef struct {
    VAR(uint8, DIO_VAR) channelId;    // ID kênh I/O (ví dụ: chân GPIO)
    VAR(boolean, DIO_VAR) isOutput;   // Là đầu ra hay đầu vào
    VAR(boolean, DIO_VAR) isEnabled;  // Trạng thái bật/tắt
} Dio_ConfigType;

/* Định nghĩa kiểu kênh Dio */
typedef VAR(uint8, DIO_VAR) Dio_ChannelType;

/* Định nghĩa mức tín hiệu */
typedef enum {
    DIO_LOW  = 0U,  // Mức thấp (0V)
    DIO_HIGH = 1U   // Mức cao (3.3V/5V)
} Dio_LevelType;

/* Khai báo hàm */
FUNC(void, DIO_CODE) Dio_Init(
    P2CONST(Dio_ConfigType, DIO_CONST, AUTOMATIC) config
);

FUNC(Dio_LevelType, DIO_CODE) Dio_ReadChannel(
    VAR(Dio_ChannelType, DIO_VAR) channelId
);

FUNC(Std_ReturnType, DIO_CODE) Dio_WriteChannel(
    VAR(Dio_ChannelType, DIO_VAR) channelId,
    VAR(Dio_LevelType, DIO_VAR) level
);

#endif /* DIO_H */