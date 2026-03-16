#include "webserver.h"

#include "ov7670_handler.h"
#include "object_detector.h"

#include "esp_err.h"
#include "esp_http_server.h"
#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#include "cJSON.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *TAG = "webserver";

static bool stream_active = false;
static detector_result_t s_last_detection;
static bool s_detection_valid = false;
static SemaphoreHandle_t s_detection_mutex = NULL;
static volatile bool s_stream_task_running = false;
static httpd_handle_t s_server = NULL;

#if CONFIG_HTTPD_WS_SUPPORT
static int s_ws_fd = -1;
#endif

static esp_err_t detector_update_from_frame(const uint8_t *jpeg_data, size_t jpeg_size)
{
    detector_result_t result;
    esp_err_t ret = object_detector_run(jpeg_data, jpeg_size, &result);
    if (ret != ESP_OK) {
        ESP_LOGW(TAG, "Detector run failed: %s", esp_err_to_name(ret));
        return ret;
    }

    s_last_detection = result;
    s_detection_valid = true;
    return ESP_OK;
}

static char *detector_result_to_json_string(const detector_result_t *result)
{
    if (!result) {
        return NULL;
    }

    cJSON *root = cJSON_CreateObject();
    if (!root) {
        return NULL;
    }

    cJSON_AddNumberToObject(root, "frame_id", result->frame_id);
    cJSON_AddNumberToObject(root, "timestamp_ms", result->timestamp_ms);
    cJSON_AddNumberToObject(root, "frame_width", result->frame_width);
    cJSON_AddNumberToObject(root, "frame_height", result->frame_height);
    cJSON_AddBoolToObject(root, "enabled", object_detector_is_enabled());
    cJSON_AddBoolToObject(root, "model_ready", object_detector_model_ready());
    cJSON_AddStringToObject(root, "model_source", object_detector_model_source());

    cJSON *boxes = cJSON_AddArrayToObject(root, "boxes");
    if (!boxes) {
        cJSON_Delete(root);
        return NULL;
    }

    for (size_t index = 0; index < result->box_count; ++index) {
        cJSON *box = cJSON_CreateObject();
        if (!box) {
            cJSON_Delete(root);
            return NULL;
        }

        cJSON_AddStringToObject(box, "label", result->boxes[index].label);
        cJSON_AddNumberToObject(box, "score", result->boxes[index].score);
        cJSON_AddNumberToObject(box, "x", result->boxes[index].x);
        cJSON_AddNumberToObject(box, "y", result->boxes[index].y);
        cJSON_AddNumberToObject(box, "w", result->boxes[index].w);
        cJSON_AddNumberToObject(box, "h", result->boxes[index].h);
        cJSON_AddItemToArray(boxes, box);
    }

    char *json_str = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    return json_str;
}

#if CONFIG_HTTPD_WS_SUPPORT
static esp_err_t detection_ws_handler(httpd_req_t *req)
{
    if (req->method == HTTP_GET) {
        s_ws_fd = httpd_req_to_sockfd(req);
        ESP_LOGI(TAG, "WebSocket connected, fd=%d", s_ws_fd);
        return ESP_OK;
    }

    httpd_ws_frame_t ws_pkt = {
        .type = HTTPD_WS_TYPE_TEXT,
        .payload = NULL,
        .len = 0,
    };

    esp_err_t ret = httpd_ws_recv_frame(req, &ws_pkt, 0);
    if (ret != ESP_OK) {
        return ret;
    }

    if (ws_pkt.len > 0) {
        uint8_t *buf = calloc(1, ws_pkt.len + 1);
        if (!buf) {
            return ESP_ERR_NO_MEM;
        }

        ws_pkt.payload = buf;
        ret = httpd_ws_recv_frame(req, &ws_pkt, ws_pkt.len);
        free(buf);

        if (ret != ESP_OK) {
            return ret;
        }
    }

    return ESP_OK;
}
#endif

