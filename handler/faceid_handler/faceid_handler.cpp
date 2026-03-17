#include "faceid_handler.h"

#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <list>
#include <string>
#include <vector>

#include "cJSON.h"
#include "dl_image_jpeg.hpp"
#include "esp_check.h"
#include "esp_heap_caps.h"
#include "esp_log.h"
#include "esp_spiffs.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "human_face_detect.hpp"
#include "human_face_recognition.hpp"

namespace {

static const char *TAG = "faceid_handler";
static const char *kSpiffsBasePath = "/spiffs";
static const char *kSpiffsPartitionLabel = "spiffs";
static const char *kFaceDbPath = "/spiffs/face.db";
static const char *kFaceNamesPath = "/spiffs/face_names.json";
static constexpr float kFaceMatchThreshold = 0.90f;

static SemaphoreHandle_t s_face_mutex = nullptr;
static HumanFaceDetect *s_face_detector = nullptr;
static HumanFaceRecognizer *s_face_recognizer = nullptr;
static bool s_storage_ready = false;
static bool s_ready = false;
static faceid_mode_t s_mode = FACEID_MODE_IDLE;
static faceid_entry_t s_entries[FACEID_HANDLER_MAX_IDS];
static size_t s_entry_count = 0;

static void copy_string(char *dest, size_t dest_size, const char *src)
{
    if (!dest || dest_size == 0) {
        return;
    }

    if (!src) {
        dest[0] = '\0';
        return;
    }

    strlcpy(dest, src, dest_size);
}

static void reset_result(faceid_result_t *result)
{
    if (!result) {
        return;
    }

    memset(result, 0, sizeof(*result));
    result->mode = s_mode;
    result->enrolled_count = s_face_recognizer ? static_cast<size_t>(s_face_recognizer->get_num_feats()) : s_entry_count;
}

static esp_err_t ensure_mutex(void)
{
    if (s_face_mutex) {
        return ESP_OK;
    }

    s_face_mutex = xSemaphoreCreateMutex();
    return s_face_mutex ? ESP_OK : ESP_ERR_NO_MEM;
}

static esp_err_t ensure_storage_ready(void)
{
    if (s_storage_ready) {
        return ESP_OK;
    }

    esp_vfs_spiffs_conf_t conf = {
        .base_path = kSpiffsBasePath,
        .partition_label = kSpiffsPartitionLabel,
        .max_files = 8,
        .format_if_mount_failed = true,
    };

    esp_err_t ret = esp_vfs_spiffs_register(&conf);
    if (ret != ESP_OK && ret != ESP_ERR_INVALID_STATE) {
        ESP_LOGE(TAG, "Failed to mount SPIFFS: %s", esp_err_to_name(ret));
        return ret;
    }

    if (ret == ESP_ERR_INVALID_STATE) {
        ESP_LOGI(TAG, "SPIFFS already mounted");
    } else {
        size_t total = 0;
        size_t used = 0;
        esp_spiffs_info(kSpiffsPartitionLabel, &total, &used);
        ESP_LOGI(TAG, "SPIFFS mounted: total=%u used=%u", (unsigned int)total, (unsigned int)used);
    }

    s_storage_ready = true;
    return ESP_OK;
}

static void clear_entries(void)
{
    memset(s_entries, 0, sizeof(s_entries));
    s_entry_count = 0;
}

static int find_entry_index(uint16_t id)
{
    for (size_t index = 0; index < s_entry_count; ++index) {
        if (s_entries[index].id == id) {
            return static_cast<int>(index);
        }
    }

    return -1;
}

static bool name_exists(const char *name)
{
    if (!name || name[0] == '\0') {
        return false;
    }

    for (size_t index = 0; index < s_entry_count; ++index) {
        if (strncmp(s_entries[index].name, name, sizeof(s_entries[index].name)) == 0) {
            return true;
        }
    }

    return false;
}

static esp_err_t save_entries_to_storage(void)
{
    FILE *file = fopen(kFaceNamesPath, "wb");
    if (!file) {
        ESP_LOGE(TAG, "Failed to open face name database");
        return ESP_FAIL;
    }

    cJSON *root = cJSON_CreateArray();
    if (!root) {
        fclose(file);
        return ESP_ERR_NO_MEM;
    }

    for (size_t index = 0; index < s_entry_count; ++index) {
        cJSON *entry = cJSON_CreateObject();
        if (!entry) {
            cJSON_Delete(root);
            fclose(file);
            return ESP_ERR_NO_MEM;
        }

        cJSON_AddNumberToObject(entry, "id", s_entries[index].id);
        cJSON_AddStringToObject(entry, "name", s_entries[index].name);
        cJSON_AddItemToArray(root, entry);
    }

    char *json = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    if (!json) {
        fclose(file);
        return ESP_ERR_NO_MEM;
    }

    size_t written = fwrite(json, 1, strlen(json), file);
    free(json);
    fclose(file);
    return written > 0 || s_entry_count == 0 ? ESP_OK : ESP_FAIL;
}

static esp_err_t load_entries_from_storage(void)
{
    clear_entries();

    FILE *file = fopen(kFaceNamesPath, "rb");
    if (!file) {
        return ESP_OK;
    }

    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return ESP_FAIL;
    }

