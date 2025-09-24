#pragma once

#include "esp_err.h"
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t encode_rgb565_to_jpeg(uint8_t *rgb565_buf, size_t width, size_t height,
                                 uint8_t **jpeg_buf_out, size_t *jpeg_size_out);

#ifdef __cplusplus
}
#endif
