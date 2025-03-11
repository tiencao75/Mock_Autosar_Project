/***************************************************************************
 * @file    Adc.c
 * @brief   Định nghĩa các hàm điều khiển bộ ADC trong mô phỏng.
 * @details File này chứa định nghĩa của các hàm mô phỏng bộ ADC,
 *          bao gồm khởi tạo và đọc giá trị sau khi chuyển đổi.
 * @version 1.0
 * @date    2025-02-27
 * @author  Grok 3 (xAI)
 ***************************************************************************/

#include "Adc.h"
#include "Compiler.h"  // Thêm Compiler.h
#include <stdio.h>

/* Biến toàn cục mô phỏng */
STATIC VAR(uint16, ADC_VAR) simulated_engine_temp = 75; // Giá trị nhiệt độ ban đầu
STATIC VAR(uint8, ADC_VAR) is_initialized = 0;          // Trạng thái khởi tạo

/**************************************************************************
 * @brief   Hàm khởi tạo 1 kênh trong bộ ADC (mô phỏng).
 * @details Hàm này mô phỏng khởi tạo 1 kênh trong bộ ADC sử dụng các cài đặt từ
 *          con trỏ được truyền vào hàm.
 * @param   ConfigPtr Con trỏ chứa các cài đặt cấu hình ADC.
 * @return  void
 **************************************************************************/
FUNC(void, ADC_CODE) Adc_Init(
    P2CONST(Adc_ConfigType, ADC_CONST, AUTOMATIC) ConfigPtr
) {
    // if (ConfigPtr == NULL_PTR) {
    //     printf("Error: Null configuration pointer\n");
    //     return;
    // }

    if (ConfigPtr->isEnabled) {
        is_initialized = 1;
        // printf("ADC Simulated: Initialized with Channel %d, Sampling Time %d\n",
        //        ConfigPtr->Adc_Channel, ConfigPtr->Adc_SamplingTime);
    } else {
        is_initialized = 0;
        // printf("ADC Simulated: Initialization disabled\n");
    }
}

/**************************************************************************
 * @brief   Hàm đọc giá trị sau chuyển đổi ở 1 kênh trong bộ ADC (mô phỏng).
 * @details Hàm này mô phỏng đọc giá trị sau chuyển đổi 1 kênh trong bộ ADC
 *          và lưu vào con trỏ truyền vào hàm.
 * @param   Adc_Channel Số thứ tự kênh trong bộ ADC mà muốn đọc.
 * @param   Adc_Value Con trỏ chứa giá trị sau khi đọc.
 * @return  Std_ReturnType
 *          - E_OK: Thành công
 *          - E_NOT_OK: Lỗi khi con trỏ NULL hoặc không đọc được giá trị
 **************************************************************************/
FUNC(Std_ReturnType, ADC_CODE) Adc_ReadChannel(
    VAR(Adc_ChannelType, ADC_VAR) Adc_Channel,
    P2VAR(uint16, ADC_VAR, AUTOMATIC) Adc_Value
) {
    if (Adc_Value == NULL_PTR) {
        printf("Error: Null pointer for Adc_Value\n");
        return E_NOT_OK;
    }

    if (Adc_Channel != 0) {
        printf("Error: Invalid channel %d (only channel 0 supported in simulation)\n", Adc_Channel);
        return E_NOT_OK;
    }

    *Adc_Value = simulated_engine_temp;
    // printf("ADC Simulated: Read Channel %d, Value = %d\n", Adc_Channel, *Adc_Value);
    return E_OK;
}

/**************************************************************************
 * @brief   Hàm mô phỏng thay đổi giá trị nhiệt độ.
 * @details Hàm này cập nhật giá trị nhiệt độ mô phỏng cho mục đích kiểm tra.
 * @param   new_temp Giá trị nhiệt độ mới.
 * @return  void
 **************************************************************************/
FUNC(void, ADC_CODE) Adc_SimulateNewTemperature(
    VAR(uint16, ADC_VAR) new_temp
) {
    simulated_engine_temp = new_temp;
    printf("ADC Simulated: Temperature updated to %d°C\n", simulated_engine_temp);
}
