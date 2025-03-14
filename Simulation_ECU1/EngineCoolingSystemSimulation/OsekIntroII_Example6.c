#include "os.h"
#include "Rte_EngineTemperatureControl.h"
#include "Rte_EngineTemperatureSensor.h"
#include <stdio.h>

int  ReadSensor_Task_Toggle = 0 ; 
int  ProcessData_Task_Toggle = 0 ; 
int  SendData_Task_Toggle = 0;
CoolingData data = {0, 0, 0, 0, 0};
volatile uint8_t Simulate_Error = 0;



DeclareTask(ReadSensor_Task);
DeclareTask(ProcessData_Task);
DeclareTask(SendData_Task);

void SystemInit(void)
{
}

int main(void)
{
  StartOS();
  while(1); /* Should not be executed */
  return 0;
}

/* Read Sensor Task */
TASK(ReadSensor_Task) {		
		while(true){
		WaitEvent(BE_Sensor);
		ReadSensor_Task_Toggle = 1;
		Rte_Call_PP_GetEngineTemperature();
    Rte_Call_PP_GetAirTemperature();

    SetEvent(ProcessData_Task, BE_ReadSensor); 
		/*Gia lap loi*/
		if (OsCnt_GetSystemCounter() == 2000)
		{
			Simulate_Error = 1;
		}
		if (Simulate_Error == 1)
		{
			// printf("Sensor Task Failed! System will reset...\n");
			while (1);
		}
		ClearEvent(BE_Sensor);
		ReadSensor_Task_Toggle = 0;
		}
		
}

/* Process Data Task */
TASK(ProcessData_Task) {
		while(true){
		WaitEvent(BE_ReadSensor);
		ProcessData_Task_Toggle = 1;
   
    Rte_Call_PP_Calibration_CalibrationData();
		Rte_Call_PP_CalcCoolingSpeed(&data);
		Rte_Call_PP_HandleErrorToNVM();

    SetEvent(SendData_Task, BE_DataReady); 
		ClearEvent(BE_ReadSensor); 
		ProcessData_Task_Toggle = 0;
		}
}

/* Send Data Task */
TASK(SendData_Task) {
    //EventMaskType eventMask;
		
		while (true){
		WaitEvent(BE_DataReady);
		SendData_Task_Toggle = 1;
			
    Rte_Call_PP_SendControlSignal();	
		
		
		ClearEvent(BE_DataReady);
		SendData_Task_Toggle = 0;
		//SendData_Task_Toggle ^= 0x1U;
		}
}
