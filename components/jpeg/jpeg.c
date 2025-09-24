#include "jpeg.h"
#include "esp_new_jpeg.h"
#include "esp_log.h"
#include "esp_heap_caps.h"

#define TAG "jpeg_encoder"

static void rgb565_to_rgb888(uint8_t *src, uint8_t *dst, size_t pixel_count) {
    for (size_t i = 0; i < pixel_count; i++) {
        uint16_t pixel = ((uint16_t *)src)[i];
        dst[i * 3 + 0] = (pixel >> 11) << 3;       // R
        dst[i * 3 + 1] = ((pixel >> 5) & 0x3F) << 2; // G
        dst[i * 3 + 2] = (pixel & 0x1F) << 3;       // B
    }
}

esp_err_t encode_rgb565_to_jpeg(uint8_t *rgb565_buf, size_t width, size_t height,
                                 uint8_t **jpeg_buf_out, size_t *jpeg_size_out) {
    esp_err_t ret;

    size_t pixel_count = width * height;
    size_t rgb888_size = pixel_count * 3;

    uint8_t *rgb888_buf = heap_caps_malloc(rgb888_size, MALLOC_CAP_SPIRAM);
    if (!rgb888_buf) {
        ESP_LOGE(TAG, "Failed to allocate RGB888 buffer");
        return ESP_ERR_NO_MEM;
    }

    rgb565_to_rgb888(rgb565_buf, rgb888_buf, pixel_count);

    jpeg_encode_config_t cfg = {
        .width = width,
        .height = height,
        .src_type = JPEG_PIXEL_FORMAT_RGB888,
        .quality = 75,
        .subsampling = JPEG_SUBSAMPLE_420,
    };

    jpeg_encoder_handle_t encoder;
    jpeg_encoder_output_t output;

    ret = jpeg_new_encoder(&cfg, &encoder);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to create JPEG encoder");
        free(rgb888_buf);
        return ret;
    }

    ret = jpeg_encoder_process(encoder, rgb888_buf, &output);
    jpeg_del_encoder(encoder);
    free(rgb888_buf);

    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "JPEG encoding failed");
        return ret;
    }

    *jpeg_buf_out = output.buf;
    *jpeg_size_out = output.len;

    return ESP_OK;
}