    long size = ftell(file);
    if (size < 0) {
        fclose(file);
        return ESP_FAIL;
    }

    rewind(file);
    std::string content;
    content.resize(static_cast<size_t>(size));
    if (size > 0) {
        size_t read = fread(content.data(), 1, static_cast<size_t>(size), file);
        if (read != static_cast<size_t>(size)) {
            fclose(file);
            return ESP_FAIL;
        }
    }
    fclose(file);

    if (content.empty()) {
        return ESP_OK;
    }

    cJSON *root = cJSON_ParseWithLength(content.c_str(), content.size());
    if (!root || !cJSON_IsArray(root)) {
        cJSON_Delete(root);
        return ESP_FAIL;
    }

    cJSON *entry = nullptr;
    cJSON_ArrayForEach(entry, root) {
        if (s_entry_count >= FACEID_HANDLER_MAX_IDS || !cJSON_IsObject(entry)) {
            continue;
        }

        cJSON *id_item = cJSON_GetObjectItem(entry, "id");
        cJSON *name_item = cJSON_GetObjectItem(entry, "name");
        if (!cJSON_IsNumber(id_item) || !cJSON_IsString(name_item) || !name_item->valuestring) {
            continue;
        }

        s_entries[s_entry_count].id = static_cast<uint16_t>(id_item->valuedouble);
        copy_string(s_entries[s_entry_count].name, sizeof(s_entries[s_entry_count].name), name_item->valuestring);
        ++s_entry_count;
    }

    cJSON_Delete(root);
    return ESP_OK;
}

static void make_default_name(uint16_t id, char *buffer, size_t buffer_size)
{
    if (!buffer || buffer_size == 0) {
        return;
    }

    snprintf(buffer, buffer_size, "face_%u", static_cast<unsigned int>(id));
}

static esp_err_t sync_entries_with_database(void)
{
    if (!s_face_recognizer) {
        return ESP_ERR_INVALID_STATE;
    }

    bool changed = false;
    size_t valid_count = static_cast<size_t>(s_face_recognizer->get_num_feats());

    while (s_entry_count > valid_count) {
        memset(&s_entries[s_entry_count - 1], 0, sizeof(s_entries[0]));
        --s_entry_count;
        changed = true;
    }

    for (size_t id = 1; id <= valid_count && s_entry_count < FACEID_HANDLER_MAX_IDS; ++id) {
        if (find_entry_index(static_cast<uint16_t>(id)) >= 0) {
            continue;
        }

        s_entries[s_entry_count].id = static_cast<uint16_t>(id);
        make_default_name(static_cast<uint16_t>(id), s_entries[s_entry_count].name, sizeof(s_entries[s_entry_count].name));
        ++s_entry_count;
        changed = true;
    }

    if (changed) {
        std::sort(s_entries, s_entries + s_entry_count, [](const faceid_entry_t &lhs, const faceid_entry_t &rhs) {
            return lhs.id < rhs.id;
        });
        return save_entries_to_storage();
    }

    return ESP_OK;
}

static const char *lookup_name(uint16_t id)
{
    int index = find_entry_index(id);
    return index >= 0 ? s_entries[index].name : nullptr;
}

static esp_err_t add_entry(uint16_t id, const char *name)
{
    int existing = find_entry_index(id);
    if (existing >= 0) {
        copy_string(s_entries[existing].name, sizeof(s_entries[existing].name), name);
    } else {
        if (s_entry_count >= FACEID_HANDLER_MAX_IDS) {
            return ESP_ERR_NO_MEM;
        }

        s_entries[s_entry_count].id = id;
        copy_string(s_entries[s_entry_count].name, sizeof(s_entries[s_entry_count].name), name);
        ++s_entry_count;

        std::sort(s_entries, s_entries + s_entry_count, [](const faceid_entry_t &lhs, const faceid_entry_t &rhs) {
            return lhs.id < rhs.id;
        });
    }

    return save_entries_to_storage();
}

