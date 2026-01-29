#include "sdcard.h"
#include "common_gpio.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "driver/sdmmc_host.h"
#include "sdmmc_cmd.h"
#include "driver/gpio.h"
#include <string.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <dirent.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

static const char *TAG = "SD_CARD";

// SD card state
static sdmmc_card_t *s_card = NULL;
static bool s_card_mounted = false;
static SemaphoreHandle_t s_card_mutex = NULL;

// Recording state
static bool s_recording = false;
static FILE *s_current_file = NULL;
static int s_current_file_index = 0;
static size_t s_current_file_size = 0;
static size_t s_total_recorded = 0;
static int s_total_file_count = 0;

// Forward declarations
static esp_err_t create_new_recording_file(void);
static esp_err_t close_current_file(void);
static int count_stream_files(void);
static esp_err_t delete_oldest_file(void);

esp_err_t sdcard_init(void) {
    if (s_card_mounted) {
        ESP_LOGW(TAG, "SD card already mounted");
        return ESP_OK;
    }

    // Create mutex for thread-safe operations
    if (s_card_mutex == NULL) {
        s_card_mutex = xSemaphoreCreateMutex();
        if (s_card_mutex == NULL) {
            ESP_LOGE(TAG, "Failed to create mutex");
            return ESP_ERR_NO_MEM;
        }
    }

    ESP_LOGI(TAG, "Initializing SD card (1-bit SDMMC mode)");

    // SD card mount configuration
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files = 5,
        .allocation_unit_size = 16 * 1024
    };

    // SDMMC host configuration (1-bit mode)
    sdmmc_host_t host = SDMMC_HOST_DEFAULT();
    host.flags = SDMMC_HOST_FLAG_1BIT;  // Use 1-bit mode
    host.max_freq_khz = SDMMC_FREQ_PROBING; // Start with low frequency for detection

    // SDMMC slot configuration for 1-bit mode
    sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();
    slot_config.width = 1;              // 1-bit mode
    slot_config.clk = SDCARD_CLK;       // GPIO 39 - Clock
    slot_config.cmd = SDCARD_CMD;       // GPIO 38 - Command
    slot_config.d0 = SDCARD_DATA;       // GPIO 40 - Data0
    slot_config.d1 = GPIO_NUM_NC;       // Not used in 1-bit mode
    slot_config.d2 = GPIO_NUM_NC;       // Not used in 1-bit mode
    slot_config.d3 = GPIO_NUM_NC;       // Not used in 1-bit mode
    slot_config.d4 = GPIO_NUM_NC;
    slot_config.d5 = GPIO_NUM_NC;
    slot_config.d6 = GPIO_NUM_NC;
    slot_config.d7 = GPIO_NUM_NC;
    slot_config.cd = GPIO_NUM_NC;       // No card detect pin
    slot_config.wp = GPIO_NUM_NC;       // No write protect pin
    slot_config.flags = 0;

    // Mount the SD card using SDMMC interface
    esp_err_t ret = esp_vfs_fat_sdmmc_mount(SDCARD_BASE_PATH, &host, &slot_config, &mount_config, &s_card);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "Failed to mount filesystem. "
                     "If you want the card to be formatted, set format_if_mount_failed = true.");
        } else {
            ESP_LOGE(TAG, "Failed to initialize the card (%s). "
                     "Make sure SD card is inserted and pins are correctly connected.", 
                     esp_err_to_name(ret));
        }
        return ret;
    }

    s_card_mounted = true;

    // Print card info
    sdmmc_card_print_info(stdout, s_card);
    
    uint64_t total_bytes, used_bytes;
    if (sdcard_get_info(&total_bytes, &used_bytes) == ESP_OK) {
        ESP_LOGI(TAG, "SD card mounted successfully");
        ESP_LOGI(TAG, "Total: %llu MB, Used: %llu MB, Available: %llu MB",
                 total_bytes / (1024 * 1024),
                 used_bytes / (1024 * 1024),
                 (total_bytes - used_bytes) / (1024 * 1024));
    }

    return ESP_OK;
}

esp_err_t sdcard_deinit(void) {
    if (!s_card_mounted) {
        return ESP_OK;
    }

    // Stop any ongoing recording
    if (s_recording) {
        sdcard_stop_recording();
    }

    ESP_LOGI(TAG, "Unmounting SD card");
    
    // Unmount and free resources
    esp_err_t ret = esp_vfs_fat_sdcard_unmount(SDCARD_BASE_PATH, s_card);
    if (ret == ESP_OK) {
        s_card = NULL;
        s_card_mounted = false;
        
        ESP_LOGI(TAG, "SD card unmounted successfully");
    } else {
        ESP_LOGE(TAG, "Failed to unmount SD card: %s", esp_err_to_name(ret));
    }

    return ret;
}

