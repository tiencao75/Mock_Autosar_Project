#include "Com.h"
#include "Rte_EngineTemperatureActuator.h"  /* Giữ để dùng Com_SignalType */

#define COM_START_SEC_VAR_CLEARED
#include "MemMap.h"  /* AUTOSAR memory mapping */
STATIC VAR(boolean, COM_VAR) is_initialized = FALSE;  /* Initialization status for ECU2 */
#define COM_STOP_SEC_VAR_CLEARED
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"

/*************************************************************************************
 * @brief Initializes the COM Module for ECU2 with the provided configuration.
 * @param ConfigPtr Pointer to the COM configuration structure.
 * @return None
 * @pre None
 * @post COM Module is initialized or an error is reported if ConfigPtr is invalid.
 * @implements Com_Init
 *************************************************************************************/
FUNC(void, COM_CODE) Com_Init(P2CONST(Com_ConfigType, AUTOMATIC, COM_CONFIG_DATA) ConfigPtr) {
    if (ConfigPtr == NULL_PTR) {
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, 0, COM_E_PARAM_POINTER);
        return;
    }
    if (ConfigPtr->isEnabled) {
        is_initialized = TRUE;
        /* printf("COM for ECU2: Initialized with Channel %u and Signal ID %u.\n", 
               ConfigPtr->comChannel, ConfigPtr->signalId); */
    } else {
        is_initialized = FALSE;
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, 0, COM_E_PARAM_CONFIG);
    }
}

/*************************************************************************************
 * @brief Receives a signal from the lower layer (e.g., PDU Router) for ECU2.
 * @param SignalId ID of the signal to receive.
 * @param SignalDataPtr Pointer to where the received signal data will be stored.
 * @return COM_OK if the signal is received successfully, COM_NOT_OK otherwise.
 * @pre COM Module must be initialized and SignalDataPtr must be valid.
 * @post Signal data is stored in SignalDataPtr.
 * @implements Com_ReceiveSignal
 *************************************************************************************/
FUNC(Std_ReturnType, COM_CODE) Com_ReceiveSignal(Com_SignalIdType SignalId, P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr) {
    // if (!is_initialized) {
    //     Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, 2, COM_E_NOT_INITIALIZED);
    //     return COM_NOT_OK;
    // }
    if (SignalDataPtr == NULL_PTR) {
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, 2, COM_E_PARAM_POINTER);
        return COM_NOT_OK;
    }

    /* Receive PDU from PduR */
    PduInfoType PduInfo;
    if (PduR_UserLoTpRxIndication(SignalId, &PduInfo) != E_OK) {
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, 2, COM_E_PARAM_CONFIG);
        return COM_NOT_OK;
    }

    /* Check PDU length (expecting 5 bytes) */
    if (PduInfo.SduLength != 5) {
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, 2, COM_E_PARAM_CONFIG);
        return COM_NOT_OK;
    }

    /* Decode data from SduDataPtr */
    uint16 fanSpeed = (PduInfo.SduDataPtr[0] << 8) | PduInfo.SduDataPtr[1];    /* 2 bytes */
    uint16 pumpSpeed = (PduInfo.SduDataPtr[2] << 8) | PduInfo.SduDataPtr[3];  /* 2 bytes */
    uint8 warningStatus = PduInfo.SduDataPtr[4];                              /* 1 byte */

    /* Store decoded data in SignalDataPtr */
    ((Com_SignalType*)SignalDataPtr)->signalId = SignalId;
    ((Com_SignalType*)SignalDataPtr)->fanSpeed = fanSpeed;      /* Thêm fanSpeed vào cấu trúc */
    ((Com_SignalType*)SignalDataPtr)->pumpSpeed = pumpSpeed;    /* Thêm pumpSpeed vào cấu trúc */
    ((Com_SignalType*)SignalDataPtr)->warningStatus = warningStatus; /* Thêm warningStatus vào cấu trúc */
    ((Com_SignalType*)SignalDataPtr)->signalValue = 0;  /* Không dùng, để lại cho tương thích */

    /* printf("COM for ECU2: Received Signal - FanSpeed=%u%%, PumpSpeed=%u%%, WarningStatus=%u\n", 
           fanSpeed, pumpSpeed, warningStatus); */

    return COM_OK;
}

/*************************************************************************************
 * @brief Sends a signal to the lower layer (e.g., PDU Router) for ECU2 (optional, if needed).
 * @param SignalId ID of the signal to send.
 * @param SignalDataPtr Pointer to the signal data to send.
 * @return COM_OK if the signal is sent successfully, COM_NOT_OK otherwise.
 * @pre COM Module must be initialized and SignalDataPtr must be valid.
 * @post Signal data is sent or an error is reported if invalid.
 * @implements Com_SendSignal
 *************************************************************************************/
FUNC(Std_ReturnType, COM_CODE) Com_SendSignal(Com_SignalIdType SignalId, P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr) {
    if (!is_initialized) {
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, 1, COM_E_NOT_INITIALIZED);
        return COM_NOT_OK;
    }
    if (SignalDataPtr == NULL_PTR) {
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, 1, COM_E_PARAM_POINTER);
        return COM_NOT_OK;
    }

    PduInfoType PduInfo;
    PduInfo.SduLength = 5;  /* Assuming 5 bytes for consistency */
    PduInfo.SduDataPtr = (uint8*)SignalDataPtr;  /* Simplified for simulation */

    if (PduR_UserUpTransmit(SignalId, &PduInfo) != E_OK) {
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, 3, COM_E_PARAM_CONFIG);
        return COM_NOT_OK;
    }

    /* printf("COM for ECU2: Sent Signal - ID = 0x%X, Value = %u\n", 
           ((Com_SignalType*)SignalDataPtr)->signalId, ((Com_SignalType*)SignalDataPtr)->signalValue); */
    return COM_OK;
}

/*************************************************************************************
 * @brief Triggers the sending of an I-PDU through the COM Module and PDU Router for ECU2 (optional, if needed).
 * @param PduId ID of the I-PDU to trigger sending.
 * @return COM_OK if the I-PDU is triggered successfully, COM_NOT_OK otherwise.
 * @pre COM Module must be initialized.
 * @post I-PDU is sent or an error is reported if invalid.
 * @implements Com_TriggerIPDUSend
 *************************************************************************************/
FUNC(Std_ReturnType, COM_CODE) Com_TriggerIPDUSend(PduIdType PduId) {
    if (!is_initialized) {
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, 3, COM_E_NOT_INITIALIZED);
        return COM_NOT_OK;
    }

    PduInfoType PduInfo;
    PduInfo.SduLength = 5;
    uint8 dummyData[5] = {0};  /* Dummy data for simulation */
    PduInfo.SduDataPtr = dummyData;

    if (PduR_UserUpTransmit(PduId, &PduInfo) != E_OK) {
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, 3, COM_E_PARAM_CONFIG);
        return COM_NOT_OK;
    }

    /* printf("COM for ECU2: Triggered I-PDU Send for PduId 0x%X.\n", PduId); */
    return COM_OK;
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"