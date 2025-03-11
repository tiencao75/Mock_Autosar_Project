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
STATIC VAR(uint16, ADC_VAR) simulated_engine_temp = 0; // Giá trị nhiệt độ ban đầu
STATIC VAR(uint16, ADC_VAR) simulated_air_temp = 0;          // Trạng thái khởi tạo


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
    
    if (Adc_Channel == 0)
    {
        *Adc_Value = Adc_SimulateAirTemperature();
    }
    else if (Adc_Channel == 1)
    {
        *Adc_Value = Adc_SimulateEngineTemperature();
    }
    
    return E_OK;
}

/**************************************************************************
 * @brief   Hàm mô phỏng thay đổi giá trị nhiệt độ.
 * @details Hàm này cập nhật giá trị nhiệt độ mô phỏng cho mục đích kiểm tra.
 * @param   new_temp Giá trị nhiệt độ mới.
 * @return  void
 **************************************************************************/
FUNC(Std_ReturnType, ADC_CODE) Adc_SimulateEngineTemperature() {
    return simulated_engine_temp = MIN_ENGINE_TEMP + (rand() % (MAX_ENGINE_TEMP - MIN_ENGINE_TEMP + 1));
}

FUNC(Std_ReturnType, ADC_CODE) Adc_SimulateAirTemperature() {
    return simulated_air_temp = MIN_AIR_TEMP + (rand() % (MAX_AIR_TEMP - MIN_AIR_TEMP + 1));
}
