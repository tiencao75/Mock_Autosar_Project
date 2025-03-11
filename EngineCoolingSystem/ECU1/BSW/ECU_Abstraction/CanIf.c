#include "CanIf.h"
#include "Det.h"
#include <stdio.h>
volatile uint8 TrackedSdu;
// Biến toàn cục volatile để theo dõi từng tín hiệu
volatile uint16 TrackedFanSpeed;    // Theo dõi FanSpeed (16 bit)
volatile uint16 TrackedPumpSpeed;   // Theo dõi PumpSpeed (16 bit)
volatile uint8 TrackedWarningStatus; // Theo dõi warningStatus (8 bit)


// Biến toàn cục lưu trạng thái và cấu hình của CAN Interface
STATIC VAR( CanIf_ConfigType, CANIF_VAR) CanIf_Config;
STATIC VAR(uint8, COM_VAR) CanIf_State = 0;  // Trạng thái khởi tạo (0: Chưa khởi tạo, 1: Đã khởi tạo)

/******************************************************************************
 * Name       : CanIf_Init
 * Param      : config : Cấu hình cho CanIf (CanIf_ConfigType)
 * Return     : None
 * Contents   : Hàm khởi tạo CanIf với cấu hình được cung cấp
 * Author     : 
 * Note       : Khởi tạo thông tin cấu hình và thay đổi trạng thái của CanIf
 ******************************************************************************/
FUNC(void, CANIF_CODE)
CanIf_Init(P2CONST(CanIf_ConfigType, AUTOMATIC, RTE_APPL_DATA) configPtr) {
    // Kiểm tra xem con trỏ cấu hình có hợp lệ không
    if (configPtr == NULL_PTR) {
        Det_ReportError(1, 0, 0, CANIF_E_PARAM_POINTER);  // Báo lỗi nếu con trỏ NULL
        return;
    }

    // Lưu cấu hình vào biến toàn cục và thay đổi trạng thái CAN Interface
    CanIf_Config = *configPtr;
    CanIf_State = 1;  // Đánh dấu đã khởi tạo
    // printf("CanIf: Đã khởi tạo với cấu hình - Channel: %d, MaxPduCount: %d\n", 
    //        CanIf_Config.comChannel, CanIf_Config.MaxPduCount);
}

/******************************************************************************
 * Name       : CanIf_Transmit
 * Param      : TxPduId    - ID của PDU cần truyền
 *              PduInfoPtr - Con trỏ đến dữ liệu PDU cần truyền
 * Return     : E_OK nếu truyền thành công, E_NOT_OK nếu có lỗi
 * Contents   : Truyền dữ liệu PDU thông qua CanIf
 * Author     : 
 * Note       : Hàm này thực hiện việc gửi dữ liệu CAN qua PDU Interface
 ******************************************************************************/
FUNC(Std_ReturnType, CANIF_CODE)
CanIf_Transmit(PduIdType TxPduId, P2CONST(PduInfoType, AUTOMATIC, RTE_APPL_DATA) PduInfoPtr) {
    // Kiểm tra xem dữ liệu PDU có hợp lệ không
    if (PduInfoPtr == NULL_PTR) {
        Det_ReportError(1, 0, 1, CANIF_E_PARAM_POINTER);  // Báo lỗi nếu con trỏ NULL
        return E_NOT_OK;
    }

    // Truy cập dữ liệu thô từ PduInfoPtr->SduDataPtr (kiểu uint8*)
    const uint8* dataPtr = PduInfoPtr->SduDataPtr;
		
		
		// Gán giá trị vào các biến volatile theo dõi (big-endian: byte cao trước, byte thấp sau)
    TrackedFanSpeed = (dataPtr[1] << 8) | dataPtr[0];  // 2 byte đầu cho FanSpeed
    TrackedPumpSpeed = (dataPtr[3] << 8) | dataPtr[2]; // 2 byte tiếp theo cho PumpSpeed
    TrackedWarningStatus = dataPtr[4];                 // 1 byte cuối cho warningStatus


    // Ở đây, gọi hàm Can_Write để thực sự truyền dữ liệu CAN qua hệ thống phần cứng
    // Giả sử Hth là Handle truyền thông phần cứng (có thể nhận từ PduInfoPtr hoặc xác định trước)
    Can_HwHandleType Hth = 5;  // Giả sử Hth được lấy từ một nguồn hợp lý nào đó
    Can_IdType CanID = 07;
    Can_PduType CanPdu;

    // Chuyển PduInfoPtr sang PduType để phù hợp với Can_Write
    CanPdu.swPduHandle = TxPduId;  // Giả sử lấy ID từ dữ liệu PDU
    CanPdu.length = PduInfoPtr->SduLength;  // Độ dài
    CanPdu.sdu = PduInfoPtr->SduDataPtr;  // Dữ liệu PDU
    CanPdu.id = CanID; //
		
		TrackedSdu = *(PduInfoPtr->SduDataPtr);
	
		
    // Gọi Can_Write để thực sự truyền thông điệp CAN
    if (Can_Write(Hth, &CanPdu) != E_OK) {
        Det_ReportError(1, 0, 2, CANIF_E_SEND_FAILED);  // Báo lỗi nếu truyền không thành công
        return E_NOT_OK;
    }

    // Trả về thành công nếu truyền đi thành công
    return E_OK;
}
/******************************************************************************
 * Name       : CanIf_DeInit
 * Param      : None
 * Return     : None
 * Contents   : Giải phóng tài nguyên của CanIf
 * Author     : 
 * Note       : Hàm này được gọi để tắt và giải phóng tài nguyên của CanIf khi không sử dụng nữa
 ******************************************************************************/
FUNC(void, CANIF_CODE)
CanIf_DeInit(void) {
    // Kiểm tra xem CanIf đã được khởi tạo chưa
    if (CanIf_State == 0) {
        Det_ReportError(1, 0, 2, CANIF_E_NOT_INITIALIZED);  // Báo lỗi nếu chưa khởi tạo
        return;
    }

    // Thực hiện giải phóng tài nguyên (nếu cần thiết)
    CanIf_State = 0;  // Đánh dấu CanIf đã được giải phóng
    // printf("CanIf: Đã giải phóng tài nguyên và dừng CAN Interface\n");
}