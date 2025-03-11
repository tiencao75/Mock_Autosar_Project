#include "Rte_EngineTemperatureActuator.h"
#include "Com.h"
#include "Det.h"

#define RTE_OK     E_OK
#define RTE_NOT_OK E_NOT_OK

#define RTE_E_PARAM_POINTER 0x01U

volatile VAR(uint16, RTE_VAR) Rte_FanSpeed = 0;      /* Tốc độ quạt */
volatile VAR(uint16, RTE_VAR) Rte_PumpSpeed = 0;     /* Tốc độ bơm */
volatile VAR(uint8, RTE_VAR) Rte_WarningStatus = 0;  /* Trạng thái đèn */

FUNC(void, RTE_CODE) Rte_InitEngineTemperatureActuator(
    P2CONST(Rte_EngineTempActuatorConfigType, RTE_CONST, AUTOMATIC) config
) {
    IoHwAb_InitEngineTempActuator(config);
}

FUNC(Std_ReturnType, RTE_CODE) Rte_ReadControlSignal(
    P2VAR(Rte_ControlDataType, RTE_APPL_DATA, AUTOMATIC) data
) {
    if (data == NULL_PTR) {
        Det_ReportError(13, 0, 4, RTE_E_PARAM_POINTER);
        return RTE_NOT_OK;
    }

    Com_SignalType signalData;
    Com_SignalIdType signalId = 1;

    if (Com_ReceiveSignal(signalId, &signalData) != COM_OK) {
        Det_ReportError(13, 0, 4, RTE_E_PARAM_POINTER);
        return RTE_NOT_OK;
    }

    Rte_FanSpeed = signalData.fanSpeed;
    Rte_PumpSpeed = signalData.pumpSpeed;
    Rte_WarningStatus = signalData.warningStatus;

    data->fanSpeed = Rte_FanSpeed;
    data->pumpSpeed = Rte_PumpSpeed;
    data->warningStatus = Rte_WarningStatus;

    return RTE_OK;
}

/* Điều chỉnh tốc độ quạt */
FUNC(Std_ReturnType, RTE_CODE) Rte_ChangeSpeedEngineFan(
    VAR(Pwm_ChannelType, RTE_APPL_DATA) channelId,  // Thêm channelId
    VAR(uint8, RTE_APPL_DATA) dutyCycle
) {
    return IoHwAb_ChangeSpeedEngineFan(channelId, dutyCycle);  // Truyền channelId xuống IoHwAb
}

/* Điều chỉnh tốc độ bơm */
FUNC(Std_ReturnType, RTE_CODE) Rte_ChangeSpeedEnginePump(
    VAR(Pwm_ChannelType, RTE_APPL_DATA) channelId,  // Thêm channelId
    VAR(uint8, RTE_APPL_DATA) dutyCycle
) {
    return IoHwAb_ChangeSpeedEnginePump(channelId, dutyCycle);  // Truyền channelId xuống IoHwAb
}

/* Điều khiển đèn cảnh báo */
FUNC(Std_ReturnType, RTE_CODE) Rte_ChangeEngineTemperatureWarningLight(
    VAR(Dio_ChannelType, RTE_APPL_DATA) channelId,  // Thêm channelId
    VAR(Dio_LevelType, RTE_APPL_DATA) level
) {
    return IoHwAb_ChangeEngineTemperatureWarningLight(channelId, level);  // Truyền channelId xuống IoHwAb
}

FUNC(Std_ReturnType, RTE_CODE) Rte_ReadDataControlSignal(
    P2VAR(Rte_ControlDataType, RTE_APPL_DATA, AUTOMATIC) data
) {
    if (data == NULL_PTR) {
        Det_ReportError(13, 0, 5, RTE_E_PARAM_POINTER);
        return RTE_NOT_OK;
    }

    data->fanSpeed = Rte_FanSpeed;
    data->pumpSpeed = Rte_PumpSpeed;
    data->warningStatus = Rte_WarningStatus;

    return RTE_OK;
}