
#include "camera.h"
#include "common_gpio.h"
#include "sccb.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "camera_reg.h"
#include "driver/i2c.h"
#include "driver/gpio.h"

//#define I2C_MASTER_NUM I2C_NUM_0
//#define I2C_MASTER_FREQ_HZ 100000
//#define OV7670_I2C_ADDR 0x42  // OV7670 write address

static const char *TAG = "CAMERA";

// VSYNC debug task
void vsync_debug_task(void *arg) {
    gpio_set_direction(PIN_VSYNC, GPIO_MODE_INPUT);

    while (1) {
        int high_count = 0;
        int low_count = 0;

        for (int i = 0; i < 100; i++) {
            int level = gpio_get_level(PIN_VSYNC);
            if (level) high_count++;
            else low_count++;
            vTaskDelay(pdMS_TO_TICKS(1));
        }

        ESP_LOGI("VSYNC_DEBUG", "VSYNC GPIO%d: High=%d, Low=%d", PIN_VSYNC, high_count, low_count);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}


// OV7670 register configuration
const struct regval_list ov7670_qvga_rgb565[] = {
    { REG_COM7, 0x80 },
    { REG_CLKRC, 0x80 },
    { REG_COM11, 0x0A },
    { REG_COM7, 0x04 },
    { REG_RGB444, 0x00 },
    { REG_COM15, 0xD0 },
    { REG_COM1, 0x00 },
    { REG_COM9, 0x6A },
    { REG_COM3, 0x04 },
    { REG_COM14, 0x19 },
    { REG_SCALING_XSC, 0x3A },
    { REG_SCALING_YSC, 0x35 },
    { REG_SCALING_DCWCTR, 0x03 },
    { REG_HSTART, 0x16 },
    { REG_HSTOP, 0x04 },
    { REG_HREF, 0x24 },
    { REG_VSTART, 0x02 },
    { REG_VSTOP, 0x7A },
    { REG_VREF, 0x0A },
};

bool ov7670_config(void) {
    for (int i = 0; i < sizeof(ov7670_qvga_rgb565)/sizeof(ov7670_qvga_rgb565[0]); i++) {
        if (sccb_write_register(ov7670_qvga_rgb565[i].reg, ov7670_qvga_rgb565[i].val) != ESP_OK) {
            ESP_LOGE(TAG, "Failed to write register 0x%02X", ov7670_qvga_rgb565[i].reg);
            return false;
        }
    }
    return true;
}

bool camera_init(void) {
    ESP_LOGI(TAG, "Initializing camera sensor...");

    fifo_gpio_init();
    sccb_init();

    // Reset OV7670
    sccb_write_register(0x12, 0x80);
    vTaskDelay(pdMS_TO_TICKS(10));

    // Read COM10 register
    uint8_t com10 = 0;
    if (sccb_read_register(0x15, &com10) == ESP_OK) {
        ESP_LOGI(TAG, "COM10 = 0x%02X", com10);
    } else {
        ESP_LOGE(TAG, "Failed to read COM10 register");
    }

    // Start VSYNC debug task
    xTaskCreate(vsync_debug_task, "vsync_debug_task", 2048, NULL, 5, NULL);

    // Configure OV7670 registers
    if (!ov7670_config()) {
        ESP_LOGE(TAG, "Failed to configure OV7670 registers");
        return false;
    }

    // Sample VSYNC signal
    int high_count = 0, low_count = 0;
    for (int i = 0; i < 100; i++) {
        int level = gpio_get_level(PIN_VSYNC);
        if (level) high_count++;
        else low_count++;
        vTaskDelay(pdMS_TO_TICKS(1));
    }
    if (high_count == 0) {
        ESP_LOGW(TAG, "VSYNC signal not detected");
    } else {
        ESP_LOGI(TAG, "VSYNC signal detected");
    }

    ESP_LOGI(TAG, "Camera sensor initialization complete.");
    return true;
}
