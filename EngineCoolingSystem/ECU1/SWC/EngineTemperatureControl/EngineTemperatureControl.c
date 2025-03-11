#include "EngineTemperatureControl.h"

#include <stdio.h>

/*----------------------------------------------------------------------------*/
/* Biến toàn cục lưu trữ dữ liệu điều khiển nhiệt độ                          */
/*----------------------------------------------------------------------------*/
static uint16 FanSpeed = 0;  /* Tốc độ quạt làm mát */
static uint16 PumpSpeed = 0; /* Tốc độ bơm nước */
static uint8 WarningLight = 0; /* Cảnh báo nhiệt độ */

/*----------------------------------------------------------------------------*/
/* Khởi tạo bộ điều khiển nhiệt độ động cơ                                    */
/*----------------------------------------------------------------------------*/
FUNC(void, AUTOMATIC) EngineTemperatureControl_Init(void) {
    printf("EngineTemperatureControl: Initialized.\n");
}

/******************************************************************************/  
/* Runnable: CalcCoolingSpeed                                                 */
/* Tính toán tốc độ quạt và tốc độ bơm dựa trên nhiệt độ động cơ              */  
/******************************************************************************/  
FUNC(Std_ReturnType, AUTOMATIC) CalcCoolingSpeed(P2VAR(CoolingData, AUTOMATIC, RTE_APPL_DATA) data) {
    uint16 engineTemp = 0;
    uint16 airTemp = 0;
    uint16 calibrationDataEngine = 0;
    uint16 calibrationDataAir = 0;

    /* Đọc dữ liệu từ RTE */
    if (Rte_Read_RP_EngineTemperatureControl_EngineTemperature(&engineTemp) != E_OK ||
        Rte_Read_RP_EngineTemperatureControl_AirTemperature(&airTemp) != E_OK) {
        Rte_Call_EngineTemperatureControl_ReportToDem(EVENT_03, DEM_EVENT_STATUS_FAILED);
        Rte_Write_PP_NVBlock_StoreErrorToRTE(U1001);
        return E_NOK;
    }
    if (Rte_Read_RP_Parameter_GetCalibrationData(&calibrationDataEngine, &calibrationDataAir) != E_OK) {
        return E_NOK;
    }

    /* Kiểm tra phạm vi nhiệt độ */
    if (engineTemp > 150) {
        Rte_Call_EngineTemperatureControl_ReportToDem(EVENT_01, DEM_EVENT_STATUS_FAILED);
        Rte_Write_PP_NVBlock_StoreErrorToRTE(B1C02);
    } else if (engineTemp == 0 && airTemp == 0) { // Giả định không nhận được tín hiệu
        Rte_Call_EngineTemperatureControl_ReportToDem(EVENT_02, DEM_EVENT_STATUS_FAILED);
        Rte_Write_PP_NVBlock_StoreErrorToRTE(B1C03);
    }
    
    /* Lưu dữ liệu vào cấu trúc */
    data->engineTemp = engineTemp;
    data->airTemp = airTemp;

    /* Tính tốc độ cơ bản dựa trên nhiệt độ động cơ */
    uint16 baseSpeed = SPEED_MIN;
    if (engineTemp >= TEMP_MAX_SPEED) {
        baseSpeed = SPEED_MAX;  /* Tốc độ tối đa khi quá nóng */
    } else if (engineTemp >= TEMP_FAN_START) {
        /* Tăng tuyến tính từ 85°C đến 110°C */
        baseSpeed = ((engineTemp - TEMP_FAN_START) * SPEED_MAX) / (TEMP_MAX_SPEED - TEMP_FAN_START);
    }

    /* Điều chỉnh dựa trên nhiệt độ không khí */
    uint16 adjustment = 0;
    if (engineTemp >= TEMP_FAN_START)
    {
        if (airTemp > calibrationDataAir + AIR_TEMP_HOT) {
        adjustment = SPEED_ADJUST;  /* Chỉ cộng thêm khi không khí nóng */
        }
    }
    
    /* Tính tốc độ */
    FanSpeed = baseSpeed + adjustment;
    PumpSpeed = baseSpeed + adjustment;

    /* Giới hạn tốc độ */
    if (FanSpeed > SPEED_MAX) {
        FanSpeed = SPEED_MAX;
    }
    if (PumpSpeed > SPEED_MAX) {
        PumpSpeed = SPEED_MAX;
    }

    /* Kiểm tra cảnh báo */
    WarningLight = (engineTemp >= calibrationDataEngine) ? 1U : 0U;

    /* Cập nhật dữ liệu */
    data->FanSpeed = FanSpeed;
    data->PumpSpeed = PumpSpeed;
    data->WarningLight = WarningLight;

    /* Ghi vào RTE */
    Rte_Write_PP_EngineTemperatureControl_FanSpeed(&FanSpeed);
    Rte_Write_PP_EngineTemperatureControl_PumpSpeed(&PumpSpeed);
    Rte_Write_PP_EngineTemperatureControl_WarningLight(&WarningLight); 
    return E_OK;
}

/******************************************************************************/  
/* Runnable: SendControlSignal                                                */
/* Gửi tín hiệu điều khiển tốc độ quạt, bơm nước đến ECU_2 thông qua Com      */  
/******************************************************************************/  
FUNC(Std_ReturnType, AUTOMATIC) SendControlSignal(void) {
    if (Rte_Call_PP_SignalSpeed() == E_OK) {
        return E_OK;
    } else {
        Rte_Call_EngineTemperatureControl_ReportToDem(EVENT_04, DEM_EVENT_STATUS_FAILED);
        Rte_Write_PP_NVBlock_StoreErrorToRTE(U1002);
        return E_NOK;
    }
}
