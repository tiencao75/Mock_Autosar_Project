#include "Os.h"
#include "Rte_EngineTemperatureControl.h"
#include <stdio.h>

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
    printf("Executing ReadSensor_Task...\n");

    /* Gọi API RTE để đọc cảm biến */
    Rte_Call_PP_GetEngineTemperature();
    Rte_Call_PP_GetAirTemperature();

    /* Kích hoạt event cho ProcessData_Task */
    SetEvent(TASK_ProcessData, BE_DataReady);

    TerminateTask();
}

/* Process Data Task */
TASK(ProcessData_Task) {
    EventMaskType eventMask;

    /* Chờ event */
    WaitEvent(BE_DataReady);
    GetEvent(TASK_ProcessData, &eventMask);

    /* Xóa event trước khi xử lý để tránh kích hoạt lại Task không cần thiết */
    ClearEvent(BE_DataReady);

    printf("Executing ProcessData_Task...\n");

    /* Gọi API RTE để xử lý dữ liệu */
    Rte_Call_PP_CalcCoolingSpeed();

    /* Kích hoạt event cho SendData_Task */
    SetEvent(TASK_SendData, BE_DataSent);

    TerminateTask();
}

/* Send Data Task */
TASK(SendData_Task) {
    EventMaskType eventMask;

    /* Chờ event */
    WaitEvent(BE_DataSent);
    GetEvent(TASK_SendData, &eventMask);

    /* Xóa event trước khi xử lý để đảm bảo Task không bị kích hoạt lại vô nghĩa */
    ClearEvent(BE_DataSent);

    printf("Executing SendData_Task...\n");

    /* Gọi API RTE để gửi tín hiệu điều khiển */
    Rte_Call_PP_SendControlSignal();

    TerminateTask();
}


