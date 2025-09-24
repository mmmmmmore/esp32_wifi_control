#include "camera.h"
#include "global_gpio.h"
#include "sccb.h"
#include "ov7670_config.h"
#include "esp_log.h"
#include "freertos/task.h"

static const char *TAG = "camera";

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
