#include "camera.h"
#include "global_gpio.h"
#include "sccb.h"
#include "ov7670_config.h"
#include "esp_log.h"
#include "freertos/task.h"
#include "camera_reg.h"


static const char *TAG = "camera";

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
    { REG_SCALING_DSP, 0x03 },
    { REG_HSTART, 0x16 },
    { REG_HSTOP, 0x04 },
    { REG_HREF, 0x24 },
    { REG_VSTART, 0x02 },
    { REG_VSTOP, 0x7A },
    { REG_VREF, 0x0A },
};

void ov7670_init_qvga_rgb565() {
    for (int i = 0; i < sizeof(ov7670_qvga_rgb565)/sizeof(ov7670_qvga_rgb565[0]); i++) {
        write_register(ov7670_qvga_rgb565[i].reg, ov7670_qvga_rgb565[i].val);
    }
}


bool camera_init(void) {
    ESP_LOGI(TAG, "Initializing camera sensor...");

    global_gpio_init();  // Initialize all GPIOs
    sccb_init();         // Initialize SCCB communication

    if (!ov7670_config()) {
        ESP_LOGE(TAG, "Failed to configure OV7670 registers");
        return false;
    }

    // Optional: check VSYNC signal
    if (gpio_get_level(GPIO_VSYNC) == 0) {
        ESP_LOGW(TAG, "VSYNC signal not detected");
    }

    ESP_LOGI(TAG, "Camera sensor initialization complete.");
    return true;
}
