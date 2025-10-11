#include "webserver_stream.h"
#include "ov7670_handler.h"
#include "esp_log.h"
#include <string.h>
#include <unistd.h>

static const char *TAG = "webserver_stream";
static bool stream_active = false;

static esp_err_t start_handler(httpd_req_t *req) {
    stream_active = true;
    ESP_LOGI(TAG, "Stream started");
    httpd_resp_send(req, "Stream started", HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

static esp_err_t stop_handler(httpd_req_t *req) {
    stream_active = false;
    ESP_LOGI(TAG, "Stream stopped");
    httpd_resp_send(req, "Stream stopped", HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

static esp_err_t stream_handler(httpd_req_t *req) {
    if (!stream_active) {
        httpd_resp_send_404(req);
        return ESP_FAIL;
    }

    httpd_resp_set_type(req, "multipart/x-mixed-replace; boundary=frame");

    while (stream_active) {
        uint8_t *jpeg_data = NULL;
        size_t jpeg_size = 0;

        if (ov7670_handler_get_jpeg(&jpeg_data, &jpeg_size) != ESP_OK || !jpeg_data) {
            ESP_LOGE(TAG, "Failed to get JPEG frame");
            break;
        }

        char header[128];
        int header_len = snprintf(header, sizeof(header),
                                  "--frame\r\nContent-Type: image/jpeg\r\nContent-Length: %d\r\n\r\n",
                                  (int)jpeg_size);

        if (httpd_resp_send_chunk(req, header, header_len) != ESP_OK ||
            httpd_resp_send_chunk(req, (const char *)jpeg_data, jpeg_size) != ESP_OK ||
            httpd_resp_send_chunk(req, "\r\n", 2) != ESP_OK) {
            ESP_LOGE(TAG, "Failed to send MJPEG chunk");
            free(jpeg_data);
            break;
        }

        free(jpeg_data);
        usleep(100000); // ~10 fps
    }

    httpd_resp_send_chunk(req, NULL, 0);
    return ESP_OK;
}

esp_err_t webserver_stream_register_handlers(httpd_handle_t server) {
    httpd_uri_t start_uri = {
        .uri = "/start",
        .method = HTTP_GET,
        .handler = start_handler,
        .user_ctx = NULL
    };

    httpd_uri_t stop_uri = {
        .uri = "/stop",
        .method = HTTP_GET,
        .handler = stop_handler,
        .user_ctx = NULL
    };

    httpd_uri_t stream_uri = {
        .uri = "/stream",
        .method = HTTP_GET,
        .handler = stream_handler,
        .user_ctx = NULL
    };

    httpd_register_uri_handler(server, &start_uri);
    httpd_register_uri_handler(server, &stop_uri);
    httpd_register_uri_handler(server, &stream_uri);

    ESP_LOGI(TAG, "Stream handlers registered");
    return ESP_OK;
}
