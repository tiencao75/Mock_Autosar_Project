#ifndef COM_H
#define COM_H

#include "Std_Types.h"
#include "Compiler.h"
#include "Det.h"
#include "PDU_R.h"

#define COM_MODULE_ID  63U
#define COM_INSTANCE_ID 0U

#define COM_E_PARAM_POINTER  0x01U
#define COM_E_PARAM_CONFIG   0x02U
#define COM_E_NOT_INITIALIZED 0x03U

#define COM_OK     E_OK
#define COM_NOT_OK E_NOT_OK

// typedef uint16 Com_SignalIdType;

typedef struct {
    VAR(Com_SignalIdType, COM_VAR) signalId;
    VAR(uint16, COM_VAR) signalValue;  /* Giữ lại cho tương thích */
    VAR(uint16, COM_VAR) fanSpeed;     /* Thêm để lưu fanSpeed */
    VAR(uint16, COM_VAR) pumpSpeed;    /* Thêm để lưu pumpSpeed */
    VAR(uint8, COM_VAR) warningStatus; /* Thêm để lưu warningStatus */
} Com_SignalType;

typedef struct {
    VAR(uint8, COM_VAR) comChannel;
    VAR(Com_SignalIdType, COM_VAR) signalId;
    VAR(boolean, COM_VAR) isEnabled;
} Com_ConfigType;

FUNC(void, COM_CODE) Com_Init(P2CONST(Com_ConfigType, AUTOMATIC, COM_CONFIG_DATA) ConfigPtr);
FUNC(Std_ReturnType, COM_CODE) Com_ReceiveSignal(Com_SignalIdType SignalId, P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr);
FUNC(Std_ReturnType, COM_CODE) Com_SendSignal(Com_SignalIdType SignalId, P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr);
FUNC(Std_ReturnType, COM_CODE) Com_TriggerIPDUSend(PduIdType PduId);

#endif /* COM_H */