esp_err_t webserver_push_detection(httpd_handle_t server)
{
    if (!server || !s_detection_valid) {
        return ESP_ERR_INVALID_STATE;
    }

#if CONFIG_HTTPD_WS_SUPPORT
    if (s_ws_fd < 0) {
        return ESP_ERR_NOT_FOUND;
    }

    detector_result_t local_result;
    if (s_detection_mutex == NULL ||
        xSemaphoreTake(s_detection_mutex, pdMS_TO_TICKS(500)) != pdTRUE) {
        return ESP_ERR_TIMEOUT;
    }
    local_result = s_last_detection;
    xSemaphoreGive(s_detection_mutex);

    char *json_str = detector_result_to_json_string(&local_result);
    if (!json_str) {
        return ESP_ERR_NO_MEM;
    }

    httpd_ws_frame_t frame = {
        .type = HTTPD_WS_TYPE_TEXT,
        .payload = (uint8_t *)json_str,
        .len = strlen(json_str),
    };

    esp_err_t ret = httpd_ws_send_frame_async(server, s_ws_fd, &frame);
    free(json_str);

    if (ret != ESP_OK) {
        ESP_LOGW(TAG, "WS send failed, disconnect fd=%d", s_ws_fd);
        s_ws_fd = -1;
    }

    return ret;
#else
    return ESP_ERR_NOT_SUPPORTED;
#endif
}

/* Background task that owns the MJPEG socket after async hand-off */
static void stream_task(void *pvParameters)
{
    httpd_req_t *req = (httpd_req_t *)pvParameters;

    httpd_resp_set_type(req, "multipart/x-mixed-replace; boundary=frame");
    ESP_LOGI(TAG, "stream_task started (CPU%d)", xPortGetCoreID());

    while (stream_active) {
        uint8_t *jpeg_data = NULL;
        size_t jpeg_size = 0;

        if (ov7670_handler_get_jpeg(&jpeg_data, &jpeg_size) != ESP_OK || !jpeg_data || jpeg_size == 0) {
            ESP_LOGE(TAG, "Failed to obtain JPEG frame");
            break;
        }

        char part_header[64];
        int header_len = snprintf(part_header,
                                  sizeof(part_header),
                                  "--frame\r\nContent-Type: image/jpeg\r\nContent-Length: %u\r\n\r\n",
                                  (unsigned int)jpeg_size);

        if (httpd_resp_send_chunk(req, part_header, header_len) != ESP_OK ||
            httpd_resp_send_chunk(req, (const char *)jpeg_data, jpeg_size) != ESP_OK ||
            httpd_resp_send_chunk(req, "\r\n", 2) != ESP_OK) {
            ESP_LOGW(TAG, "stream_task: client disconnected");
            free(jpeg_data);
            break;
        }

        free(jpeg_data);
        vTaskDelay(pdMS_TO_TICKS(100));
    }

    httpd_resp_send_chunk(req, "--frame--\r\n", strlen("--frame--\r\n"));
    ESP_LOGI(TAG, "stream_task ended");
    s_stream_task_running = false;
    httpd_req_async_handler_complete(req);
    vTaskDelete(NULL);
}

static esp_err_t stream_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "HTTP GET /stream");

    if (!stream_active) {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Stream not started");
        return ESP_FAIL;
    }

    if (s_stream_task_running) {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Stream already active");
        return ESP_FAIL;
    }

    httpd_req_t *async_req = NULL;
    if (httpd_req_async_handler_begin(req, &async_req) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to start async stream handler");
        return ESP_FAIL;
    }

    s_stream_task_running = true;
    if (xTaskCreatePinnedToCore(stream_task, "mjpeg_stream", 8192, async_req, 5, NULL, 1) != pdPASS) {
        ESP_LOGE(TAG, "Failed to create stream task");
        s_stream_task_running = false;
        httpd_req_async_handler_complete(async_req);
        return ESP_FAIL;
    }

    return ESP_OK;
}

static esp_err_t snapshot_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "HTTP GET /snapshot");

    uint8_t *jpeg_data = NULL;
    size_t jpeg_size = 0;

    if (ov7670_handler_get_jpeg(&jpeg_data, &jpeg_size) != ESP_OK || !jpeg_data || jpeg_size == 0) {
        ESP_LOGE(TAG, "Failed to get JPEG snapshot");
        httpd_resp_send_500(req);
        return ESP_FAIL;
    }

    httpd_resp_set_type(req, "image/jpeg");
    esp_err_t res = httpd_resp_send(req, (const char *)jpeg_data, (ssize_t)jpeg_size);
    free(jpeg_data);
    return res;
}

