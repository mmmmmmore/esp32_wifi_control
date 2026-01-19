#include "common_gpio.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "driver/i2c.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_heap_caps.h"
#include <stdio.h>
#include <stdlib.h>

static const char *TAG = "common_gpio";

/*
// ======================= 摄像头 GPIO 初始化 =======================
void ov7670_gpio_init(void) {
    gpio_config_t io_conf = {
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
        .pin_bit_mask = 0
    };

    gpio_num_t ov7670_gpios[] = {
        //GPIO_SCL, GPIO_SDA,
        GPIO_D0, GPIO_D1, GPIO_D2, GPIO_D3, GPIO_D4, GPIO_D5, GPIO_D6, GPIO_D7,
        GPIO_VSYNC, GPIO_RCLK, GPIO_OE, GPIO_WRST, GPIO_RRST, GPIO_WEN
    };

    for (int i = 0; i < sizeof(ov7670_gpios)/sizeof(ov7670_gpios[0]); i++) {
        if (ov7670_gpios[i] >= GPIO_NUM_0 && ov7670_gpios[i] < GPIO_NUM_MAX) {
            io_conf.pin_bit_mask |= (1ULL << ov7670_gpios[i]);
        } else {
            ESP_LOGW(TAG, "Invalid OV7670 GPIO: %d", ov7670_gpios[i]);
        }
    }

    ESP_ERROR_CHECK(gpio_config(&io_conf));
    ESP_LOGI(TAG, "OV7670 GPIOs initialized");
}
*/


// ======================= 电机 GPIO 初始化 =======================
// Note: Motor GPIO and PWM initialization is now handled by motor_handler component
// This function is kept for backward compatibility but does minimal work
void motor_gpio_init(void) {
    ESP_LOGI(TAG, "Motor GPIO initialization delegated to motor_handler component");
    // Motor handler will initialize all motor pins and PWM channels
}

// ======================= 其他 GPIO 初始化 =======================
/*
void misc_gpio_init(void) {
    gpio_config_t io_conf = {
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
        .pin_bit_mask = 0
    };

    gpio_num_t misc_gpios[] = {
        GPIO_LED_STATUS,
        GPIO_WEBSERVER_CTRL
    };

    for (int i = 0; i < sizeof(misc_gpios)/sizeof(misc_gpios[0]); i++) {
        if (misc_gpios[i] >= GPIO_NUM_0 && misc_gpios[i] < GPIO_NUM_MAX) {
            io_conf.pin_bit_mask |= (1ULL << misc_gpios[i]);
        } else {
            ESP_LOGW(TAG, "Invalid Misc GPIO: %d", misc_gpios[i]);
        }
    }

    ESP_ERROR_CHECK(gpio_config(&io_conf));
    ESP_LOGI(TAG, "Misc GPIOs initialized");
}
*/


// ======================= 总入口函数 =======================
void common_gpio_init(void) {
    ESP_LOGI(TAG, "Starting GPIO initialization...");
    //ov7670_gpio_init();
    motor_gpio_init();
    //misc_gpio_init();
    ESP_LOGI(TAG, "All GPIOs initialized");
}

// ======================= LEDC 初始化 =======================
// Note: LEDC/PWM initialization for motors is now handled by motor_handler
// This function is kept for other potential LEDC uses
void ledc_init(void) {
    ESP_LOGI(TAG, "LEDC initialization for motors is handled by motor_handler");
    // Motor PWM channels are configured in motor_handler_init()
}


// ======================= I2C 初始化 =======================
// Note: I2C driver is now managed by esp32-camera component using the new I2C driver API
// The old driver (i2c_driver_install) conflicts with driver_ng used by the camera
// Camera will initialize I2C automatically
void i2c_master_init(void) {
    ESP_LOGI(TAG, "I2C initialization is handled by esp32-camera component");
    // Camera driver will set up I2C using the new driver API
}
