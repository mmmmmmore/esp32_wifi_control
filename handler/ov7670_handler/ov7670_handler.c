#include "ov7670_handler.h"
#include "common_gpio.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "esp_rom_sys.h"
#include "esp_log.h"

static const char *TAG = "OV7670_HANDLER";

// 图像缓冲区（可根据尺寸动态分配）
static uint8_t* image_buffer = NULL;

void ov7670_handler_init(void) {
    // 可选：初始化 VSYNC 中断或采集任务
}

static void wait_for_vsync() {
    // 等待 VSYNC 上升沿
    while (gpio_get_level(PIN_VSYNC) == 0) {
        vTaskDelay(pdMS_TO_TICKS(1));
    }
    // 等待 VSYNC 下降沿
    while (gpio_get_level(PIN_VSYNC) == 1) {
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}

void fifo_capture_frame_start() {
    ESP_LOGI(TAG, "Resetting FIFO write pointer...");
    fifo_reset_write_pointer();  // WRST 复位

    ESP_LOGI(TAG, "Waiting for VSYNC to start frame...");
    wait_for_vsync();            // 等待第一帧开始

    ESP_LOGI(TAG, "Starting frame capture...");
    gpio_set_level(PIN_WEN, 1); // 开始写入

    wait_for_vsync();            // 等待帧结束

    ESP_LOGI(TAG, "Stopping frame capture...");
    gpio_set_level(PIN_WEN, 0); // 停止写入
}

static void fifo_reset_read_pointer() {
    ESP_LOGI(TAG, "Resetting FIFO read pointer...");
    gpio_set_level(PIN_RRST, 0);
    gpio_set_level(PIN_RCLK, 0);
    gpio_set_level(PIN_RCLK, 1);
    gpio_set_level(PIN_RRST, 1);
}

void fifo_reset_write_pointer() {
    ESP_LOGI(TAG, "Resetting FIFO write pointer...");
    gpio_set_level(PIN_WRST, 0);
    gpio_set_level(PIN_WEN, 0);
    esp_rom_delay_us(1);
    gpio_set_level(PIN_WRST, 1);
}

static void fifo_enable_output(bool enable) {
    ESP_LOGI(TAG, "%s FIFO output...", enable ? "Enabling" : "Disabling");
    gpio_set_level(PIN_OE, enable ? 0 : 1); // OE低电平使能
}

uint8_t fifo_read_byte() {
    gpio_set_level(PIN_RCLK, 0);
    esp_rom_delay_us(1); // 可调节
    uint8_t data = 0;
    data |= gpio_get_level(PIN_D0) << 0;
    data |= gpio_get_level(PIN_D1) << 1;
    data |= gpio_get_level(PIN_D2) << 2;
    data |= gpio_get_level(PIN_D3) << 3;
    data |= gpio_get_level(PIN_D4) << 4;
    data |= gpio_get_level(PIN_D5) << 5;
    data |= gpio_get_level(PIN_D6) << 6;
    data |= gpio_get_level(PIN_D7) << 7;
    gpio_set_level(PIN_RCLK, 1);
    return data;
}


uint8_t* ov7670_capture_frame(const image_size_t* size, size_t* out_len) {
    if (!size || size->width == 0 || size->height == 0) return NULL;

    size_t pixel_count = size->width * size->height;
    size_t buffer_size = pixel_count * 2; // RGB565 每像素2字节

    if (image_buffer) free(image_buffer);
    image_buffer = malloc(buffer_size);
    if (!image_buffer) {
        ESP_LOGE(TAG, "Failed to allocate image buffer");
        return NULL;
    }

    ESP_LOGI(TAG, "Capturing frame: %dx%d", size->width, size->height);
    fifo_capture_frame_start();     // 采集一帧图像
    fifo_reset_read_pointer();      // 准备读取
    fifo_enable_output(true);       // 启用输出

    // ✅ 添加调试代码：采样前10个字节
    ESP_LOGI(TAG, "Sampling first 10 bytes from FIFO...");
    for (int i = 0; i < 10; i++) {
        uint8_t byte = fifo_read_byte();
        ESP_LOGI(TAG, "Byte[%d] = 0x%02X", i, byte);
    }

    // ✅ 正式读取图像数据
    for (size_t i = 0; i < pixel_count; i++) {
        uint8_t high = fifo_read_byte();  // 高字节
        uint8_t low  = fifo_read_byte();  // 低字节
        image_buffer[i * 2]     = high;
        image_buffer[i * 2 + 1] = low;

        if (i == 0) {
            ESP_LOGI(TAG, "First pixel: high=0x%02X, low=0x%02X", high, low);
        }
    }

    fifo_enable_output(false);  // 关闭输出

    *out_len = buffer_size;
    ESP_LOGI(TAG, "Frame capture complete, size: %d bytes", buffer_size);
    return image_buffer;
}

void ov7670_read_frame(uint8_t *buffer, size_t size) {
    if (!buffer || size == 0) return;

    ESP_LOGI(TAG, "Reading raw frame of size: %d", size);
    fifo_reset_read_pointer();  // 准备读取
    fifo_enable_output(true);   // 启用输出

    for (size_t i = 0; i < size; i++) {
        buffer[i] = fifo_read_byte();
        if (i < 4) {
            ESP_LOGI(TAG, "Byte[%d] = 0x%02X", i, buffer[i]);
        }
    }

    fifo_enable_output(false);  // 关闭输出
    ESP_LOGI(TAG, "Raw frame read complete");
}