static esp_err_t set_error(faceid_result_t *result, esp_err_t err, const char *message)
{
    reset_result(result);
    if (result) {
        copy_string(result->message, sizeof(result->message), message);
    }
    return err;
}

static esp_err_t decode_jpeg_to_rgb888(const uint8_t *jpeg_data, size_t jpeg_size, dl::image::img_t *img)
{
    if (!jpeg_data || jpeg_size == 0 || !img) {
        return ESP_ERR_INVALID_ARG;
    }

    dl::image::jpeg_img_t jpeg_src = {
        .data = (void *)jpeg_data,
        .data_len = jpeg_size,
    };

    *img = dl::image::sw_decode_jpeg(jpeg_src, dl::image::DL_IMAGE_PIX_TYPE_RGB888);
    return img->data ? ESP_OK : ESP_ERR_NO_MEM;
}

static std::list<dl::detect::result_t> *detect_faces(const dl::image::img_t &img)
{
    if (!s_face_detector) {
        return nullptr;
    }

    return &s_face_detector->run(img);
}

} // namespace

extern "C" esp_err_t faceid_handler_init(void)
{
    ESP_RETURN_ON_ERROR(ensure_mutex(), TAG, "Failed to create face mutex");

    if (xSemaphoreTake(s_face_mutex, pdMS_TO_TICKS(5000)) != pdTRUE) {
        return ESP_ERR_TIMEOUT;
    }

    if (s_ready) {
        xSemaphoreGive(s_face_mutex);
        return ESP_OK;
    }

    esp_err_t ret = ensure_storage_ready();
    if (ret != ESP_OK) {
        xSemaphoreGive(s_face_mutex);
        return ret;
    }

    ret = load_entries_from_storage();
    if (ret != ESP_OK) {
        ESP_LOGW(TAG, "Failed to load face names; recreating mapping later");
        clear_entries();
    }

    s_face_detector = new HumanFaceDetect();
    s_face_recognizer = new HumanFaceRecognizer(kFaceDbPath);
    if (!s_face_detector || !s_face_recognizer) {
        delete s_face_detector;
        delete s_face_recognizer;
        s_face_detector = nullptr;
        s_face_recognizer = nullptr;
        xSemaphoreGive(s_face_mutex);
        return ESP_ERR_NO_MEM;
    }

    ret = sync_entries_with_database();
    if (ret != ESP_OK) {
        ESP_LOGW(TAG, "Failed to sync face names with database: %s", esp_err_to_name(ret));
    }

    s_ready = true;
    ESP_LOGI(TAG, "Face ID ready with %u enrolled face(s)", (unsigned int)s_face_recognizer->get_num_feats());
    xSemaphoreGive(s_face_mutex);
    return ESP_OK;
}

extern "C" bool faceid_handler_is_ready(void)
{
    return s_ready;
}

extern "C" void faceid_handler_set_mode(faceid_mode_t mode)
{
    if (!s_face_mutex) {
        s_mode = mode;
        return;
    }

    if (xSemaphoreTake(s_face_mutex, pdMS_TO_TICKS(1000)) == pdTRUE) {
        s_mode = mode;
        xSemaphoreGive(s_face_mutex);
    }
}

extern "C" faceid_mode_t faceid_handler_get_mode(void)
{
    return s_mode;
}

extern "C" size_t faceid_handler_get_count(void)
{
    return s_face_recognizer ? static_cast<size_t>(s_face_recognizer->get_num_feats()) : s_entry_count;
}

extern "C" esp_err_t faceid_handler_list(faceid_entry_t *entries, size_t max_entries, size_t *out_count)
{
    if (!out_count) {
        return ESP_ERR_INVALID_ARG;
    }

    ESP_RETURN_ON_FALSE(s_face_mutex != nullptr, ESP_ERR_INVALID_STATE, TAG, "Face handler not initialized");
    if (xSemaphoreTake(s_face_mutex, pdMS_TO_TICKS(1000)) != pdTRUE) {
        return ESP_ERR_TIMEOUT;
    }

    *out_count = s_entry_count;
    size_t copy_count = std::min(s_entry_count, max_entries);
    for (size_t index = 0; index < copy_count; ++index) {
        entries[index] = s_entries[index];
    }

    xSemaphoreGive(s_face_mutex);
    return ESP_OK;
}

