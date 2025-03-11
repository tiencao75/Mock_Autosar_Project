#ifndef CAN_H
#define CAN_H

#include "Det.h"
#include "PDU_R.h"
#include "Compiler.h"  // Bao gồm Compiler.h để sử dụng các macro AUTOSAR
#include <stdint.h>

/*************************************************************************************
 * Định nghĩa cấu hình phần cứng CAN
 *************************************************************************************/
typedef struct {
    uint32_t bitrate;           // Tốc độ truyền CAN (bật/tắt tốc độ truyền)
    uint32_t controller_id;     // ID của bộ điều khiển CAN
    const void* hardware_config; // Cấu hình phần cứng của CAN
} Can_ConfigType;

/*************************************************************************************
 * Kiểu dữ liệu handle của phần cứng CAN
 *************************************************************************************/
typedef uint16 Can_HwHandleType;  // Kiểu dữ liệu đại diện cho handle của phần cứng CAN

/*************************************************************************************
 * Trạng thái của CAN
 *************************************************************************************/
typedef enum {
    CAN_STATE_UNINITIALIZED = 0,  // Chưa được khởi tạo
    CAN_STATE_INITIALIZED         // Đã được khởi tạo
} Can_StateType;

/*************************************************************************************
 * Kiểu dữ liệu đại diện cho ID của PDU trong hệ thống CAN
 *************************************************************************************/
typedef uint32 Can_IdType;

/*************************************************************************************
 * Cấu trúc PDU trong CAN
 *************************************************************************************/
typedef struct {
    PduIdType swPduHandle;  // Handle của PDU
    uint8 length;            // Độ dài của PDU (SduLength)
    Can_IdType id;          // ID của PDU (CanId)
    uint8* sdu;             // Dữ liệu của PDU (SduData)
} Can_PduType;

/*************************************************************************************
 * Hàm khởi tạo CAN
 *************************************************************************************/
FUNC(void, CAN_DRIVER_CODE)
Can_Init(P2CONST(Can_ConfigType, AUTOMATIC, RTE_APPL_DATA) ConfigPtr);

/*************************************************************************************
 * Hàm hủy khởi tạo CAN
 *************************************************************************************/
FUNC(void, CAN_DRIVER_CODE)
Can_DeInit(void);

/*************************************************************************************
 * Hàm ghi dữ liệu CAN
 *************************************************************************************/
FUNC(Std_ReturnType, CAN_DRIVER_CODE)
Can_Write(Can_HwHandleType Hth, P2CONST(Can_PduType, AUTOMATIC, RTE_APPL_DATA) PduInfoPtr);

#endif /* CAN_H */