static esp_err_t detection_handler(httpd_req_t *req)
{
    if (!s_detection_valid) {
        cJSON *root = cJSON_CreateObject();
        if (!root) {
            httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "JSON create failed");
            return ESP_FAIL;
        }
        cJSON_AddBoolToObject(root, "enabled", object_detector_is_enabled());
        cJSON_AddBoolToObject(root, "model_ready", object_detector_model_ready());
        cJSON_AddStringToObject(root, "model_source", object_detector_model_source());
        cJSON_AddStringToObject(root, "message", "No detection result yet");
        cJSON_AddArrayToObject(root, "boxes");
        char *json = cJSON_PrintUnformatted(root);
        cJSON_Delete(root);
        if (!json) {
            httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "JSON encode failed");
            return ESP_FAIL;
        }
        httpd_resp_set_type(req, "application/json");
        esp_err_t ret_empty = httpd_resp_send(req, json, HTTPD_RESP_USE_STRLEN);
        free(json);
        return ret_empty;
    }

    detector_result_t local_result;
    if (s_detection_mutex == NULL ||
        xSemaphoreTake(s_detection_mutex, pdMS_TO_TICKS(500)) != pdTRUE) {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Detection busy");
        return ESP_FAIL;
    }
    local_result = s_last_detection;
    xSemaphoreGive(s_detection_mutex);

    char *json = detector_result_to_json_string(&local_result);
    if (!json) {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "JSON encode failed");
        return ESP_FAIL;
    }

    httpd_resp_set_type(req, "application/json");
    esp_err_t ret = httpd_resp_send(req, json, HTTPD_RESP_USE_STRLEN);
    free(json);
    return ret;
}

static esp_err_t detector_status_handler(httpd_req_t *req)
{
    cJSON *root = cJSON_CreateObject();
    if (!root) {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "JSON create failed");
        return ESP_FAIL;
    }

    cJSON_AddBoolToObject(root, "enabled", object_detector_is_enabled());
    cJSON_AddBoolToObject(root, "model_ready", object_detector_model_ready());
    cJSON_AddStringToObject(root, "model_source", object_detector_model_source());
    cJSON_AddBoolToObject(root, "has_result", s_detection_valid);
    cJSON_AddNumberToObject(root, "last_box_count", s_detection_valid ? s_last_detection.box_count : 0);

    char *json = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    if (!json) {
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "JSON encode failed");
        return ESP_FAIL;
    }

    httpd_resp_set_type(req, "application/json");
    esp_err_t ret = httpd_resp_send(req, json, HTTPD_RESP_USE_STRLEN);
    free(json);
    return ret;
}

static esp_err_t detector_toggle_handler(httpd_req_t *req)
{
    char query[64] = {0};
    if (httpd_req_get_url_query_str(req, query, sizeof(query)) == ESP_OK) {
        char value[16] = {0};
        if (httpd_query_key_value(query, "enable", value, sizeof(value)) == ESP_OK) {
            if (strcmp(value, "1") == 0 || strcmp(value, "true") == 0) {
                object_detector_set_enabled(true);
            } else if (strcmp(value, "0") == 0 || strcmp(value, "false") == 0) {
                object_detector_set_enabled(false);
            }
        }
    }

    char resp[64];
    snprintf(resp, sizeof(resp), "{\"enabled\":%s}", object_detector_is_enabled() ? "true" : "false");
    httpd_resp_set_type(req, "application/json");
    return httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
}

