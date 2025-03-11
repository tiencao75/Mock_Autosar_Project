#ifndef CANIF_H
#define CANIF_H

#include "Std_Types.h"        // AUTOSAR standard types
#include "Det.h"              // Development Error Tracer
#include "CanDriver.h"        // CAN Driver for ECU2
#include "PDU_R.h"             // PDU Router
#include "Compiler.h"         // AUTOSAR compiler abstraction

/* AUTOSAR Module ID for CAN Interface (ECU2-specific) */
#define CANIF_MODULE_ID            61U
#define CANIF_INSTANCE_ID          0U

/* AUTOSAR Error Codes for CAN Interface */
#define CANIF_E_PARAM_POINTER      0x01U  /* Invalid pointer */
#define CANIF_E_PARAM_CONFIG       0x02U  /* Invalid configuration */
#define CANIF_E_NOT_INITIALIZED    0x03U  /* Module not initialized */
#define CANIF_E_RECEIVE_FAILED     0x04U  /* Receive operation failed */

/* AUTOSAR CAN Interface Configuration Type for ECU2 */
// typedef struct {
//     uint8 CanIfChannelId;       /* CAN Channel ID */
//     uint16 MaxPduCount;         /* Maximum number of PDUs that can be handled */
//     const void* CanIfConfig;    /* Hardware-specific configuration */
// } CanIf_ConfigType;

// /* AUTOSAR CAN Interface State Type for ECU2 */
// typedef enum {
//     CANIF_UNINIT = 0,  /* CAN Interface is not initialized */
//     CANIF_READY        /* CAN Interface is initialized and ready */
// } CanIf_StateType;

/* AUTOSAR CAN Interface API Prototypes for ECU2 */

/**
 * @brief Initializes the CAN Interface for ECU2 with the provided configuration.
 * @param ConfigPtr Pointer to the CAN Interface configuration structure.
 * @return None
 * @pre None
 * @post CAN Interface is initialized or an error is reported if ConfigPtr is invalid.
 */
FUNC(void, CANIF_CODE) CanIf_Init(P2CONST(CanIf_ConfigType, AUTOMATIC, CANIF_CONFIG_DATA) ConfigPtr);

/**
 * @brief De-initializes the CAN Interface for ECU2 and releases resources.
 * @param None
 * @return None
 * @pre CAN Interface must be initialized.
 * @post CAN Interface is de-initialized or an error is reported if not initialized.
 */
FUNC(void, CANIF_CODE) CanIf_DeInit(void);

/**
 * @brief Receives a PDU from the CAN bus for ECU2.
 * @param RxPduId ID of the PDU to receive.
 * @param PduInfoPtr Pointer to the PDU information structure to store received data.
 * @return E_OK if the receive operation is successful, E_NOT_OK otherwise.
 * @pre CAN Interface must be initialized and PduInfoPtr must be valid.
 * @post PDU data is stored in PduInfoPtr or an error is reported if invalid.
 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_Receive(PduIdType RxPduId, P2VAR(PduInfoType, AUTOMATIC, CANIF_APPL_DATA) PduInfoPtr);

/**
 * @brief Transmits a PDU to the CAN bus for ECU2 (optional, if needed).
 * @param TxPduId ID of the PDU to transmit.
 * @param PduInfoPtr Pointer to the PDU information structure containing data to send.
 * @return E_OK if the transmit operation is successful, E_NOT_OK otherwise.
 * @pre CAN Interface must be initialized and PduInfoPtr must be valid.
 * @post PDU data is sent or an error is reported if invalid.
 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_Transmit(PduIdType TxPduId, P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_DATA) PduInfoPtr);

#endif /* CANIF_H */  