#ifndef CANIF_TYPES_H
#define CANIF_TYPES_H

#include "Std_Types.h"        // AUTOSAR standard types
#include "Compiler.h"         // AUTOSAR compiler abstraction

/* AUTOSAR Module ID for CAN Interface Types */
#define CANIF_TYPES_MODULE_ID      61U

/* AUTOSAR CAN Interface Types */

/* CAN Hardware Object Handle Type */
typedef uint16 Can_HwHandleType;

/* CAN Identifier Type */
typedef uint32 Can_IdType;

/* CAN PDU Type */
typedef struct {
    PduIdType swPduHandle;  /* Software PDU handle */
    uint8 length;           /* Length of PDU data (SduLength) */
    Can_IdType id;          /* CAN Identifier (CanId) */
    uint8* sdu;             /* Pointer to PDU data (SduData) */
} Can_PduType;

/* CAN Interface Configuration Type */
typedef struct {
    uint8 CanIfChannelId;       /* CAN Channel ID */
    uint16 MaxPduCount;         /* Maximum number of PDUs that can be handled */
    const void* CanIfConfig;    /* Hardware-specific configuration */
} CanIf_ConfigType;

/* CAN Interface State Type */
typedef enum {
    CANIF_UNINIT = 0,  /* CAN Interface is not initialized */
    CANIF_READY        /* CAN Interface is initialized and ready */
} CanIf_StateType;

/* CAN Interface Controller State Type */
typedef enum {
    CANIF_CS_UNINIT = 0,  /* Controller is not initialized */
    CANIF_CS_STARTED,     /* Controller is started */
    CANIF_CS_STOPPED,     /* Controller is stopped */
    CANIF_CS_SLEEP        /* Controller is in sleep mode */
} CanIf_ControllerStateType;

/* CAN Interface Transceiver State Type */
typedef enum {
    CANIF_TRCV_MODE_NORMAL = 0,  /* Normal mode */
    CANIF_TRCV_MODE_STANDBY,     /* Standby mode */
    CANIF_TRCV_MODE_SLEEP        /* Sleep mode */
} CanIf_TransceiverModeType;

/* CAN Interface PDU Mode Type */
typedef enum {
    CANIF_OFFLINE = 0,  /* PDU is offline */
    CANIF_ONLINE         /* PDU is online */
} CanIf_PduModeType;

#endif /* CANIF_TYPES_H */