#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DETECTOR_MAX_BOXES 8

typedef struct {
    char label[24];
    float score;
    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;
} detector_box_t;

typedef struct {
    uint32_t frame_id;
    uint32_t timestamp_ms;
    uint16_t frame_width;
    uint16_t frame_height;
    size_t box_count;
    detector_box_t boxes[DETECTOR_MAX_BOXES];
} detector_result_t;

typedef struct {
    bool enabled;
    uint16_t input_width;
    uint16_t input_height;
    float score_threshold;
} detector_config_t;

esp_err_t object_detector_init(const detector_config_t *cfg);
esp_err_t object_detector_run(const uint8_t *jpeg_data, size_t jpeg_size, detector_result_t *result);
void object_detector_set_enabled(bool enabled);
bool object_detector_is_enabled(void);
bool object_detector_model_ready(void);
const char *object_detector_model_source(void);

#ifdef __cplusplus
}
#endif
