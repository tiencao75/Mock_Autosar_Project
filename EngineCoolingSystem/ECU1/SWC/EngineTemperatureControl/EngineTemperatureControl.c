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
FUNC(void, AUTOMATIC) CalcCoolingSpeed(P2VAR(CoolingData, AUTOMATIC, RTE_APPL_DATA) data) {
    uint16 engineTemp;
    uint16 airTemp;
    uint16 calibrationDataEngine;
    uint16 calibrationDataAir;
    

    /* Đọc dữ liệu nhiệt độ từ RTE */
    if (Rte_Read_RP_EngineTemperatureControl_EngineTemperature(&engineTemp) == E_OK &&
        Rte_Read_RP_EngineTemperatureControl_AirTemperature(&airTemp) == E_OK) {
		
		/* Đọc dữ liệu hiệu chỉnh từ RTE */
        if (Rte_Read_RP_Parameter_GetCalibrationData(&calibrationDataEngine, &calibrationDataAir) == E_OK) {
					
				data->engineTemp = engineTemp;
        data->airTemp = airTemp;

        /* Điều chỉnh tốc độ quạt làm mát */
        if (engineTemp > calibrationDataEngine) {
            FanSpeed = 100; /* Quạt chạy tối đa */
        } else if (engineTemp > (calibrationDataEngine - 30)) {
            FanSpeed = 70;  /* Quạt chạy ở mức trung bình */
        } else {
            FanSpeed = 0; /* Tắt quạt nếu nhiệt độ thấp */
        }

        /* Điều chỉnh tốc độ bơm nước dựa trên nhiệt độ động cơ và hiệu chỉnh */
        if (engineTemp > calibrationDataEngine) {
            PumpSpeed = 100; /* Bơm chạy tối đa */
        } else if (engineTemp > (calibrationDataEngine - 30)) {
            PumpSpeed = 50;  /* Bơm chạy ở mức trung bình */
        } else {
            PumpSpeed = 0;
        }

        /* Bật cảnh báo nếu nhiệt độ quá cao so với giá trị hiệu chỉnh */
        if (engineTemp > (calibrationDataEngine + 10)) {
            WarningLight = 1; /* Cảnh báo nhiệt độ quá cao */
        } else {
            WarningLight = 0;
        }
				
				data->FanSpeed = FanSpeed;
				data->PumpSpeed = PumpSpeed;
				data->WarningLight = WarningLight;
        /* Ghi giá trị vào RTE */
        Rte_Write_PP_EngineTemperatureControl_FanSpeed(&FanSpeed);
        Rte_Write_PP_EngineTemperatureControl_PumpSpeed(&PumpSpeed);
        Rte_Write_PP_EngineTemperatureControl_WarningLight(&WarningLight);

    } else {
        // printf("CalcCoolingSpeed: Failed to read temperature data.\n");
    }
	}
}

/******************************************************************************/  
/* Runnable: SendControlSignal                                                */
/* Gửi tín hiệu điều khiển tốc độ quạt, bơm nước đến ECU_2 thông qua Com      */  
/******************************************************************************/  
FUNC(void, AUTOMATIC) SendControlSignal(void) {
		
    if (Com_SendSignal(1, (const void*)&FanSpeed) == COM_OK) {
        // printf("SendControlSignal: Sent Fan Speed = %d RPM to ECU_2\n", FanSpeed);
    } else {
        // printf("SendControlSignal: Failed to send Fan Speed.\n");
    }

    if (Com_SendSignal(2, (const void*)&PumpSpeed) == COM_OK) {
        // printf("SendControlSignal: Sent Pump Speed = %d to ECU_2\n", PumpSpeed);
    } else {
        // printf("SendControlSignal: Failed to send Pump Speed.\n");
    }
}
