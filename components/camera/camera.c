#include "camera.h"
#include "common_gpio.h"
#include "esp_camera.h"
#include "img_converters.h"
#include "esp_log.h"
#include "esp_heap_caps.h"
#include <string.h>

static const char *TAG = "camera";

// Configure ESP32-S3-CAM with the requested pinout
static const camera_config_t camera_config = {
    .pin_pwdn = -1,
    .pin_reset = -1,
    .pin_xclk = CAM_PIN_XCLK,
    .pin_sccb_sda = CAM_PIN_SIOD,
    .pin_sccb_scl = CAM_PIN_SIOC,
    .pin_d7 = CAM_PIN_Y9,
    .pin_d6 = CAM_PIN_Y8,
    .pin_d5 = CAM_PIN_Y7,
    .pin_d4 = CAM_PIN_Y6,
    .pin_d3 = CAM_PIN_Y5,
    .pin_d2 = CAM_PIN_Y4,
    .pin_d1 = CAM_PIN_Y3,
    .pin_d0 = CAM_PIN_Y2,
    .pin_vsync = CAM_PIN_VSYNC,
    .pin_href = CAM_PIN_HREF,
    .pin_pclk = CAM_PIN_PCLK,
    .xclk_freq_hz = 20000000,
    .ledc_timer = LEDC_TIMER_1,
    .ledc_channel = LEDC_CHANNEL_1,
    .pixel_format = PIXFORMAT_JPEG,
    .frame_size = FRAMESIZE_QVGA,
    .jpeg_quality = 12,
    .fb_count = 2,
    .fb_location = CAMERA_FB_IN_PSRAM,
    .grab_mode = CAMERA_GRAB_WHEN_EMPTY
};

esp_err_t camera_init(void) {
    ESP_LOGI(TAG, "Initializing ESP32-S3-CAM driver...");
    esp_err_t ret = esp_camera_init(&camera_config);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "esp_camera_init failed: %s", esp_err_to_name(ret));
        return ret;
    }

    ESP_LOGI(TAG, "Camera initialized: %dx%d JPEG", CAMERA_FRAME_WIDTH, CAMERA_FRAME_HEIGHT);
    return ESP_OK;
}

esp_err_t camera_capture_jpeg(uint8_t **jpeg_data, size_t *jpeg_size) {
    if (!jpeg_data || !jpeg_size) {
        return ESP_ERR_INVALID_ARG;
    }

    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) {
        ESP_LOGE(TAG, "Failed to get frame buffer from camera");
        return ESP_FAIL;
    }

    esp_err_t ret = ESP_OK;
    uint8_t *out_buf = NULL;
    size_t out_len = 0;

    if (fb->format == PIXFORMAT_JPEG) {
        out_len = fb->len;
        out_buf = heap_caps_malloc(out_len, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
        if (!out_buf) {
            ESP_LOGE(TAG, "No memory for JPEG copy (%d bytes)", (int)out_len);
            ret = ESP_ERR_NO_MEM;
        } else {
            memcpy(out_buf, fb->buf, out_len);
        }
    } else {
        bool converted = frame2jpg(fb, 80, &out_buf, &out_len);
        if (!converted || !out_buf) {
            ESP_LOGE(TAG, "Failed to convert frame to JPEG");
            ret = ESP_FAIL;
        }
    }

    esp_camera_fb_return(fb);

    if (ret != ESP_OK) {
        if (out_buf) {
            free(out_buf);
        }
        return ret;
    }

    *jpeg_data = out_buf;
    *jpeg_size = out_len;
    return ESP_OK;
}

void camera_stop(void) {
    esp_camera_deinit();
    ESP_LOGI(TAG, "Camera driver deinitialized");
}