extern "C" esp_err_t faceid_handler_enroll_from_jpeg(const uint8_t *jpeg_data,
                                                       size_t jpeg_size,
                                                       const char *name,
                                                       faceid_result_t *result)
{
    ESP_RETURN_ON_FALSE(s_ready, ESP_ERR_INVALID_STATE, TAG, "Face handler not initialized");
    ESP_RETURN_ON_FALSE(name && name[0] != '\0', ESP_ERR_INVALID_ARG, TAG, "Face name required");

    if (xSemaphoreTake(s_face_mutex, pdMS_TO_TICKS(5000)) != pdTRUE) {
        return ESP_ERR_TIMEOUT;
    }

    if (s_mode != FACEID_MODE_SETUP) {
        esp_err_t err = set_error(result, ESP_ERR_INVALID_STATE, "Face mode is not setup");
        xSemaphoreGive(s_face_mutex);
        return err;
    }

    if (s_face_recognizer->get_num_feats() >= FACEID_HANDLER_MAX_IDS) {
        esp_err_t err = set_error(result, ESP_ERR_NO_MEM, "Face database is full");
        xSemaphoreGive(s_face_mutex);
        return err;
    }

    if (name_exists(name)) {
        esp_err_t err = set_error(result, ESP_ERR_INVALID_STATE, "Face name already exists");
        xSemaphoreGive(s_face_mutex);
        return err;
    }

    dl::image::img_t img = {};
    esp_err_t ret = decode_jpeg_to_rgb888(jpeg_data, jpeg_size, &img);
    if (ret != ESP_OK) {
        esp_err_t err = set_error(result, ret, "Failed to decode JPEG frame");
        xSemaphoreGive(s_face_mutex);
        return err;
    }

    std::list<dl::detect::result_t> *detections = detect_faces(img);
    size_t detected_face_count = detections ? detections->size() : 0;
    if (!detections || detected_face_count != 1) {
        if (img.data) {
            heap_caps_free(img.data);
        }
        reset_result(result);
        result->detected_face_count = detected_face_count;
        copy_string(result->message, sizeof(result->message), "Need exactly one face for enrollment");
        xSemaphoreGive(s_face_mutex);
        return ESP_OK;
    }

    ret = s_face_recognizer->enroll(img, *detections);
    if (img.data) {
        heap_caps_free(img.data);
    }

    reset_result(result);
    result->detected_face_count = detected_face_count;
    if (ret != ESP_OK) {
        copy_string(result->message, sizeof(result->message), "Face enrollment failed");
        xSemaphoreGive(s_face_mutex);
        return ret;
    }

    result->success = true;
    result->id = static_cast<uint16_t>(s_face_recognizer->get_num_feats());
    result->enrolled_count = static_cast<size_t>(s_face_recognizer->get_num_feats());
    copy_string(result->name, sizeof(result->name), name);
    copy_string(result->message, sizeof(result->message), "Face enrolled");

    ret = add_entry(result->id, name);
    xSemaphoreGive(s_face_mutex);
    return ret;
}

extern "C" esp_err_t faceid_handler_identify_from_jpeg(const uint8_t *jpeg_data,
                                                         size_t jpeg_size,
                                                         faceid_result_t *result)
{
    ESP_RETURN_ON_FALSE(s_ready, ESP_ERR_INVALID_STATE, TAG, "Face handler not initialized");

    if (xSemaphoreTake(s_face_mutex, pdMS_TO_TICKS(5000)) != pdTRUE) {
        return ESP_ERR_TIMEOUT;
    }

    if (s_mode != FACEID_MODE_IDENTIFY) {
        esp_err_t err = set_error(result, ESP_ERR_INVALID_STATE, "Face mode is not identify");
        xSemaphoreGive(s_face_mutex);
        return err;
    }

    if (s_face_recognizer->get_num_feats() == 0) {
        reset_result(result);
        copy_string(result->message, sizeof(result->message), "No enrolled faces");
        xSemaphoreGive(s_face_mutex);
        return ESP_OK;
    }

    dl::image::img_t img = {};
    esp_err_t ret = decode_jpeg_to_rgb888(jpeg_data, jpeg_size, &img);
    if (ret != ESP_OK) {
        esp_err_t err = set_error(result, ret, "Failed to decode JPEG frame");
        xSemaphoreGive(s_face_mutex);
        return err;
    }

    std::list<dl::detect::result_t> *detections = detect_faces(img);
    size_t detected_face_count = detections ? detections->size() : 0;
    reset_result(result);
    result->detected_face_count = detected_face_count;

    if (!detections || detected_face_count != 1) {
        if (img.data) {
            heap_caps_free(img.data);
        }
        copy_string(result->message, sizeof(result->message), "Need exactly one face for identification");
        xSemaphoreGive(s_face_mutex);
        return ESP_OK;
    }

    std::vector<dl::recognition::result_t> matches = s_face_recognizer->recognize(img, *detections);
    if (img.data) {
        heap_caps_free(img.data);
    }

    if (matches.empty() || matches[0].similarity < kFaceMatchThreshold) {
        result->matched = false;
        copy_string(result->name, sizeof(result->name), "unknown");
        copy_string(result->message, sizeof(result->message), "Face not recognized");
        xSemaphoreGive(s_face_mutex);
        return ESP_OK;
    }

    result->success = true;
    result->matched = true;
    result->id = matches[0].id;
    result->similarity = matches[0].similarity;

    const char *name = lookup_name(result->id);
    if (!name) {
        char fallback_name[FACEID_HANDLER_NAME_MAX_LEN];
        make_default_name(result->id, fallback_name, sizeof(fallback_name));
        copy_string(result->name, sizeof(result->name), fallback_name);
    } else {
        copy_string(result->name, sizeof(result->name), name);
    }
    copy_string(result->message, sizeof(result->message), "Face recognized");

    xSemaphoreGive(s_face_mutex);
    return ESP_OK;
}

