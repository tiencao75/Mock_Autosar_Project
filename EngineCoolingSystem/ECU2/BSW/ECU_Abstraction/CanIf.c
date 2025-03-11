#include "CanIf.h"

#define CANIF_START_SEC_VAR_CLEARED
#include "MemMap.h"  /* AUTOSAR memory mapping */
STATIC VAR(CanIf_StateType, CANIF_VAR) CanIf_State = CANIF_UNINIT;
STATIC VAR(CanIf_ConfigType, CANIF_VAR) CanIf_Config;
#define CANIF_STOP_SEC_VAR_CLEARED
#include "MemMap.h"

#define CANIF_START_SEC_CODE
#include "MemMap.h"

/*************************************************************************************
 * @brief Initializes the CAN Interface for ECU2 with the provided configuration.
 * @param ConfigPtr Pointer to the CAN Interface configuration structure.
 * @return None
 * @pre None
 * @post CAN Interface is initialized or an error is reported if ConfigPtr is invalid.
 * @implements CanIf_Init
 *************************************************************************************/
FUNC(void, CANIF_CODE) CanIf_Init(P2CONST(CanIf_ConfigType, AUTOMATIC, CANIF_CONFIG_DATA) ConfigPtr) {
    if (ConfigPtr == NULL_PTR) {
        Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, 0, CANIF_E_PARAM_POINTER);
        return;
    }
    CanIf_Config = *ConfigPtr;
    CanIf_State = CANIF_READY;
    /* printf("CANIF for ECU2: Initialized with Channel ID %u and Max PDU Count %u.\n", 
           CanIf_Config.CanIfChannelId, CanIf_Config.MaxPduCount); */
}

/*************************************************************************************
 * @brief Receives a PDU from the CAN bus for ECU2.
 * @param RxPduId ID of the PDU to receive.
 * @param PduInfoPtr Pointer to the PDU information structure to store received data.
 * @return E_OK if the receive operation is successful, E_NOT_OK otherwise.
 * @pre CAN Interface must be initialized and PduInfoPtr must be valid.
 * @post PDU data is stored in PduInfoPtr or an error is reported if invalid.
 * @implements CanIf_Receive
 *************************************************************************************/
FUNC(Std_ReturnType, CANIF_CODE) CanIf_Receive(PduIdType RxPduId, P2VAR(PduInfoType, AUTOMATIC, CANIF_APPL_DATA) PduInfoPtr) {
    // if (CanIf_State != CANIF_READY) {
    //     Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, 1, CANIF_E_NOT_INITIALIZED);
    //     return E_NOT_OK;
    // }
    // if (PduInfoPtr == NULL_PTR) {
    //     Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, 1, CANIF_E_PARAM_POINTER);
    //     return E_NOT_OK;
    // }

    Can_HwHandleType Hth = 0;  /* Example hardware handle */
    Can_PduType CanPdu;

    /* Call Can_Read to retrieve data from CAN Driver */
    if (Can_Read(Hth, &CanPdu) != E_OK) {
        Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, 2, CANIF_E_RECEIVE_FAILED);
        return E_NOT_OK;
    }

    /* Copy data from CanPdu to PduInfoPtr */
    PduInfoPtr->SduLength = CanPdu.length;  /* 5 bytes: 2 for fanSpeed, 2 for pumpSpeed, 1 for warningStatus */
    PduInfoPtr->SduDataPtr = CanPdu.sdu;    /* Pointer to data: [fanSpeedHigh, fanSpeedLow, pumpSpeedHigh, pumpSpeedLow, warningStatus] */

    /* printf("CANIF for ECU2: Received PDU with ID %u and Length %u\n", 
           RxPduId, PduInfoPtr->SduLength); */

    return E_OK;
}

/*************************************************************************************
 * @brief De-initializes the CAN Interface for ECU2 and releases resources.
 * @param None
 * @return None
 * @pre CAN Interface must be initialized.
 * @post CAN Interface is de-initialized or an error is reported if not initialized.
 * @implements CanIf_DeInit
 *************************************************************************************/
FUNC(void, CANIF_CODE) CanIf_DeInit(void) {
    if (CanIf_State != CANIF_READY) {
        Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, 2, CANIF_E_NOT_INITIALIZED);
        return;
    }
    CanIf_State = CANIF_UNINIT;
    /* printf("CANIF for ECU2: De-Initialized.\n"); */
}

/*************************************************************************************
 * @brief Transmits a PDU to the CAN bus for ECU2 (optional, if needed).
 * @param TxPduId ID of the PDU to transmit.
 * @param PduInfoPtr Pointer to the PDU information structure containing data to send.
 * @return E_OK if the transmit operation is successful, E_NOT_OK otherwise.
 * @pre CAN Interface must be initialized and PduInfoPtr must be valid.
 * @post PDU data is sent or an error is reported if invalid.
 * @implements CanIf_Transmit
 *************************************************************************************/
FUNC(Std_ReturnType, CANIF_CODE) CanIf_Transmit(PduIdType TxPduId, P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_DATA) PduInfoPtr) {
    if (CanIf_State != CANIF_READY) {
        Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, 1, CANIF_E_NOT_INITIALIZED);
        return E_NOT_OK;
    }
    if (PduInfoPtr == NULL_PTR) {
        Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, 1, CANIF_E_PARAM_POINTER);
        return E_NOT_OK;
    }

    Can_HwHandleType Hth = 0;
    Can_PduType CanPdu;
    CanPdu.id = 0x124;
    CanPdu.length = PduInfoPtr->SduLength;
    CanPdu.sdu = PduInfoPtr->SduDataPtr;
    CanPdu.swPduHandle = TxPduId;

    if (Can_Write(Hth, &CanPdu) != E_OK) {
        Det_ReportError(CANIF_MODULE_ID, CANIF_INSTANCE_ID, 2, CANIF_E_RECEIVE_FAILED);
        return E_NOT_OK;
    }

    /* printf("CANIF for ECU2: Transmitted PDU with ID %u and Length %u\n", 
           TxPduId, PduInfoPtr->SduLength); */
    return E_OK;
}

#define CANIF_STOP_SEC_CODE
#include "MemMap.h"