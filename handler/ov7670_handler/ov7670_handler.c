#include "ov7670_handler.h"
#include "camera.h"
#include "esp_log.h"
#include "esp_timer.h"
#include <stdlib.h>

static const char *TAG = "ov7670_handler";

// Throttle logging to once per second (frames are captured ~10 times/sec)
#define LOG_THROTTLE_US (1000000)  // 1 second in microseconds
static int64_t last_log_time = 0;

esp_err_t ov7670_handler_get_jpeg(uint8_t **jpeg_data, size_t *jpeg_size) {
    if (!jpeg_data || !jpeg_size) {
        ESP_LOGE(TAG, "Invalid output parameters");
        return ESP_ERR_INVALID_ARG;
    }

    esp_err_t ret = camera_capture_jpeg(jpeg_data, jpeg_size);
    if (ret != ESP_OK || !*jpeg_data || *jpeg_size == 0) {
        ESP_LOGE(TAG, "Failed to capture JPEG frame");
        return ESP_FAIL;
    }

    // Log only once per second to reduce log spam
    int64_t now = esp_timer_get_time();
    if (now - last_log_time >= LOG_THROTTLE_US) {
        ESP_LOGI(TAG, "JPEG capture: size %d bytes (throttled log ~1/sec)", (int)*jpeg_size);
        last_log_time = now;
    }

    return ESP_OK;
}