bool sdcard_is_mounted(void) {
    return s_card_mounted;
}

esp_err_t sdcard_get_info(uint64_t *total_bytes, uint64_t *used_bytes) {
    if (!s_card_mounted) {
        return ESP_ERR_INVALID_STATE;
    }

    FATFS *fs;
    DWORD fre_clust;
    
    // Get volume information
    if (f_getfree("0:", &fre_clust, &fs) != FR_OK) {
        return ESP_FAIL;
    }

    // Calculate total and free space
    uint64_t total_sectors = (fs->n_fatent - 2) * fs->csize;
    uint64_t free_sectors = fre_clust * fs->csize;
    
    if (total_bytes) {
        *total_bytes = total_sectors * fs->ssize;
    }
    
    if (used_bytes) {
        *used_bytes = (total_sectors - free_sectors) * fs->ssize;
    }

    return ESP_OK;
}

static int count_stream_files(void) {
    if (!s_card_mounted) {
        return 0;
    }

    DIR *dir = opendir(SDCARD_BASE_PATH);
    if (!dir) {
        ESP_LOGE(TAG, "Failed to open directory");
        return 0;
    }

    int count = 0;
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strncmp(entry->d_name, SDCARD_STREAM_FILE_PREFIX, 
                    strlen(SDCARD_STREAM_FILE_PREFIX)) == 0) {
            count++;
        }
    }

    closedir(dir);
    return count;
}

static esp_err_t delete_oldest_file(void) {
    if (!s_card_mounted) {
        return ESP_ERR_INVALID_STATE;
    }

    DIR *dir = opendir(SDCARD_BASE_PATH);
    if (!dir) {
        return ESP_FAIL;
    }

    char oldest_file[256] = {0};
    time_t oldest_time = 0;
    bool found = false;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strncmp(entry->d_name, SDCARD_STREAM_FILE_PREFIX, 
                    strlen(SDCARD_STREAM_FILE_PREFIX)) == 0) {
            char filepath[300];
            snprintf(filepath, sizeof(filepath), "%s/%s", SDCARD_BASE_PATH, entry->d_name);
            
            struct stat st;
            if (stat(filepath, &st) == 0) {
                if (!found || st.st_mtime < oldest_time) {
                    oldest_time = st.st_mtime;
                    strncpy(oldest_file, filepath, sizeof(oldest_file) - 1);
                    found = true;
                }
            }
        }
    }

    closedir(dir);

    if (found) {
        ESP_LOGI(TAG, "Deleting oldest file: %s", oldest_file);
        if (unlink(oldest_file) == 0) {
            return ESP_OK;
        } else {
            ESP_LOGE(TAG, "Failed to delete file");
            return ESP_FAIL;
        }
    }

    return ESP_ERR_NOT_FOUND;
}

static esp_err_t create_new_recording_file(void) {
    if (!s_card_mounted) {
        ESP_LOGE(TAG, "SD card not mounted");
        return ESP_ERR_INVALID_STATE;
    }

    // Close current file if open
    if (s_current_file) {
        close_current_file();
    }

    // Check if we need to delete old files
    int file_count = count_stream_files();
    while (file_count >= SDCARD_MAX_FILES) {
        ESP_LOGW(TAG, "Max files reached, deleting oldest");
        if (delete_oldest_file() != ESP_OK) {
            break;
        }
        file_count--;
    }

    // Create new filename with timestamp
    char filename[300];
    snprintf(filename, sizeof(filename), "%s/%s%d_%lu.mjpeg",
             SDCARD_BASE_PATH, SDCARD_STREAM_FILE_PREFIX,
             s_current_file_index++, (unsigned long)time(NULL));

    ESP_LOGI(TAG, "Creating new recording file: %s", filename);

    s_current_file = fopen(filename, "wb");
    if (!s_current_file) {
        ESP_LOGE(TAG, "Failed to create file: %s", filename);
        return ESP_FAIL;
    }

    s_current_file_size = 0;
    s_total_file_count++;

    return ESP_OK;
}

static esp_err_t close_current_file(void) {
    if (s_current_file) {
        ESP_LOGI(TAG, "Closing recording file (size: %u bytes)", (unsigned int)s_current_file_size);
        fclose(s_current_file);
        s_current_file = NULL;
        s_current_file_size = 0;
    }
    return ESP_OK;
}

