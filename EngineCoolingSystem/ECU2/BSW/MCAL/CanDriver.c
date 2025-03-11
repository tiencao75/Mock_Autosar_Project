#include "CanDriver.h"
#include "Compiler.h"  // Thêm để dùng STATIC và các macro khác
#include <stdlib.h>

#define CAN_START_SEC_VAR_CLEARED
#include "MemMap.h"  /* AUTOSAR memory mapping */
STATIC VAR(CanIf_StateType, CAN_VAR) Can_State = CANIF_UNINIT;  // Sửa Can_StateType thành CanIf_StateType
#define CAN_STOP_SEC_VAR_CLEARED
#include "MemMap.h"

#define CAN_START_SEC_CODE
#include "MemMap.h"

volatile uint16 dataFan;
volatile uint16 dataPump;
volatile uint8 dataLight;

/*************************************************************************************
 * @brief Initializes the CAN Driver for ECU2 with the provided configuration.
 * @param ConfigPtr Pointer to the CAN configuration structure.
 * @return None
 * @pre None
 * @post CAN Driver is initialized or an error is reported if ConfigPtr is invalid.
 * @implements Can_Init
 *************************************************************************************/
FUNC(void, CAN_CODE) Can_Init(P2CONST(Can_ConfigType, AUTOMATIC, CAN_CONFIG_DATA) ConfigPtr) {
    if (ConfigPtr == NULL_PTR) {
        Det_ReportError(CAN_DRIVER_MODULE_ID, CAN_DRIVER_INSTANCE_ID, 0, CAN_E_PARAM_POINTER);
        return;
    }
    Can_State = CANIF_READY;  // Sửa CAN_READY thành CANIF_READY
    /* printf("CAN for ECU2 Initialized with Baudrate %lu and Controller ID %u.\n", 
           ConfigPtr->CanControllerBaudrate, ConfigPtr->CanControllerId); */
}

/*************************************************************************************
 * @brief Reads a PDU from the CAN bus for ECU2.
 * @param Hth CAN Hardware Handle.
 * @param PduInfoPtr Pointer to the PDU information structure to store received data.
 * @return E_OK if the read operation is successful, E_NOT_OK otherwise.
 * @pre CAN Driver must be initialized and PduInfoPtr must be valid.
 * @post PDU data is stored in PduInfoPtr or an error is reported if invalid.
 * @implements Can_Read
 *************************************************************************************/
FUNC(Std_ReturnType, CAN_CODE) Can_Read(Can_HwHandleType Hth, P2VAR(Can_PduType, AUTOMATIC, CAN_APPL_DATA) PduInfoPtr) {
    // if (PduInfoPtr == NULL_PTR) {
    //     Det_ReportError(CAN_DRIVER_MODULE_ID, CAN_DRIVER_INSTANCE_ID, 2, CAN_E_PARAM_POINTER);
    //     return E_NOT_OK;
    // }
    // if (Can_State != CANIF_READY) {
    //     Det_ReportError(CAN_DRIVER_MODULE_ID, CAN_DRIVER_INSTANCE_ID, 2, CAN_E_NOT_INITIALIZED);
    //     return E_NOT_OK;
    // }

    /* Simulate receiving 3 separate signals from ECU1 */
    PduInfoPtr->id = 0x123;  /* CAN ID từ ECU1 */
    PduInfoPtr->length = 5;  /* 5 bytes: 2 cho fanSpeed, 2 cho pumpSpeed, 1 cho warningStatus */
    static uint8 sdu_data[5];  // Mảng tĩnh để lưu dữ liệu
    PduInfoPtr->sdu = sdu_data;

    /* Tạo dữ liệu ngẫu nhiên */
    uint16 fanSpeed = (uint16)(rand() % 101);    /* Random từ 0-100% */
    uint16 pumpSpeed = (uint16)(rand() % 101);   /* Random từ 0-100% */
    uint8 warningStatus = (uint8)(rand() % 2);   /* Random từ 0-1 (OFF/ON) */

    dataFan = fanSpeed;
    dataPump = pumpSpeed;
    dataLight = warningStatus;

    /* Đóng gói dữ liệu vào sdu (big-endian format) */
    PduInfoPtr->sdu[0] = (uint8)(fanSpeed >> 8);   /* High byte của fanSpeed */
    PduInfoPtr->sdu[1] = (uint8)(fanSpeed & 0xFF);  /* Low byte của fanSpeed */
    PduInfoPtr->sdu[2] = (uint8)(pumpSpeed >> 8);   /* High byte của pumpSpeed */
    PduInfoPtr->sdu[3] = (uint8)(pumpSpeed & 0xFF);  /* Low byte của pumpSpeed */
    PduInfoPtr->sdu[4] = warningStatus;             /* warningStatus */

    /* Debug output */
    /* printf("CAN for ECU2: Read PDU with HW Handle %u, ID = 0x%X, Length = %u\n", 
           Hth, PduInfoPtr->id, PduInfoPtr->length); 
    printf("Data: FanSpeed=%u%%, PumpSpeed=%u%%, WarningStatus=%u\n", 
           fanSpeed, pumpSpeed, warningStatus); */

    return E_OK;
}

/*************************************************************************************
 * @brief De-initializes the CAN Driver for ECU2 and releases resources.
 * @param None
 * @return None
 * @pre CAN Driver must be initialized.
 * @post CAN Driver is de-initialized or an error is reported if not initialized.
 * @implements Can_DeInit
 *************************************************************************************/
FUNC(void, CAN_CODE) Can_DeInit(void) {
    if (Can_State != CANIF_READY) {  // Sửa CAN_READY thành CANIF_READY
        Det_ReportError(CAN_DRIVER_MODULE_ID, CAN_DRIVER_INSTANCE_ID, 0, CAN_E_NOT_INITIALIZED);
        return;
    }
    Can_State = CANIF_UNINIT;  // Sửa CAN_UNINIT thành CANIF_UNINIT
    /* printf("CAN for ECU2 De-Initialized.\n"); */
}

/*************************************************************************************
 * @brief Writes a PDU to the CAN bus for ECU2 (optional, if needed).
 * @param Hth CAN Hardware Handle.
 * @param PduInfoPtr Pointer to the PDU information structure containing data to send.
 * @return E_OK if the write operation is successful, E_NOT_OK otherwise.
 * @pre CAN Driver must be initialized and PduInfoPtr must be valid.
 * @post PDU data is sent or an error is reported if invalid.
 * @implements Can_Write
 *************************************************************************************/
FUNC(Std_ReturnType, CAN_CODE) Can_Write(Can_HwHandleType Hth, P2CONST(Can_PduType, AUTOMATIC, CAN_APPL_DATA) PduInfoPtr) {
    if (PduInfoPtr == NULL_PTR) {
        Det_ReportError(CAN_DRIVER_MODULE_ID, CAN_DRIVER_INSTANCE_ID, 2, CAN_E_PARAM_POINTER);
        return E_NOT_OK;
    }
    if (Can_State != CANIF_READY) {  // Sửa CAN_READY thành CANIF_READY
        Det_ReportError(CAN_DRIVER_MODULE_ID, CAN_DRIVER_INSTANCE_ID, 2, CAN_E_NOT_INITIALIZED);
        return E_NOT_OK;
    }
    /* printf("CAN for ECU2: Writing PDU with HW Handle %u, ID = 0x%X, Length = %u\n", 
           Hth, PduInfoPtr->id, PduInfoPtr->length); */
    return E_OK;
}

#define CAN_STOP_SEC_CODE
#include "MemMap.h"