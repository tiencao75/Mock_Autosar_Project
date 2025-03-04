#include "EngineTemperatureControl.h"
#include "Rte_EngineTemperatureControl.h"
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
FUNC(void, AUTOMATIC) CalcCoolingSpeed(void) {
    uint16 engineTemp;
    uint16 airTemp;

    /* Đọc dữ liệu nhiệt độ từ RTE */
    if (Rte_Read_RP_EngineTemperatureControl_EngineTemperature(&engineTemp) == E_OK &&
        Rte_Read_RP_EngineTemperatureControl_AirTemperature(&airTemp) == E_OK) {

        /* Điều chỉnh tốc độ quạt làm mát */
        if (engineTemp > 90) {
            FanSpeed = 100; /* Quạt chạy tối đa */
        } else if (engineTemp > 70) {
            FanSpeed = 70;
        } else {
            FanSpeed = 0; /* Tắt quạt nếu nhiệt độ thấp */
        }

        /* Điều chỉnh tốc độ bơm nước */
        if (engineTemp > 90) {
            PumpSpeed = 100;
        } else if (engineTemp > 70) {
            PumpSpeed = 50;
        } else {
            PumpSpeed = 0;
        }

        /* Bật cảnh báo nếu nhiệt độ quá cao */
        if (engineTemp > 110) {
            WarningLight = 1;
        } else {
            WarningLight = 0;
        }

        /* Ghi giá trị vào RTE */
        Rte_Write_PP_EngineTemperatureControl_FanSpeed(&FanSpeed);
        Rte_Write_PP_EngineTemperatureControl_PumpSpeed(&PumpSpeed);
        Rte_Write_PP_EngineTemperatureControl_WarningLight(&WarningLight);

        printf("CalcCoolingSpeed: Engine Temp = %d°C, Fan Speed = %d RPM, Pump Speed = %d, Warning Light = %d\n",
               engineTemp, FanSpeed, PumpSpeed, WarningLight);
    } else {
        printf("CalcCoolingSpeed: Failed to read temperature data.\n");
    }
}

/******************************************************************************/  
/* Runnable: SendControlSignal                                                */
/* Gửi tín hiệu điều khiển tốc độ quạt, bơm nước đến ECU_2 thông qua Com      */  
/******************************************************************************/  
FUNC(void, AUTOMATIC) SendControlSignal(void) {
    Com_SignalType fanSpeedSignal = {FanSpeed, 1};  // ID 1 cho tốc độ quạt
    Com_SignalType pumpSpeedSignal = {PumpSpeed, 2}; // ID 2 cho tốc độ bơm

    if (Com_SendSignal(&fanSpeedSignal) == COM_OK) {
        printf("SendControlSignal: Sent Fan Speed = %d RPM to ECU_2\n", FanSpeed);
    } else {
        printf("SendControlSignal: Failed to send Fan Speed.\n");
    }

    if (Com_SendSignal(&pumpSpeedSignal) == COM_OK) {
        printf("SendControlSignal: Sent Pump Speed = %d to ECU_2\n", PumpSpeed);
    } else {
        printf("SendControlSignal: Failed to send Pump Speed.\n");
    }
}
