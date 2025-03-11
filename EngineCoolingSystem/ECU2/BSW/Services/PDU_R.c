#include "PDU_R.h"
#include "CanIf.h"

#define PDUR_START_SEC_VAR_CLEARED
#include "MemMap.h"  /* AUTOSAR memory mapping */
STATIC VAR(PduR_StateType, PDUR_VAR) PduR_State = PDUR_UNINIT;
STATIC VAR(PduR_PBConfigType, PDUR_VAR) PduR_Config;
#define PDUR_STOP_SEC_VAR_CLEARED
#include "MemMap.h"

#define PDUR_START_SEC_CODE
#include "MemMap.h"

/*************************************************************************************
 * @brief Initializes the PDU Router for ECU2 with the provided configuration.
 * @param ConfigPtr Pointer to the PDU Router PB configuration structure.
 * @return None
 * @pre None
 * @post PDU Router is initialized or an error is reported if ConfigPtr is invalid.
 * @implements PduR_Init
 *************************************************************************************/
FUNC(void, PDUR_CODE) PduR_Init(P2CONST(PduR_PBConfigType, AUTOMATIC, PDUR_CONFIG_DATA) ConfigPtr) {
    if (ConfigPtr == NULL_PTR) {
        Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, 0, PDUR_E_PARAM_POINTER);
        return;
    }
    PduR_Config = *ConfigPtr;
    PduR_State = PDUR_INIT;
    /* printf("PDUR for ECU2: Initialized with %u instances.\n", 
           PduR_Config.MaxPduRouterInstances); */
}

/*************************************************************************************
 * @brief Retrieves version information of the PDU Router for ECU2.
 * @param versioninfo Pointer to the structure where version information will be stored.
 * @return None
 * @pre None
 * @post Version information is stored in versioninfo or an error is reported if versioninfo is invalid.
 * @implements PduR_GetVersionInfo
 *************************************************************************************/
FUNC(void, PDUR_CODE) PduR_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, PDUR_APPL_DATA) versioninfo) {
    if (versioninfo == NULL_PTR) {
        Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, 1, PDUR_E_PARAM_POINTER);
        return;
    }
    versioninfo->vendorID = 1;
    versioninfo->moduleID = PDUR_MODULE_ID;
    versioninfo->sw_major_version = 4;
    versioninfo->sw_minor_version = 3;
    versioninfo->sw_patch_version = 0;
}

/*************************************************************************************
 * @brief Receives a PDU from the lower layer (e.g., CAN Interface) for ECU2.
 * @param RxPduId ID of the PDU to receive.
 * @param PduInfoPtr Pointer to the PDU information structure to store received data.
 * @return E_OK if the receive operation is successful, E_NOT_OK otherwise.
 * @pre PDU Router must be initialized and PduInfoPtr must be valid.
 * @post PDU data is stored in PduInfoPtr or an error is reported if invalid.
 * @implements PduR_UserLoTpRxIndication
 *************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_UserLoTpRxIndication(PduIdType RxPduId, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr) {
    // if (PduR_State != PDUR_INIT) {
    //     Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, 2, PDUR_E_NOT_INITIALIZED);
    //     return E_NOT_OK;
    // }
    if (PduInfoPtr == NULL_PTR) {
        Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, 2, PDUR_E_PARAM_POINTER);
        return E_NOT_OK;
    }

    /* printf("PDUR for ECU2: Receiving PDU with ID %u.\n", RxPduId); */

    /* Call CanIf_Receive to retrieve data from CAN Interface */
    if (CanIf_Receive(RxPduId, PduInfoPtr) != E_OK) {
        Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, 2, PDUR_E_RECEIVE_FAILED);
        return E_NOT_OK;
    }

    /* Data received: 5 bytes (2 for fanSpeed, 2 for pumpSpeed, 1 for warningStatus) */
    /* printf("PDUR for ECU2: Received PDU with ID %u and Length %u successfully.\n", 
           RxPduId, PduInfoPtr->SduLength); */

    return E_OK;
}

/*************************************************************************************
 * @brief Confirms transmission of a PDU from the lower layer for ECU2 (optional, if needed).
 * @param TxPduId ID of the PDU that was transmitted.
 * @param result Result of the transmission (E_OK or E_NOT_OK).
 * @return None
 * @pre PDU Router must be initialized.
 * @post Transmission confirmation is processed or an error is reported if not initialized.
 * @implements PduR_UserLoTpTxConfirmation
 *************************************************************************************/
FUNC(void, PDUR_CODE) PduR_UserLoTpTxConfirmation(PduIdType TxPduId, Std_ReturnType result) {
    if (PduR_State != PDUR_INIT) {
        Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, 3, PDUR_E_NOT_INITIALIZED);
        return;
    }
    /* printf("PDUR for ECU2: Transmission Confirmation for PDU ID %u, Result: %d\n", 
           TxPduId, result); */
}

/*************************************************************************************
 * @brief Transmits a PDU to the upper layer (e.g., COM) for ECU2 (optional, if needed).
 * @param TxPduId ID of the PDU to transmit.
 * @param PduInfoPtr Pointer to the PDU information structure containing data to send.
 * @return E_OK if the transmit operation is successful, E_NOT_OK otherwise.
 * @pre PDU Router must be initialized and PduInfoPtr must be valid.
 * @post PDU data is sent or an error is reported if invalid.
 * @implements PduR_UserUpTransmit
 *************************************************************************************/
FUNC(Std_ReturnType, PDUR_CODE) PduR_UserUpTransmit(PduIdType TxPduId, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr) {
    if (PduR_State != PDUR_INIT) {
        Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, 2, PDUR_E_NOT_INITIALIZED);
        return E_NOT_OK;
    }
    if (PduInfoPtr == NULL_PTR) {
        Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, 2, PDUR_E_PARAM_POINTER);
        return E_NOT_OK;
    }

    /* printf("PDUR for ECU2: Transmitting PDU with ID %u and Length %u.\n", 
           TxPduId, PduInfoPtr->SduLength); */

    if (CanIf_Transmit(TxPduId, PduInfoPtr) != E_OK) {
        Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID, 2, PDUR_E_TRANSMIT_FAILED);
        return E_NOT_OK;
    }

    return E_OK;
}

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"