#include "PDU_R.h"
#include "Det.h"
#include <stdio.h>

/* Biến toàn cục quản lý trạng thái PDUR */
STATIC VAR(PduR_StateType,PDUR_VAR) PduR_State = PDUR_UNINIT;
STATIC VAR(PduR_PBConfigType,PDUR_VAR) PduR_Config;


/******************************************************************************
 * Name       : PduR_Init
 * Param      : ConfigPtr : Con trỏ đến cấu hình PDU Router
 * Return     : None
 * Contents   : Khởi tạo PDU Router với cấu hình được cung cấp
 * Author     : 
 * Note       : Hàm này kiểm tra tính hợp lệ của cấu hình và khởi tạo
 *              PDU Router. Nếu cấu hình không hợp lệ hoặc NULL, sẽ báo lỗi.
 ******************************************************************************/
FUNC(void, PDUR_CODE)
PduR_Init(P2CONST(PduR_PBConfigType, AUTOMATIC, RTE_APPL_DATA) ConfigPtr) {
    if (ConfigPtr == NULL_PTR) {
        Det_ReportError(1, 0, 0, PDUR_E_PARAM_POINTER);  // Báo lỗi nếu con trỏ cấu hình bị NULL
        return;
    }
    
    PduR_Config = *ConfigPtr;  // Gán cấu hình vào biến toàn cục PduR_Config
    PduR_State = PDUR_INIT;    // Đặt trạng thái của PDU Router là đã được khởi tạo
    
    // printf("PduR: Đã khởi tạo với %d instances\n", PduR_Config.MaxPduRouterInstances);
}


/******************************************************************************
 * Tên        : PduR_GetVersionInfo
 * Tham số    : versioninfo : Con trỏ đến cấu trúc thông tin phiên bản cần được điền dữ liệu
 * Trả về     : Không có giá trị trả về
 * Nội dung   : Lấy thông tin phiên bản của PDU Router
 * Tác giả    : 
 * Ghi chú    : Hàm này điền thông tin phiên bản vào cấu trúc thông tin phiên bản,
 *              bao gồm thông tin nhà cung cấp, mã module và chi tiết phiên bản.
 ******************************************************************************/
FUNC(void, PDUR_CODE)
PduR_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, RTE_APPL_DATA) versioninfo) {
    if (versioninfo == NULL_PTR) {
        Det_ReportError(1, 0, 1, PDUR_E_PARAM_POINTER);
        return;
    }

    versioninfo->vendorID = 1;
    versioninfo->moduleID = 2;
    versioninfo->sw_major_version = 1;
    versioninfo->sw_minor_version = 0;
    versioninfo->sw_patch_version = 0;
}

/*************************************************************************************
 * Tên Hàm    : PduR_UserUpTransmit
 * Tham Số    : TxPduId    - Mã nhận diện của PDU cần truyền
 *              PduInfoPtr - Con trỏ đến dữ liệu PDU và thông tin siêu dữ liệu của PDU
 * Trả Về     : Trạng Thái  - E_OK nếu yêu cầu truyền dữ liệu được chấp nhận, 
 *                            E_NOT_OK nếu yêu cầu truyền dữ liệu không được chấp nhận
 * Nội Dung    : Hàm này yêu cầu truyền PDU qua PDU Router
 * Tác Giả    : 
 * Ghi Chú    : Hàm này kiểm tra xem PDU Router đã được khởi tạo và 
 *              thông tin PDU cung cấp có hợp lệ không. Nếu hợp lệ, 
 *              nó sẽ yêu cầu truyền PDU qua PDU Router.
 *************************************************************************************/

FUNC(Std_ReturnType, PDUR_CODE)
PduR_UserUpTransmit(PduIdType TxPduId, P2CONST(PduInfoType, AUTOMATIC, RTE_APPL_DATA) PduInfoPtr) {
    // // Kiểm tra xem PDU Router đã được khởi tạo chưa
    // if (PduR_State != PDUR_INIT) {
    //     Det_ReportError(1, 0, 2, PDUR_E_NOT_INITIALIZED); // Báo lỗi nếu PDU Router chưa được khởi tạo
    //     return E_NOT_OK;
    // }

    // Kiểm tra con trỏ PDU có hợp lệ không
    if (PduInfoPtr == NULL_PTR) {
        Det_ReportError(1, 0, 2, PDUR_E_PARAM_POINTER); // Báo lỗi nếu con trỏ PDU là NULL
        return E_NOT_OK;
    }

    // Mô phỏng quá trình truyền PDU qua PDU Router
    // printf("PduR: Đang truyền PDU ID %d với độ dài %d\n", TxPduId, PduInfoPtr->SduLength);

    // Lấy thông tin PDU, ví dụ ID, độ dài và dữ liệu
    PduIdType pduId = TxPduId;  // ID của PDU
    uint8* pduData = PduInfoPtr->SduDataPtr;  // Dữ liệu của PDU
    uint8 pduLength = PduInfoPtr->SduLength;  // Độ dài của PDU

    // Tiến hành truyền PDU qua phần cứng CAN thông qua giao diện
    if (CanIf_Transmit(pduId, PduInfoPtr) == E_OK) {
        // printf("PduR: Truyền PDU thành công với ID %d và độ dài %d\n", pduId, pduLength);
        return E_OK;
    } else {
        Det_ReportError(1, 0, 2, PDUR_E_TRANSMIT_FAILED);  // Báo lỗi nếu không thể truyền được
        return E_NOT_OK;
    }
}


/******************************************************************************
 * Name       : PduR_UserLoTpTxConfirmation
 * Param      : id     : ID của PDU đã được truyền
 *              result : Kết quả của việc truyền PDU (E_OK hoặc E_NOT_OK)
 * Return     : None
 * Contents   : Cung cấp xác nhận sau khi truyền PDU
 * Author     : 
 * Note       : Hàm này được gọi để xác nhận kết quả của việc truyền PDU.
 ******************************************************************************/
FUNC(void, PDUR_CODE)
PduR_UserLoTpTxConfirmation(PduIdType id, Std_ReturnType result) {
    // printf("PduR: Xác nhận truyền PDU với ID %d, Kết quả: %d\n", id, result);
}

/******************************************************************************
 * Name       : PduR_UserLoTpRxIndication
 * Param      : id      : ID của PDU đã nhận
 *              result  : Kết quả nhận PDU (E_OK hoặc E_NOT_OK)
 * Return     : None
 * Contents   : Xử lý tín hiệu nhận được và thông báo kết quả
 * Author     : 
 * Note       : Hàm này được gọi khi PDU được nhận. Kết quả xác nhận việc nhận PDU.
 ******************************************************************************/
FUNC(void, PDUR_CODE)
PduR_UserLoTpRxIndication(PduIdType id, Std_ReturnType result) {
    if (result == E_OK) {
        // printf("PduR: Nhận PDU thành công với ID %d\n", id);
    } else {
        Det_ReportError(1, 0, 3, PDUR_E_PARAM_POINTER);  // Nếu kết quả không thành công, báo lỗi
        // printf("PduR: Nhận PDU thất bại với ID %d\n", id);
    }
}