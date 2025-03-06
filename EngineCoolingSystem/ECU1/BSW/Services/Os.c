#include "Os.h"
#include "Rte_EngineTemperatureControl.h"
#include <stdio.h>

int  ReadSensor_Task_Toggle = 0 ; 
int  ProcessData_Task_Toggle = 0 ; 
int  SendData_Task_Toggle = 0;
/* Function Definitions */
void SystemInit(void) {
    /* Khởi tạo hệ thống nếu cần thiết */
}

/* Main function to start the OS */
int main(void) {
    StartOS();
    while (1) {
        /* OS chạy liên tục */
    }
    return 0;
}

/* Read Sensor Task */
TASK(ReadSensor_Task) {
	
    while(1){
    WaitEvent(BE_Sensor);
    ReadSensor_Task_Toggle = 1;			
    Rte_Call_PP_GetEngineTemperature();
    Rte_Call_PP_GetAirTemperature();

    SetEvent(ProcessData_Task, BE_ReadSensor); 
    ReadSensor_Task_Toggle = 0;
    ClearEvent(BE_Sensor);
    }
}

/* Process Data Task */
TASK(ProcessData_Task) {
//EventMaskType eventMask;

    while(1){
    WaitEvent(BE_ReadSensor);
    ProcessData_Task_Toggle = 1;

    Rte_Call_PP_CalcCoolingSpeed();

SetEvent(SendData_Task, BE_DataReady); 
    ProcessData_Task_Toggle = 0;
    ClearEvent(BE_ReadSensor); 
    }
}

/* Send Data Task */
TASK(SendData_Task) {
//EventMaskType eventMask;
    
    while (1){
    WaitEvent(BE_DataReady);
    SendData_Task_Toggle = 1;
        
    Rte_Call_PP_SendControlSignal();	
    
    SendData_Task_Toggle = 0;
    ClearEvent(BE_DataReady);
    //SendData_Task_Toggle ^= 0x1U;
    }
}