static esp_err_t start_handler(httpd_req_t *req)
{
    stream_active = true;
    ESP_LOGI(TAG, "Stream started");
    httpd_resp_send(req, "Stream started", HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

static esp_err_t stop_handler(httpd_req_t *req)
{
    stream_active = false;
    ESP_LOGI(TAG, "Stream stopped");
    httpd_resp_send(req, "Stream stopped", HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

static esp_err_t health_handler(httpd_req_t *req)
{
    static const char *resp = "ok";
    httpd_resp_set_type(req, "text/plain");
    return httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
}

/* Runs on CPU1: captures a frame and runs YOLO inference every ~2 seconds.
   Detection results are stored under s_detection_mutex so the httpd task
   (CPU0) can read them at any time without blocking the stream. */
static void detector_background_task(void *pvParameters)
{
    ESP_LOGI(TAG, "detector_background_task started (CPU%d)", xPortGetCoreID());

    while (1) {
        if (!object_detector_is_enabled() || !object_detector_model_ready()) {
            vTaskDelay(pdMS_TO_TICKS(1000));
            continue;
        }

        uint8_t *jpeg_data = NULL;
        size_t jpeg_size = 0;

        if (ov7670_handler_get_jpeg(&jpeg_data, &jpeg_size) == ESP_OK &&
            jpeg_data != NULL && jpeg_size > 0) {
            detector_result_t result;
            if (object_detector_run(jpeg_data, jpeg_size, &result) == ESP_OK) {
                if (s_detection_mutex &&
                    xSemaphoreTake(s_detection_mutex, pdMS_TO_TICKS(200)) == pdTRUE) {
                    s_last_detection = result;
                    s_detection_valid = true;
                    xSemaphoreGive(s_detection_mutex);
                }
                ESP_LOGI(TAG, "Detection complete: %d object(s)", result.box_count);
                if (s_server) {
                    webserver_push_detection(s_server);
                }
            }
        }

        if (jpeg_data) {
            free(jpeg_data);
        }

        /* 2 second cooldown between detection runs */
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

httpd_handle_t start_webserver(void)
{
    ESP_LOGI(TAG, "Starting webserver...");

    s_detection_mutex = xSemaphoreCreateMutex();
    if (!s_detection_mutex) {
        ESP_LOGE(TAG, "Failed to create detection mutex");
    }

    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.max_uri_handlers = 16;
    config.uri_match_fn = httpd_uri_match_wildcard;

    httpd_handle_t server = NULL;
    if (httpd_start(&server, &config) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to start webserver");
        return NULL;
    }

    s_server = server;

    httpd_uri_t health_uri = {
        .uri = "/",
        .method = HTTP_GET,
        .handler = health_handler,
        .user_ctx = NULL,
    };

    httpd_uri_t start_uri = {
        .uri = "/start",
        .method = HTTP_GET,
        .handler = start_handler,
        .user_ctx = NULL,
    };

    httpd_uri_t stop_uri = {
        .uri = "/stop",
        .method = HTTP_GET,
        .handler = stop_handler,
        .user_ctx = NULL,
    };

    httpd_uri_t stream_uri = {
        .uri = "/stream",
        .method = HTTP_GET,
        .handler = stream_handler,
        .user_ctx = NULL,
    };

    httpd_uri_t snapshot_uri = {
        .uri = "/snapshot",
        .method = HTTP_GET,
        .handler = snapshot_handler,
        .user_ctx = NULL,
    };

    httpd_uri_t detection_uri = {
        .uri = "/detection",
        .method = HTTP_GET,
        .handler = detection_handler,
        .user_ctx = NULL,
    };

    httpd_uri_t detector_toggle_uri = {
        .uri = "/detector",
        .method = HTTP_GET,
        .handler = detector_toggle_handler,
        .user_ctx = NULL,
    };

    httpd_uri_t detector_status_uri = {
        .uri = "/detector/status",
        .method = HTTP_GET,
        .handler = detector_status_handler,
        .user_ctx = NULL,
    };

#if CONFIG_HTTPD_WS_SUPPORT
    httpd_uri_t detection_ws_uri = {
        .uri = "/ws/detection",
        .method = HTTP_GET,
        .handler = detection_ws_handler,
        .user_ctx = NULL,
        .is_websocket = true,
    };
#endif

    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &health_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &start_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &stop_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &stream_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &snapshot_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &detection_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &detector_toggle_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &detector_status_uri));

#if CONFIG_HTTPD_WS_SUPPORT
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &detection_ws_uri));
#endif

    ESP_LOGI(TAG, "Webserver ready");

    /* Start background inference task on CPU1 (httpd runs on CPU0) */
    xTaskCreatePinnedToCore(detector_background_task, "detector_bg",
                            8192, NULL, 3, NULL, 1);

    return server;
}
