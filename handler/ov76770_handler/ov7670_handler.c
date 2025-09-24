#include "ov7670_handler.h"
#include "global_gpio.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdlib.h>
#include <string.h>

// 图像缓冲区（可根据尺寸动态分配）
static uint8_t* image_buffer = NULL;

void ov7670_handler_init(void) {
    // 可选：初始化 VSYNC 中断或采集任务
}

static void fifo_reset_read_pointer() {
    gpio_set_level(GPIO_RRST, 0);
    gpio_set_level(GPIO_RCLK, 0);
    gpio_set_level(GPIO_RCLK, 1);
    gpio_set_level(GPIO_RRST, 1);
}

static void fifo_enable_output(bool enable) {
    gpio_set_level(GPIO_OE, enable ? 0 : 1); // OE低电平使能
}

static uint8_t fifo_read_byte() {
    gpio_set_level(GPIO_RCLK, 0);
    ets_delay_us(1); // 可调节
    uint8_t data = 0;
    data |= gpio_get_level(GPIO_D0) << 0;
    data |= gpio_get_level(GPIO_D1) << 1;
    data |= gpio_get_level(GPIO_D2) << 2;
    data |= gpio_get_level(GPIO_D3) << 3;
    data |= gpio_get_level(GPIO_D4) << 4;
    data |= gpio_get_level(GPIO_D5) << 5;
    data |= gpio_get_level(GPIO_D6) << 6;
    data |= gpio_get_level(GPIO_D7) << 7;
    gpio_set_level(GPIO_RCLK, 1);
    return data;
}

uint8_t* ov7670_capture_frame(const image_size_t* size, size_t* out_len) {
    if (!size || size->width == 0 || size->height == 0) return NULL;

    size_t pixel_count = size->width * size->height;
    size_t buffer_size = pixel_count * 2; // 假设 RGB565，每像素2字节

    if (image_buffer) free(image_buffer);
    image_buffer = malloc(buffer_size);
    if (!image_buffer) return NULL;

    fifo_reset_read_pointer();
    fifo_enable_output(true);

    for (size_t i = 0; i < buffer_size; i++) {
        image_buffer[i] = fifo_read_byte();
    }

    fifo_enable_output(false);

    *out_len = buffer_size;
    return image_buffer;
}
