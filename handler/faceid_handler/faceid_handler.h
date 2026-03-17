#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FACEID_HANDLER_MAX_IDS 5
#define FACEID_HANDLER_NAME_MAX_LEN 32
#define FACEID_HANDLER_MESSAGE_MAX_LEN 96

typedef enum {
    FACEID_MODE_IDLE = 0,
    FACEID_MODE_SETUP,
    FACEID_MODE_IDENTIFY,
} faceid_mode_t;

typedef struct {
    uint16_t id;
    char name[FACEID_HANDLER_NAME_MAX_LEN];
} faceid_entry_t;

typedef struct {
    bool success;
    bool matched;
    uint16_t id;
    float similarity;
    size_t detected_face_count;
    size_t enrolled_count;
    char name[FACEID_HANDLER_NAME_MAX_LEN];
    char message[FACEID_HANDLER_MESSAGE_MAX_LEN];
    faceid_mode_t mode;
} faceid_result_t;

esp_err_t faceid_handler_init(void);
bool faceid_handler_is_ready(void);

void faceid_handler_set_mode(faceid_mode_t mode);
faceid_mode_t faceid_handler_get_mode(void);

size_t faceid_handler_get_count(void);
esp_err_t faceid_handler_list(faceid_entry_t *entries, size_t max_entries, size_t *out_count);

esp_err_t faceid_handler_enroll_from_jpeg(const uint8_t *jpeg_data,
                                          size_t jpeg_size,
                                          const char *name,
                                          faceid_result_t *result);
esp_err_t faceid_handler_identify_from_jpeg(const uint8_t *jpeg_data,
                                            size_t jpeg_size,
                                            faceid_result_t *result);
esp_err_t faceid_handler_delete_last(faceid_result_t *result);
esp_err_t faceid_handler_clear_all(faceid_result_t *result);

const char *faceid_handler_mode_to_string(faceid_mode_t mode);

#ifdef __cplusplus
}
#endif