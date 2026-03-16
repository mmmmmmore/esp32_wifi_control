#include "ov7670_handler.h"
#include "camera.h"
#include "esp_log.h"
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

static const char *TAG = "ov7670_handler";

static SemaphoreHandle_t s_camera_mutex = NULL;
static portMUX_TYPE s_mutex_init_lock = portMUX_INITIALIZER_UNLOCKED;

esp_err_t ov7670_handler_get_jpeg(uint8_t **jpeg_data, size_t *jpeg_size) {
    if (!jpeg_data || !jpeg_size) {
        ESP_LOGE(TAG, "Invalid output parameters");
        return ESP_ERR_INVALID_ARG;
    }

    /* Thread-safe lazy mutex init */
    if (s_camera_mutex == NULL) {
        portENTER_CRITICAL(&s_mutex_init_lock);
        if (s_camera_mutex == NULL) {
            s_camera_mutex = xSemaphoreCreateMutex();
        }
        portEXIT_CRITICAL(&s_mutex_init_lock);
    }

    if (xSemaphoreTake(s_camera_mutex, pdMS_TO_TICKS(3000)) != pdTRUE) {
        ESP_LOGE(TAG, "Camera mutex timeout");
        return ESP_ERR_TIMEOUT;
    }

    esp_err_t ret = camera_capture_jpeg(jpeg_data, jpeg_size);
    if (ret != ESP_OK || !*jpeg_data || *jpeg_size == 0) {
        ESP_LOGE(TAG, "Failed to capture JPEG frame");
        ret = ESP_FAIL;
    } else {
        ESP_LOGI(TAG, "JPEG capture ok, size: %d bytes", (int)*jpeg_size);
    }

    xSemaphoreGive(s_camera_mutex);
    return ESP_OK;
}
