#ifndef COM_H
#define COM_H

#include "Std_Types.h"
#include "PDU_R.h"
#include "Det.h"

// Trạng thái trả về của COM
#define COM_OK         E_OK
#define COM_NOT_OK     E_NOT_OK

// Mã lỗi của COM
#define COM_E_PARAM_POINTER    0x01U  // Lỗi con trỏ NULL
#define COM_E_PARAM_CONFIG     0x02U  // Lỗi cấu hình không hợp lệ
#define COM_E_NOT_INITIALIZED  0x03U  // Module chưa khởi tạo

// Định nghĩa cấu hình cho COM
typedef struct {
    uint8 comChannel;  // Kênh giao tiếp (ví dụ: CAN Channel)
    uint8 signalId;    // ID của tín hiệu
    boolean isEnabled; // Trạng thái bật/tắt
} Com_ConfigType;

// Định nghĩa kiểu dữ liệu cho tín hiệu giao tiếp
typedef struct {
    uint16 signalValue; // Giá trị tín hiệu (ví dụ: nhiệt độ động cơ)
    uint16 signalId;    // ID của tín hiệu
} Com_SignalType;

// Định nghĩa kiểu dữ liệu cho PDU
typedef struct {
    PduIdType PduId;          // ID của PDU
    uint8* SduDataPtr;        // Con trỏ đến dữ liệu SDU
    PduLengthType SduLength;  // Độ dài SDU
} Com_PduType;

// Khởi tạo COM module
FUNC(void, COM_CODE) Com_Init(P2CONST(Com_ConfigType, AUTOMATIC, RTE_APPL_DATA) config);

// Gửi tín hiệu
FUNC(Std_ReturnType, COM_CODE) Com_SendSignal(Com_SignalIdType SignalId, P2CONST(void, AUTOMATIC, RTE_APPL_DATA) SignalDataPtr);

// Nhận tín hiệu
FUNC(Std_ReturnType, COM_CODE) Com_ReceiveSignal(Com_SignalIdType SignalId, P2VAR(void, AUTOMATIC, RTE_APPL_DATA) SignalDataPtr);

// Xử lý gói PDU
FUNC(Std_ReturnType, COM_CODE) Com_TriggerIPDUSend(PduIdType PduId);

#endif // COM_H
