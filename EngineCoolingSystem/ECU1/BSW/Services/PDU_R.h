#ifndef PDU_R_H
#define PDU_R_H

#include "Std_Types.h"
#include "Det.h"
#include "Compiler.h"  // Bao gồm Compiler.h để sử dụng các macro AUTOSAR

/* Định nghĩa các kiểu dữ liệu theo chuẩn AUTOSAR 8.2 */
typedef uint16 PduIdType;
typedef uint16 PduR_PBConfigIdType;  // Định nghĩa kiểu ID cho cấu hình PDU Router
typedef uint16 PduR_RoutingPathGroupIdType;
typedef uint16 PduLengthType;

/* Cấu trúc PDU Info - Chứa dữ liệu và độ dài của PDU */
typedef struct {
    uint8* SduDataPtr;        // Con trỏ đến dữ liệu PDU
    PduLengthType SduLength;  // Độ dài dữ liệu PDU
} PduInfoType;

/* Trạng thái của PDU Router */
typedef enum {
    PDUR_UNINIT,  // Chưa được khởi tạo
    PDUR_INIT     // Đã được khởi tạo
} PduR_StateType;

/* Cấu hình PDU Router */
typedef struct {
    uint8 MaxPduRouterInstances;  // Số lượng tối đa các instance của PDU Router
} PduR_ConfigType;

/* Cấu trúc PDU Router PBConfig - Cấu hình thời gian xây dựng của PDU Router */
typedef struct {
    uint16 MaxPduRouterInstances;  /* Số lượng tối đa các instance của PDU Router */
    /* Thêm các trường dữ liệu cấu hình khác nếu cần thiết */
} PduR_PBConfigType;

/* API theo mục 8.3 */

/* Khởi tạo PDU Router */
FUNC(void, PDUR_CODE) PduR_Init(P2CONST(PduR_PBConfigType, AUTOMATIC, RTE_APPL_DATA) ConfigPtr);

/* Lấy thông tin phiên bản */
FUNC(void, PDUR_CODE) PduR_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, RTE_APPL_DATA) versioninfo);

/* Lấy ID cấu hình của PDU Router */
FUNC(PduIdType, PDUR_CODE) PduR_GetConfigurationId(void);

/* Kích hoạt định tuyến của PDU Router */
FUNC(void, PDUR_CODE) PduR_EnableRouting(PduR_RoutingPathGroupIdType id);

/* Vô hiệu hóa định tuyến của PDU Router */
FUNC(void, PDUR_CODE) PduR_DisableRouting(PduR_RoutingPathGroupIdType id, boolean initialize);

/* Truyền PDU từ ứng dụng lên PDU Router */
FUNC(Std_ReturnType, PDUR_CODE) PduR_UserUpTransmit(PduIdType TxPduId, P2CONST(PduInfoType, AUTOMATIC, RTE_APPL_DATA) PduInfoPtr);

/* Xác nhận truyền PDU từ PDU Router */
FUNC(void, PDUR_CODE) PduR_UserLoTpTxConfirmation(PduIdType id, Std_ReturnType result);

/* Thông báo nhận PDU từ PDU Router */
FUNC(void, PDUR_CODE) PduR_UserLoTpRxIndication(PduIdType id, Std_ReturnType result);

#endif /* PDU_R_H */
