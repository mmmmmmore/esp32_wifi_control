#include "ov7670_handler.h"
#include "camera.h"
#include "esp_log.h"
#include <stdlib.h>

static const char *TAG = "ov7670_handler";

esp_err_t ov7670_handler_get_jpeg(uint8_t **jpeg_data, size_t *jpeg_size) {
    if (!jpeg_data || !jpeg_size) {
        ESP_LOGE(TAG, "Invalid output parameters");
        return ESP_ERR_INVALID_ARG;
    }

    ESP_LOGI(TAG, "Capturing JPEG frame from camera...");

    esp_err_t ret = camera_capture_jpeg(jpeg_data, jpeg_size);
    if (ret != ESP_OK || !*jpeg_data || *jpeg_size == 0) {
        ESP_LOGE(TAG, "Failed to capture JPEG frame");
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "JPEG capture successful, size: %d bytes", (int)*jpeg_size);
    return ESP_OK;
}
