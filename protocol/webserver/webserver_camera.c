#include "webserver_camera.h"
#include "esp_http_server.h"
#include "esp_log.h"
#include "esp_heap_caps.h"
#include "ov7670_handler.h"
#include "jpeg.h"
#include "capture_control.h"
#include <string.h>

#define STREAM_FRAME_INTERVAL_MS 100

static const char *TAG = "webserver_camera";

static esp_err_t image_handler(httpd_req_t *req) {
    ESP_LOGI(TAG, "HTTP GET /image");

    if (!capture_control_get()) {
        ESP_LOGW(TAG, "Capture is disabled");
        httpd_resp_sendstr(req, "Capture disabled");
        return ESP_OK;
    }

    size_t width = 320;
    size_t height = 240;
    size_t frame_size = width * height * 2;

    ESP_LOGI(TAG, "Allocating frame buffer (%d bytes)", frame_size);
    ESP_LOGI(TAG, "Free heap before alloc: %d", esp_get_free_heap_size());

    uint8_t *frame_buffer = heap_caps_malloc(frame_size, MALLOC_CAP_SPIRAM);
    if (!frame_buffer) {
        ESP_LOGE(TAG, "Failed to allocate frame buffer");
        httpd_resp_send_500(req);
        return ESP_FAIL;
    }

    fifo_read_frame(frame_buffer, frame_size);

    size_t jpeg_size = 0;
    uint8_t *jpeg_buf = jpeg_encode_rgb565(frame_buffer, frame_size, width, height, &jpeg_size);
    free(frame_buffer);

    if (!jpeg_buf || jpeg_size == 0) {
        ESP_LOGE(TAG, "JPEG encoding failed");
        httpd_resp_send_500(req);
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "JPEG encoded size: %d bytes", jpeg_size);
    httpd_resp_set_type(req, "image/jpeg");
    httpd_resp_send(req, (const char *)jpeg_buf, jpeg_size);
    free(jpeg_buf);

    return ESP_OK;
}

static esp_err_t stream_handler(httpd_req_t *req) {
    ESP_LOGI(TAG, "HTTP GET /stream");

    if (!capture_control_get()) {
        ESP_LOGW(TAG, "Capture is disabled");
        httpd_resp_sendstr(req, "Capture disabled");
        return ESP_OK;
    }

    const char *boundary = "frame";
    httpd_resp_set_type(req, "multipart/x-mixed-replace; boundary=frame");

    size_t width = 320;
    size_t height = 240;
    size_t frame_size = width * height * 2;

    while (capture_control_get()) {
        ESP_LOGI(TAG, "Allocating frame buffer for stream");
        ESP_LOGI(TAG, "Free heap before alloc: %d", esp_get_free_heap_size());

        uint8_t *frame_buffer = heap_caps_malloc(frame_size, MALLOC_CAP_SPIRAM);
        if (!frame_buffer) {
            ESP_LOGE(TAG, "Failed to allocate frame buffer");
            break;
        }

        fifo_read_frame(frame_buffer, frame_size);

        size_t jpeg_size = 0;
        uint8_t *jpeg_buf = jpeg_encode_rgb565(frame_buffer, frame_size, width, height, &jpeg_size);
        free(frame_buffer);

        if (!jpeg_buf || jpeg_size == 0) {
            ESP_LOGE(TAG, "JPEG encoding failed");
            break;
        }

        char part_header[128];
        int header_len = snprintf(part_header, sizeof(part_header),
            "--%s\r\nContent-Type: image/jpeg\r\nContent-Length: %d\r\n\r\n",
            boundary, (int)jpeg_size);

        httpd_resp_send_chunk(req, part_header, header_len);
        httpd_resp_send_chunk(req, (const char *)jpeg_buf, jpeg_size);
        httpd_resp_send_chunk(req, "\r\n", 2);

        free(jpeg_buf);

        vTaskDelay(pdMS_TO_TICKS(STREAM_FRAME_INTERVAL_MS));
    }

    httpd_resp_send_chunk(req, "--frame--\r\n", strlen("--frame--\r\n"));
    return ESP_OK;
}

void register_camera_routes(httpd_handle_t server) {
    httpd_uri_t image_uri = {
        .uri = "/image",
        .method = HTTP_GET,
        .handler = image_handler
    };
    httpd_register_uri_handler(server, &image_uri);

    httpd_uri_t stream_uri = {
        .uri = "/stream",
        .method = HTTP_GET,
        .handler = stream_handler
    };
    httpd_register_uri_handler(server, &stream_uri);
}
