#include "os.h"
#include "Rte_EngineTemperatureActuator.h"
#include "EngineTemperatureActuator.h"
#include <stdio.h>

int ReadControlSignal_Task_Toggle = 0;  // 0 = OFF, 1 = ON
int Actuator_Task_Toggle = 0;           // 0 = OFF, 1 = ON
static int a = 1;                       // Placeholder variable
static Rte_ControlDataType controlData; // Bi?n toàn c?c du?c dùng chung

// Ð?nh nghia các channelId c? d?nh cho ví d? (có th? thay d?i theo yêu c?u)
#define FAN_CHANNEL_ID      0  // Kênh PWM cho qu?t
#define PUMP_CHANNEL_ID     1  // Kênh PWM cho bom
#define WARNING_LIGHT_CHANNEL_ID 2  // Kênh DIO cho dèn c?nh báo

DeclareTask(ReadControlSignal_Task);
DeclareTask(Actuator_Task);

void SystemInit(void) {
    /* Add hardware initialization here if needed */
} 

int main(void) {
    StartOS();
    while (1); /* Infinite loop, scheduler takes over */
    return 0;
}

TASK(ReadControlSignal_Task) {
    while (TRUE) {
        WaitEvent(BE_CONTROL_SIGNAL_READ);
        ReadControlSignal_Task_Toggle = 1;
        if (Rte_Run_Swc_ReadControlSignal(&controlData) == SWC_OK) {  // G?i SWC d? d?c tín hi?u, luu vào controlData
            //ReadControlSignal_Task_Toggle = 0;
            SetEvent(Actuator_Task, BE_TEMPERATURE_UPDATE);
            ClearEvent(BE_CONTROL_SIGNAL_READ);
            ChainTask(Actuator_Task);
        } else {
            //ReadControlSignal_Task_Toggle = 0;
            ClearEvent(BE_CONTROL_SIGNAL_READ);
        }
    }
}

TASK(Actuator_Task) {
    while (TRUE) {
        WaitEvent(BE_TEMPERATURE_UPDATE);
				ReadControlSignal_Task_Toggle = 0;
        Actuator_Task_Toggle = 1;

        // L?y d? li?u t? RTE và luu vào controlData
        if (Rte_ReadDataControlSignal(&controlData) == RTE_OK) {
            uint8_t pumpDutyCycle = (uint8_t)controlData.pumpSpeed;
            Rte_Run_Swc_ChangeSpeedEnginePump(PUMP_CHANNEL_ID, pumpDutyCycle);  // Truy?n channelId cho bom

            uint8_t fanDutyCycle = (uint8_t)controlData.fanSpeed;
            Rte_Run_Swc_ChangeSpeedEngineFan(FAN_CHANNEL_ID, fanDutyCycle);  // Truy?n channelId cho qu?t

            Dio_LevelType lightLevel = (controlData.warningStatus == 1) ? DIO_HIGH : DIO_LOW;
            Rte_Run_Swc_ChangeEngineTemperatureWarningLight(WARNING_LIGHT_CHANNEL_ID, lightLevel);  // Truy?n channelId cho dèn
        }

        Actuator_Task_Toggle = 0;
        ClearEvent(BE_TEMPERATURE_UPDATE);
    }
}