#ifndef PDU_R_H
#define PDU_R_H

#include "Std_Types.h"        // AUTOSAR standard types
#include "Det.h"              // Development Error Tracer
// #include "CanIf.h"            // CAN Interface for ECU2
#include "Compiler.h"         // AUTOSAR compiler abstraction

/* AUTOSAR Module ID for PDU Router (ECU2-specific) */
#define PDUR_MODULE_ID            62U
#define PDUR_INSTANCE_ID          0U

/* AUTOSAR Error Codes for PDU Router */
#define PDUR_E_PARAM_POINTER      0x01U  /* Invalid pointer */
#define PDUR_E_PARAM_CONFIG       0x02U  /* Invalid configuration */
#define PDUR_E_NOT_INITIALIZED    0x03U  /* Module not initialized */
#define PDUR_E_TRANSMIT_FAILED    0x04U  /* Transmit operation failed */
#define PDUR_E_RECEIVE_FAILED     0x05U  /* Receive operation failed */

/* AUTOSAR PDU Router Types */
// typedef uint16 PduIdType;                     /* PDU Identifier Type */
typedef uint16 PduR_PBConfigIdType;           /* PDU Router PB Configuration ID Type */
typedef uint16 PduR_RoutingPathGroupIdType;   /* PDU Router Routing Path Group ID Type */
typedef uint16 PduLengthType;                 /* PDU Length Type */

/* AUTOSAR PDU Info Type */
typedef struct {
    uint8* SduDataPtr;        /* Pointer to PDU data */
    PduLengthType SduLength;  /* Length of PDU data */
} PduInfoType;

/* AUTOSAR PDU Router State Type for ECU2 */
typedef enum {
    PDUR_UNINIT = 0,  /* PDU Router is not initialized */
    PDUR_INIT         /* PDU Router is initialized and ready */
} PduR_StateType;

/* AUTOSAR PDU Router Configuration Type for ECU2 */
typedef struct {
    uint8 MaxPduRouterInstances;  /* Maximum number of PDU Router instances */
    const void* PduRConfig;       /* Hardware-specific configuration */
} PduR_ConfigType;

/* AUTOSAR PDU Router PBConfig Type for ECU2 */
typedef struct {
    uint16 MaxPduRouterInstances; /* Maximum number of PDU Router instances */
    /* Additional configuration fields can be added if needed */
} PduR_PBConfigType;

/* AUTOSAR PDU Router API Prototypes for ECU2 */

/**
 * @brief Initializes the PDU Router for ECU2 with the provided configuration.
 * @param ConfigPtr Pointer to the PDU Router PB configuration structure.
 * @return None
 * @pre None
 * @post PDU Router is initialized or an error is reported if ConfigPtr is invalid.
 */
FUNC(void, PDUR_CODE) PduR_Init(P2CONST(PduR_PBConfigType, AUTOMATIC, PDUR_CONFIG_DATA) ConfigPtr);

/**
 * @brief Retrieves version information of the PDU Router for ECU2.
 * @param versioninfo Pointer to the structure where version information will be stored.
 * @return None
 * @pre None
 * @post Version information is stored in versioninfo or an error is reported if versioninfo is invalid.
 */
FUNC(void, PDUR_CODE) PduR_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, PDUR_APPL_DATA) versioninfo);

/**
 * @brief Receives a PDU from the lower layer (e.g., CAN Interface) for ECU2.
 * @param RxPduId ID of the PDU to receive.
 * @param PduInfoPtr Pointer to the PDU information structure to store received data.
 * @return E_OK if the receive operation is successful, E_NOT_OK otherwise.
 * @pre PDU Router must be initialized and PduInfoPtr must be valid.
 * @post PDU data is stored in PduInfoPtr or an error is reported if invalid.
 */
FUNC(Std_ReturnType, PDUR_CODE) PduR_UserLoTpRxIndication(PduIdType RxPduId, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr);

/**
 * @brief Confirms transmission of a PDU from the lower layer for ECU2 (optional, if needed).
 * @param TxPduId ID of the PDU that was transmitted.
 * @param result Result of the transmission (E_OK or E_NOT_OK).
 * @return None
 * @pre PDU Router must be initialized.
 * @post Transmission confirmation is processed or an error is reported if not initialized.
 */
FUNC(void, PDUR_CODE) PduR_UserLoTpTxConfirmation(PduIdType TxPduId, Std_ReturnType result);

/**
 * @brief Transmits a PDU to the upper layer (e.g., COM) for ECU2 (optional, if needed).
 * @param TxPduId ID of the PDU to transmit.
 * @param PduInfoPtr Pointer to the PDU information structure containing data to send.
 * @return E_OK if the transmit operation is successful, E_NOT_OK otherwise.
 * @pre PDU Router must be initialized and PduInfoPtr must be valid.
 * @post PDU data is sent or an error is reported if invalid.
 */
FUNC(Std_ReturnType, PDUR_CODE) PduR_UserUpTransmit(PduIdType TxPduId, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr);

#endif /* PDU_R_H */