extern "C" esp_err_t faceid_handler_delete_last(faceid_result_t *result)
{
    ESP_RETURN_ON_FALSE(s_ready, ESP_ERR_INVALID_STATE, TAG, "Face handler not initialized");

    if (xSemaphoreTake(s_face_mutex, pdMS_TO_TICKS(5000)) != pdTRUE) {
        return ESP_ERR_TIMEOUT;
    }

    reset_result(result);
    if (s_face_recognizer->get_num_feats() == 0) {
        copy_string(result->message, sizeof(result->message), "No faces to delete");
        xSemaphoreGive(s_face_mutex);
        return ESP_OK;
    }

    uint16_t deleted_id = static_cast<uint16_t>(s_face_recognizer->get_num_feats());
    esp_err_t ret = s_face_recognizer->delete_last_feat();
    if (ret != ESP_OK) {
        copy_string(result->message, sizeof(result->message), "Failed to delete face");
        xSemaphoreGive(s_face_mutex);
        return ret;
    }

    if (s_entry_count > 0) {
        int index = find_entry_index(deleted_id);
        if (index >= 0) {
            for (size_t move_index = static_cast<size_t>(index) + 1; move_index < s_entry_count; ++move_index) {
                s_entries[move_index - 1] = s_entries[move_index];
            }
            memset(&s_entries[s_entry_count - 1], 0, sizeof(s_entries[0]));
            --s_entry_count;
        }
    }

    ret = save_entries_to_storage();
    result->success = ret == ESP_OK;
    result->id = deleted_id;
    result->enrolled_count = static_cast<size_t>(s_face_recognizer->get_num_feats());
    copy_string(result->message, sizeof(result->message), "Last face deleted");
    xSemaphoreGive(s_face_mutex);
    return ret;
}

extern "C" esp_err_t faceid_handler_clear_all(faceid_result_t *result)
{
    ESP_RETURN_ON_FALSE(s_ready, ESP_ERR_INVALID_STATE, TAG, "Face handler not initialized");

    if (xSemaphoreTake(s_face_mutex, pdMS_TO_TICKS(5000)) != pdTRUE) {
        return ESP_ERR_TIMEOUT;
    }

    esp_err_t ret = s_face_recognizer->clear_all_feats();
    reset_result(result);
    if (ret != ESP_OK) {
        copy_string(result->message, sizeof(result->message), "Failed to clear face database");
        xSemaphoreGive(s_face_mutex);
        return ret;
    }

    clear_entries();
    ret = save_entries_to_storage();
    result->success = ret == ESP_OK;
    result->enrolled_count = 0;
    copy_string(result->message, sizeof(result->message), "All faces cleared");
    xSemaphoreGive(s_face_mutex);
    return ret;
}

extern "C" const char *faceid_handler_mode_to_string(faceid_mode_t mode)
{
    switch (mode) {
    case FACEID_MODE_SETUP:
        return "setup";
    case FACEID_MODE_IDENTIFY:
        return "identify";
    case FACEID_MODE_IDLE:
    default:
        return "idle";
    }
}