#ifndef CANIF_H
#define CANIF_H

#include "Std_Types.h"
#include "Det.h"
#include "PDU_R.h"
#include "Can.h"
#include "Compiler.h"  // Bao gồm Compiler.h để sử dụng các macro AUTOSAR

/* Định nghĩa kiểu dữ liệu cấu hình CAN Interface */
typedef struct {
    uint8 comChannel;     // Kênh giao tiếp (ví dụ: CAN Channel)
    uint16 MaxPduCount;   // Số lượng tối đa các PDU có thể truyền
} CanIf_ConfigType;

/* Khai báo các hàm */

/*************************************************************************************
 * Name       : CanIf_Init
 * Param      : config - Con trỏ đến cấu hình CAN Interface
 * Return     : None
 * Contents   : Hàm khởi tạo CAN Interface với cấu hình đã cho
 * Author     : 
 * Note       : Hàm này kiểm tra tính hợp lệ của cấu hình và khởi tạo CAN Interface
 *************************************************************************************/
FUNC(void, CANIF_CODE)
CanIf_Init(P2CONST(CanIf_ConfigType, AUTOMATIC, RTE_APPL_DATA) config);

/*************************************************************************************
 * Name       : CanIf_DeInit
 * Param      : None
 * Return     : None
 * Contents   : Hàm hủy khởi tạo CAN Interface
 * Author     : 
 * Note       : Hàm này sẽ hủy khởi tạo và giải phóng tài nguyên của CAN Interface.
 *************************************************************************************/
FUNC(void, CANIF_CODE)
CanIf_DeInit(void);

/*************************************************************************************
 * Name       : CanIf_Transmit
 * Param      : TxPduId     - ID của PDU cần truyền
 *              PduInfoPtr  - Con trỏ đến dữ liệu PDU cần truyền
 * Return     : E_OK nếu truyền thành công, E_NOT_OK nếu có lỗi
 * Contents   : Truyền dữ liệu PDU thông qua CAN Interface
 * Author     : 
 * Note       : Hàm này gửi tín hiệu PDU qua CAN Interface.
 *************************************************************************************/
FUNC(Std_ReturnType, CANIF_CODE)
CanIf_Transmit(PduIdType TxPduId, P2CONST(PduInfoType, AUTOMATIC, RTE_APPL_DATA) PduInfoPtr);

#endif /* CANIF_H */
