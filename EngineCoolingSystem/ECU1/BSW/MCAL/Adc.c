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
#include <stdio.h>
#include <stdint.h>

// Biến toàn cục mô phỏng dữ liệu nhiệt độ động cơ
static uint16_t simulated_engine_temp = 75; // Giá trị nhiệt độ ban đầu (độ C)
static uint8_t is_initialized = 0;         // Trạng thái khởi tạo

/**************************************************************************
 * @brief   Hàm khởi tạo 1 kênh trong bộ ADC (mô phỏng).
 * @details Hàm này mô phỏng khởi tạo 1 kênh trong bộ ADC sử dụng các cài đặt từ
 *          con trỏ được truyền vào hàm.
 * @param   ConfigPtr Con trỏ chứa các cài đặt cấu hình ADC.
 * @return  void
 **************************************************************************/
void Adc_Init(const Adc_ConfigType *ConfigPtr)
{
    if (ConfigPtr == NULL_PTR) {
        printf("Error: Null configuration pointer\n");
        return;
    }

    // Mô phỏng khởi tạo ADC (không cần phần cứng)
    if (ConfigPtr->isEnabled) {
        is_initialized = 1;
        printf("ADC Simulated: Initialized with Channel %d, Sampling Time %d\n",
               ConfigPtr->Adc_Channel, ConfigPtr->Adc_SamplingTime);
    } else {
        is_initialized = 0;
        printf("ADC Simulated: Initialization disabled\n");
    }
}

/**************************************************************************
 * @brief   Hàm đọc giá trị sau chuyển đổi ở 1 kênh trong bộ ADC (mô phỏng).
 * @details Hàm này mô phỏng đọc giá trị sau chuyển đổi 1 kênh trong bộ ADC
 *          và lưu vào con trỏ truyền vào hàm.
 *          Nếu con trỏ đầu vào là NULL, hàm sẽ trả về lỗi.
 * @param   Adc_Channel Số thứ tự kênh trong bộ ADC mà muốn đọc.
 * @param   Adc_Value Con trỏ chứa giá trị sau khi đọc.
 * @return  Std_ReturnType
 *          - E_OK: Thành công
 *          - E_NOT_OK: Lỗi khi con trỏ NULL hoặc không đọc được giá trị
 **************************************************************************/
Std_ReturnType Adc_ReadChannel(Adc_ChannelType Adc_Channel, uint16_t *Adc_Value)
{
    // Kiểm tra tham số truyền vào
    if (Adc_Value == NULL_PTR) {
        printf("Error: Null pointer for Adc_Value\n");
        return E_NOT_OK;
    }

    if (!is_initialized) {
        printf("Error: ADC not initialized\n");
        return E_NOT_OK;
    }

    if (Adc_Channel != 0) { // Giả định chỉ hỗ trợ kênh 0 cho mô phỏng
        printf("Error: Invalid channel %d (only channel 0 supported in simulation)\n", Adc_Channel);
        return E_NOT_OK;
    }

    // Mô phỏng đọc giá trị từ cảm biến (giả lập)
    *Adc_Value = simulated_engine_temp;
    printf("ADC Simulated: Read Channel %d, Value = %d\n", Adc_Channel, *Adc_Value);

    // Trả về OK nếu đọc thành công
    return E_OK;
}

// Hàm bổ sung để thay đổi giá trị mô phỏng (cho mục đích kiểm tra)
void Adc_SimulateNewTemperature(uint16_t new_temp) {
    simulated_engine_temp = new_temp;
    printf("ADC Simulated: Temperature updated to %d°C\n", simulated_engine_temp);
}

// Hàm main để kiểm tra (chỉ dùng khi compile riêng)
#ifdef TEST_ADC
int main(void) {
    Adc_ConfigType config = {0, 10, 1}; // Kênh 0, 10-bit, bật
    uint16_t temp;

    // Khởi tạo ADC
    Adc_Init(&config);

    // Đọc giá trị
    if (Adc_ReadChannel(0, &temp) == E_OK) {
        printf("Temperature read successfully: %d°C\n", temp);
    }

    // Thay đổi giá trị mô phỏng
    Adc_SimulateNewTemperature(85);
    if (Adc_ReadChannel(0, &temp) == E_OK) {
        printf("Updated Temperature: %d°C\n", temp);
    }

    // Kiểm tra lỗi (con trỏ NULL)
    if (Adc_ReadChannel(0, NULL_PTR) == E_NOT_OK) {
        printf("Error handling worked for NULL pointer\n");
    }

    return 0;
}
#endif