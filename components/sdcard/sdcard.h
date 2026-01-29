#ifndef SDCARD_H
#define SDCARD_H

#include "esp_err.h"
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// SD card configuration
#define SDCARD_MAX_FILE_SIZE_MB    10
#define SDCARD_MAX_FILE_SIZE       (SDCARD_MAX_FILE_SIZE_MB * 1024 * 1024)
#define SDCARD_MAX_FILES           10
#define SDCARD_BASE_PATH           "/sdcard"
#define SDCARD_STREAM_FILE_PREFIX  "stream_"

/**
 * @brief Initialize SD card with SPI mode
 * 
 * @return esp_err_t ESP_OK on success
 */
esp_err_t sdcard_init(void);

/**
 * @brief Deinitialize and unmount SD card
 * 
 * @return esp_err_t ESP_OK on success
 */
esp_err_t sdcard_deinit(void);

/**
 * @brief Check if SD card is mounted
 * 
 * @return true if SD card is mounted
 */
bool sdcard_is_mounted(void);

/**
 * @brief Get SD card information
 * 
 * @param total_bytes Total size of SD card in bytes (can be NULL)
 * @param used_bytes Used space in bytes (can be NULL)
 * @return esp_err_t ESP_OK on success
 */
esp_err_t sdcard_get_info(uint64_t *total_bytes, uint64_t *used_bytes);

/**
 * @brief Start recording stream data to SD card
 * 
 * Automatically manages file rotation based on size limits
 * and maximum file count
 * 
 * @return esp_err_t ESP_OK on success
 */
esp_err_t sdcard_start_recording(void);

/**
 * @brief Stop recording stream data
 * 
 * @return esp_err_t ESP_OK on success
 */
esp_err_t sdcard_stop_recording(void);

/**
 * @brief Check if currently recording
 * 
 * @return true if recording is active
 */
bool sdcard_is_recording(void);

/**
 * @brief Write JPEG frame to current recording file
 * 
 * Automatically handles file rotation when size limit is reached
 * 
 * @param jpeg_data Pointer to JPEG data
 * @param jpeg_size Size of JPEG data in bytes
 * @return esp_err_t ESP_OK on success
 */
esp_err_t sdcard_write_frame(const uint8_t *jpeg_data, size_t jpeg_size);

/**
 * @brief Get current recording statistics
 * 
 * @param file_count Current number of files (can be NULL)
 * @param current_file_size Current file size in bytes (can be NULL)
 * @param total_recorded Total bytes recorded in this session (can be NULL)
 * @return esp_err_t ESP_OK on success
 */
esp_err_t sdcard_get_recording_stats(int *file_count, size_t *current_file_size, size_t *total_recorded);

/**
 * @brief Clean up old recording files (remove oldest files if exceeding limit)
 * 
 * @return esp_err_t ESP_OK on success
 */
esp_err_t sdcard_cleanup_old_files(void);

#ifdef __cplusplus
}
#endif

#endif // SDCARD_H
