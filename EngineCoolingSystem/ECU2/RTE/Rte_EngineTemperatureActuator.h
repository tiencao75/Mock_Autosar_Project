#ifndef RTE_ENGINETEMPACTUATOR_H
#define RTE_ENGINETEMPACTUATOR_H

#include "Compiler.h"
#include "Std_Types.h"
#include "Det.h"
#include "Dem.h"
#include "Com.h"
#include "IoHwAb_EngineTempActuator.h"
#include "EngineTemperatureActuator.h"
#include "EngineTemp_Types.h"


#define RTE_OK       E_OK
#define RTE_NOT_OK   E_NOT_OK

#define RTE_E_PARAM_POINTER    0x01U
#define RTE_E_PARAM_CONFIG     0x02U
#define RTE_E_NOT_INITIALIZED  0x03U
#define RTE_E_PARAM_DUTYCYCLE  0x04U
#define RTE_E_PARAM_LEVEL      0x05U
#define RTE_E_PARAM_CHANNEL    0x06U

typedef struct {
    VAR(boolean, RTE_VAR) isEnabled;
} Rte_EngineTempActuatorConfigType;

// typedef struct {
//     VAR(uint16, RTE_VAR) fanSpeed;
//     VAR(uint16, RTE_VAR) pumpSpeed;
//     VAR(uint8, RTE_VAR) warningStatus;
// } Rte_ControlDataType;

typedef EngineTemp_ControlDataType Rte_ControlDataType;

FUNC(void, RTE_CODE) Rte_InitEngineTemperatureActuator(
    P2CONST(Rte_EngineTempActuatorConfigType, RTE_CONST, AUTOMATIC) config
);

FUNC(Std_ReturnType, RTE_CODE) Rte_ChangeSpeedEngineFan(
    VAR(Pwm_ChannelType, RTE_APPL_DATA) channelId,
    VAR(uint8, RTE_APPL_DATA) dutyCycle
);

FUNC(Std_ReturnType, RTE_CODE) Rte_ChangeSpeedEnginePump(
    VAR(Pwm_ChannelType, RTE_APPL_DATA) channelId,
    VAR(uint8, RTE_APPL_DATA) dutyCycle
);

FUNC(Std_ReturnType, RTE_CODE) Rte_ChangeEngineTemperatureWarningLight(
    VAR(Dio_ChannelType, RTE_APPL_DATA) channelId,
    VAR(Dio_LevelType, RTE_APPL_DATA) level
);

FUNC(Std_ReturnType, RTE_CODE) Rte_ReadControlSignal(
    P2VAR(Rte_ControlDataType, RTE_APPL_DATA, AUTOMATIC) data
);

FUNC(Std_ReturnType, RTE_CODE) Rte_ReadDataControlSignal(
    P2VAR(Rte_ControlDataType, RTE_APPL_DATA, AUTOMATIC) data
);

// Macro gọi hàm RTE
#define Rte_Run_ChangeSpeedEngineFan(channelId, dutyCycle) Rte_ChangeSpeedEngineFan(channelId, dutyCycle)
#define Rte_Run_ChangeSpeedEnginePump(channelId, dutyCycle) Rte_ChangeSpeedEnginePump(channelId, dutyCycle)
#define Rte_Run_ChangeEngineTemperatureWarningLight(channelId, level) Rte_ChangeEngineTemperatureWarningLight(channelId, level)
#define Rte_Run_ReadControlSignal(data) Rte_ReadControlSignal(data)

// Macro gọi hàm SWC (không cần include SWC header, chỉ dùng tên hàm)
#define Rte_Run_Swc_ChangeSpeedEngineFan(channelId, dutyCycle) ChangeSpeedEngineFan(channelId, dutyCycle)
#define Rte_Run_Swc_ChangeSpeedEnginePump(channelId, dutyCycle) ChangeSpeedEnginePump(channelId, dutyCycle)
#define Rte_Run_Swc_ChangeEngineTemperatureWarningLight(channelId, level) ChangeEngineTemperatureWarningLight(channelId, level)
#define Rte_Run_Swc_ReadControlSignal(data) ReadControlSignal(data)

#endif /* RTE_ENGINETEMPACTUATOR_H */