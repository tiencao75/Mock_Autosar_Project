#include "EngineTemperatureSensor.h"
#include "Rte_EngineTemperatureSensor.h"
#include <stdio.h>

/*----------------------------------------------------------------------------*/
/* Function Implementations                                                   */
/*----------------------------------------------------------------------------*/

/* Khởi tạo cảm biến nhiệt độ động cơ */
FUNC(void, AUTOMATIC) EngineTemperatureSensor_Init(void) {
    printf("EngineTemperatureSensor: Initialized.\n");
}

/******************************************************************************/  
/* Runnable: GetEngineTemperature                                             */
/* Đọc giá trị nhiệt độ động cơ từ RTE và truyền xuống BSW                   */  
/******************************************************************************/  
FUNC(void, AUTOMATIC) GetEngineTemperature(void) {
    float temperature = 0.0;

    /* Gọi API RTE để lấy dữ liệu từ BSW */
    Std_ReturnType status = Rte_Read_EngineTemperatureSensor_EngineTemperature(&temperature);

    if (status == E_OK) {
        printf("GetEngineTemperature: Engine Temperature = %.2f°C\n", temperature);
    } else {
        printf("GetEngineTemperature: Failed to read Engine Temperature.\n");
    }
}

/******************************************************************************/  
/* Runnable: GetAirTemperature                                                */
/* Đọc giá trị nhiệt độ không khí từ RTE và truyền xuống BSW                 */  
/******************************************************************************/  
FUNC(void, AUTOMATIC) GetAirTemperature(void) {
    float airTemperature = 0.0;

    /* Gọi API RTE để lấy dữ liệu từ BSW */
    Std_ReturnType status = Rte_Read_EngineTemperatureSensor_AirTemperature(&airTemperature);

    if (status == E_OK) {
        printf("GetAirTemperature: Air Temperature = %.2f°C\n", airTemperature);
    } else {
        printf("GetAirTemperature: Failed to read Air Temperature.\n");
    }
}
