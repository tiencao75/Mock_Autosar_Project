#include "Can.h"  // Thư viện CAN chuẩn

STATIC VAR (Can_StateType,CANDRV_VAR) Can_State = CAN_STATE_UNINITIALIZED;  // Trạng thái của CAN

/*************************************************************************************
 * Name       : Can_Init
 * Param      : Config - Cấu hình cho CAN.
 * Return     : None
 * Contents   : Hàm này khởi tạo hệ thống CAN dựa trên cấu hình được cung cấp.
 * Author     : 
 * Note       : Hàm được gọi khi bắt đầu sử dụng CAN, để cấu hình các tham số như tốc độ, chế độ CAN.
 *************************************************************************************/

FUNC(void, CAN_DRIVER_CODE)  
Can_Init(P2CONST(Can_ConfigType, AUTOMATIC, RTE_APPL_DATA) Config) {
    // Kiểm tra xem cấu hình CAN có hợp lệ không
    if (Config == NULL_PTR) {
        Det_ReportError(1, 0, 0, CAN_E_PARAM_CONFIG);  // Báo lỗi nếu cấu hình NULL
        return;
    }

    // Thực hiện khởi tạo CAN dựa trên cấu hình từ Config
    // Giả sử CAN được cấu hình từ Config và khởi tạo phần cứng tại đây
    Can_State = CAN_STATE_INITIALIZED;  // Đánh dấu CAN đã được khởi tạo
    // printf("CAN Initialized.\n");  // In thông báo khi CAN đã được khởi tạo
}
/*************************************************************************************
 * Name       : Can_Write
 * Param      : Hth       - Handle truyền thông phần cứng.
 *              PduInfo   - Thông tin về PDU (Protocol Data Unit) cần truyền.
 * Return     : E_OK nếu việc truyền dữ liệu thành công, E_NOT_OK nếu có lỗi.
 * Contents   : Hàm này ghi dữ liệu vào hệ thống CAN, truyền PDU qua phần cứng CAN.
 * Author     : 
 * Note       : Hàm này truyền thông điệp CAN qua hệ thống phần cứng CAN.
 *************************************************************************************/

FUNC(Std_ReturnType, CAN_DRIVER_CODE) 
Can_Write(Can_HwHandleType Hth, P2CONST(Can_PduType, AUTOMATIC, RTE_APPL_DATA) PduInfo) {
    // Kiểm tra xem dữ liệu PDU có hợp lệ không
    if (PduInfo == NULL_PTR) {
        Det_ReportError(1, 0, 2, CAN_E_PARAM_POINTER);  // Báo lỗi nếu PduInfo là NULL
        return E_NOT_OK;
    }
    return E_OK;
}
/*************************************************************************************
 * Name       : Can_DeInit
 * Param      : None
 * Return     : None
 * Contents   : Hàm này dùng để hủy khởi tạo và giải phóng tài nguyên của CAN.
 * Author     : 
 * Note       : Hàm được gọi khi không còn sử dụng CAN nữa, để giải phóng tài nguyên.
 *************************************************************************************/

FUNC(void, CAN_DRIVER_CODE) 
Can_DeInit(void) {
    // Kiểm tra xem CAN đã được khởi tạo chưa
    if (Can_State != CAN_STATE_INITIALIZED) {
        Det_ReportError(1, 0, 0, CAN_E_NOT_INITIALIZED);  // Báo lỗi nếu CAN chưa được khởi tạo
        return;
    }

    // Thực hiện giải phóng tài nguyên CAN (nếu cần thiết)
    Can_State = CAN_STATE_UNINITIALIZED;  // Đánh dấu CAN đã được giải phóng
//     printf("CAN De-Initialized.\n");  // In thông báo khi CAN được giải phóng
}
