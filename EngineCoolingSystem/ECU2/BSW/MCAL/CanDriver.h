#ifndef CAN_DRIVER_H
#define CAN_DRIVER_H

#include "Std_Types.h"        // AUTOSAR standard types
#include "Det.h"              // Development Error Tracer
#include "CanIf_Types.h"      // AUTOSAR CAN Interface types
#include "Compiler.h"         // AUTOSAR compiler abstraction

/* AUTOSAR Module ID for CAN Driver (ECU2-specific) */
#define CAN_DRIVER_MODULE_ID       60U
#define CAN_DRIVER_INSTANCE_ID     0U

/* AUTOSAR Error Codes for CAN Driver */
#define CAN_E_PARAM_POINTER        0x01U  /* Invalid pointer */
#define CAN_E_PARAM_CONFIG         0x02U  /* Invalid configuration */
#define CAN_E_NOT_INITIALIZED      0x03U  /* Module not initialized */

/* AUTOSAR CAN Driver Configuration Type for ECU2 */
typedef struct {
    uint32 CanControllerBaudrate;  /* Baudrate of CAN controller */
    uint8 CanControllerId;         /* ID of CAN controller */
    const void* CanControllerConfig; /* Hardware-specific configuration */
} Can_ConfigType;

/* AUTOSAR CAN Driver API Prototypes for ECU2 */

/**
 * @brief Initializes the CAN Driver for ECU2 with the provided configuration.
 * @param ConfigPtr Pointer to the CAN configuration structure.
 * @return None
 * @pre None
 * @post CAN Driver is initialized or an error is reported if ConfigPtr is invalid.
 */
FUNC(void, CAN_CODE) Can_Init(P2CONST(Can_ConfigType, AUTOMATIC, CAN_CONFIG_DATA) ConfigPtr);

/**
 * @brief De-initializes the CAN Driver for ECU2 and releases resources.
 * @param None
 * @return None
 * @pre CAN Driver must be initialized.
 * @post CAN Driver is de-initialized or an error is reported if not initialized.
 */
FUNC(void, CAN_CODE) Can_DeInit(void);

/**
 * @brief Reads a PDU from the CAN bus for ECU2.
 * @param Hth CAN Hardware Handle.
 * @param PduInfoPtr Pointer to the PDU information structure to store received data.
 * @return E_OK if the read operation is successful, E_NOT_OK otherwise.
 * @pre CAN Driver must be initialized and PduInfoPtr must be valid.
 * @post PDU data is stored in PduInfoPtr or an error is reported if invalid.
 */
FUNC(Std_ReturnType, CAN_CODE) Can_Read(Can_HwHandleType Hth, P2VAR(Can_PduType, AUTOMATIC, CAN_APPL_DATA) PduInfoPtr);

/**
 * @brief Writes a PDU to the CAN bus for ECU2 (optional, if needed).
 * @param Hth CAN Hardware Handle.
 * @param PduInfoPtr Pointer to the PDU information structure containing data to send.
 * @return E_OK if the write operation is successful, E_NOT_OK otherwise.
 * @pre CAN Driver must be initialized and PduInfoPtr must be valid.
 * @post PDU data is sent or an error is reported if invalid.
 */
FUNC(Std_ReturnType, CAN_CODE) Can_Write(Can_HwHandleType Hth, P2CONST(Can_PduType, AUTOMATIC, CAN_APPL_DATA) PduInfoPtr);

#endif /* CAN_DRIVER_H */