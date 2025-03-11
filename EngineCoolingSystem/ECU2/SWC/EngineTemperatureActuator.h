#ifndef ENGINETEMPACTUATOR_H
#define ENGINETEMPACTUATOR_H

#include "Compiler.h"
#include "Std_Types.h"
#include "Det.h"
#include "Rte_EngineTemperatureActuator.h"  /* Giao tiếp với RTE */
#include "EngineTemp_Types.h"

#define SWC_OK       E_OK
#define SWC_NOT_OK   E_NOT_OK

#define SWC_E_PARAM_POINTER    0x01U
#define SWC_E_PARAM_CONFIG     0x02U
#define SWC_E_NOT_INITIALIZED  0x03U
#define SWC_E_PARAM_DUTYCYCLE  0x04U
#define SWC_E_PARAM_LEVEL      0x05U
#define SWC_E_PARAM_SIGNAL     0x06U
#define SWC_E_PARAM_CHANNEL    0x07U  // Thêm lỗi cho channelId không hợp lệ

typedef struct {
    VAR(boolean, SWC_VAR) isEnabled;
    VAR(uint16, SWC_VAR) temperatureThreshold;
} EngineTempActuatorConfigType;

FUNC(void, SWC_CODE) EngineTemperatureActuator_Init(
    P2CONST(EngineTempActuatorConfigType, SWC_CONST, AUTOMATIC) config
);

// Thêm channelId vào các hàm điều khiển
FUNC(Std_ReturnType, SWC_CODE) ChangeSpeedEnginePump(
    VAR(Pwm_ChannelType, SWC_APPL_DATA) channelId,  // Thêm channelId
    VAR(uint8, SWC_APPL_DATA) dutyCycle
);

FUNC(Std_ReturnType, SWC_CODE) ChangeSpeedEngineFan(
    VAR(Pwm_ChannelType, SWC_APPL_DATA) channelId,  // Thêm channelId
    VAR(uint8, SWC_APPL_DATA) dutyCycle
);

FUNC(Std_ReturnType, SWC_CODE) ChangeEngineTemperatureWarningLight(
    VAR(Dio_ChannelType, SWC_APPL_DATA) channelId,  // Thêm channelId
    VAR(Dio_LevelType, SWC_APPL_DATA) level
);

FUNC(Std_ReturnType, SWC_CODE) ReadControlSignal(
    P2VAR(EngineTemp_ControlDataType, SWC_APPL_DATA, AUTOMATIC) data
);

// Cập nhật macro để truyền channelId
#define Swc_Run_ChangeSpeedEnginePump(channelId, dutyCycle) \
    ChangeSpeedEnginePump(channelId, dutyCycle)

#define Swc_Run_ChangeSpeedEngineFan(channelId, dutyCycle) \
    ChangeSpeedEngineFan(channelId, dutyCycle)

#define Swc_Run_ChangeEngineTemperatureWarningLight(channelId, level) \
    ChangeEngineTemperatureWarningLight(channelId, level)

#define Swc_Run_ReadControlSignal(data) \
    ReadControlSignal(data)

#endif /* ENGINETEMPACTUATOR_H */