esp_err_t sdcard_start_recording(void) {
    if (!s_card_mounted) {
        ESP_LOGE(TAG, "Cannot start recording: SD card not mounted");
        return ESP_ERR_INVALID_STATE;
    }

    if (s_recording) {
        ESP_LOGW(TAG, "Recording already active");
        return ESP_OK;
    }

    if (xSemaphoreTake(s_card_mutex, pdMS_TO_TICKS(1000)) != pdTRUE) {
        return ESP_ERR_TIMEOUT;
    }

    s_recording = true;
    s_current_file_index = 0;
    s_total_recorded = 0;
    s_total_file_count = 0;

    esp_err_t ret = create_new_recording_file();
    
    xSemaphoreGive(s_card_mutex);

    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "Recording started");
    }

    return ret;
}

esp_err_t sdcard_stop_recording(void) {
    if (!s_recording) {
        return ESP_OK;
    }

    if (xSemaphoreTake(s_card_mutex, pdMS_TO_TICKS(1000)) != pdTRUE) {
        return ESP_ERR_TIMEOUT;
    }

    close_current_file();
    s_recording = false;

    ESP_LOGI(TAG, "Recording stopped. Total recorded: %u bytes in %d files",
             (unsigned int)s_total_recorded, s_total_file_count);

    xSemaphoreGive(s_card_mutex);

    return ESP_OK;
}

bool sdcard_is_recording(void) {
    return s_recording;
}

esp_err_t sdcard_write_frame(const uint8_t *jpeg_data, size_t jpeg_size) {
    if (!s_recording || !jpeg_data || jpeg_size == 0) {
        return ESP_ERR_INVALID_ARG;
    }

    if (xSemaphoreTake(s_card_mutex, pdMS_TO_TICKS(100)) != pdTRUE) {
        return ESP_ERR_TIMEOUT;
    }

    // Check if we need to create a new file
    if (!s_current_file || s_current_file_size >= SDCARD_MAX_FILE_SIZE) {
        if (create_new_recording_file() != ESP_OK) {
            xSemaphoreGive(s_card_mutex);
            return ESP_FAIL;
        }
    }

    // Write MJPEG frame header
    const char *frame_header = "--frame\r\nContent-Type: image/jpeg\r\n\r\n";
    size_t header_len = strlen(frame_header);
    
    size_t written = fwrite(frame_header, 1, header_len, s_current_file);
    if (written != header_len) {
        ESP_LOGE(TAG, "Failed to write frame header");
        xSemaphoreGive(s_card_mutex);
        return ESP_FAIL;
    }

    // Write JPEG data
    written = fwrite(jpeg_data, 1, jpeg_size, s_current_file);
    if (written != jpeg_size) {
        ESP_LOGE(TAG, "Failed to write JPEG data");
        xSemaphoreGive(s_card_mutex);
        return ESP_FAIL;
    }

    // Write frame footer
    const char *frame_footer = "\r\n";
    written = fwrite(frame_footer, 1, 2, s_current_file);
    if (written != 2) {
        ESP_LOGE(TAG, "Failed to write frame footer");
        xSemaphoreGive(s_card_mutex);
        return ESP_FAIL;
    }

    // Flush to ensure data is written
    fflush(s_current_file);

    s_current_file_size += (header_len + jpeg_size + 2);
    s_total_recorded += (header_len + jpeg_size + 2);

    xSemaphoreGive(s_card_mutex);

    return ESP_OK;
}

esp_err_t sdcard_get_recording_stats(int *file_count, size_t *current_file_size, size_t *total_recorded) {
    if (!s_recording) {
        return ESP_ERR_INVALID_STATE;
    }

    if (file_count) {
        *file_count = s_total_file_count;
    }

    if (current_file_size) {
        *current_file_size = s_current_file_size;
    }

    if (total_recorded) {
        *total_recorded = s_total_recorded;
    }

    return ESP_OK;
}

esp_err_t sdcard_cleanup_old_files(void) {
    if (!s_card_mounted) {
        return ESP_ERR_INVALID_STATE;
    }

    int file_count = count_stream_files();
    ESP_LOGI(TAG, "Found %d stream files", file_count);

    while (file_count > SDCARD_MAX_FILES) {
        if (delete_oldest_file() != ESP_OK) {
            break;
        }
        file_count--;
    }

    ESP_LOGI(TAG, "Cleanup complete. %d files remaining", file_count);
    return ESP_OK;
}
