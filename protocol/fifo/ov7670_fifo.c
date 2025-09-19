#include "ov7670_fifo.h"
#include "ov7670_gpio.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// 初始化 FIFO 控制引脚（RRST, RCLK）
void fifo_init(void) {
    gpio_config_t fifo_ctrl_conf = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = (1ULL << OV7670_RRST) | (1ULL << OV7670_RCLK),
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&fifo_ctrl_conf);

    gpio_set_level(OV7670_RRST, 1);
    gpio_set_level(OV7670_RCLK, 0);
}

// 复位 FIFO 读指针
void fifo_reset_read_pointer(void) {
    gpio_set_level(OV7670_RCLK, 0);
    gpio_set_level(OV7670_RRST, 0);
    vTaskDelay(pdMS_TO_TICKS(1));
    gpio_set_level(OV7670_RCLK, 1);
    vTaskDelay(pdMS_TO_TICKS(1));
    gpio_set_level(OV7670_RRST, 1);
    vTaskDelay(pdMS_TO_TICKS(1));
}

// 读取一个字节（D0–D7）
uint8_t fifo_read_byte(void) {
    gpio_set_level(OV7670_RCLK, 0);
    vTaskDelay(pdMS_TO_TICKS(1));  // 可根据时序要求调整
    gpio_set_level(OV7670_RCLK, 1);

    uint8_t value = 0;
    for (int i = 0; i < OV7670_DATA_GPIO_NUM; i++) {
        value |= (gpio_get_level(ov7670_data_pins[i]) << i);
    }
    return value;
}

// 读取一帧图像（用户需提供缓冲区）
void fifo_read_frame(uint8_t *buffer, size_t size) {
    fifo_reset_read_pointer();
    for (size_t i = 0; i < size; i++) {
        buffer[i] = fifo_read_byte();
    }
}
