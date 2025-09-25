
#include "webserver.h"
#include "esp_http_server.h"
#include "ov7670_handler"
#include "jpeg.h"
#include "esp_log.h"
#include "esp_heap_caps.h"
#include <string.h>

#define STREAM_FRAME_INTERVAL_MS 100 // stream image flash time interval ms

static const char *TAG = "webserver";

static esp_err_t toggle_handler(httpd_req_t *req) {
    char buf[8] = {0};
    int ret = httpd_req_recv(req, buf, sizeof(buf) - 1);
    if (ret <= 0) {
        httpd_resp_send_500(req);
        return ESP_FAIL;
    }
    buf[ret] = '\0';
    ESP_LOGI(TAG, "Received toggle command: %s", buf);

    if (strncmp(buf, "ON", 2) == 0) {
        capture_control_set(true);
        httpd_resp_sendstr(req, "Capture ON");
    } else {
        capture_control_set(false);
        httpd_resp_sendstr(req, "Capture OFF");
    }
    return ESP_OK;
}

static esp_err_t image_handler(httpd_req_t *req) {
    if (!capture_control_get()) {
        httpd_resp_sendstr(req, "Capture disabled");
        return ESP_OK;
    }

    size_t width = 320;
    size_t height = 240;
    size_t frame_size = width * height * 2;

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

    httpd_resp_set_type(req, "image/jpeg");
    httpd_resp_send(req, (const char *)jpeg_buf, jpeg_size);
    free(jpeg_buf);

    return ESP_OK;
}

static esp_err_t stream_handler(httpd_req_t *req) {
    if (!capture_control_get()) {
        httpd_resp_sendstr(req, "Capture disabled");
        return ESP_OK;
    }

    const char *boundary = "frame";
    httpd_resp_set_type(req, "multipart/x-mixed-replace; boundary=frame");

    size_t width = 320;
    size_t height = 240;
    size_t frame_size = width * height * 2;

    while (capture_control_get()) {
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

        vTaskDelay(pdMS_TO_TICKS(STREAM_FRAME_INTERVAL_MS));  // ~10fps
    }

    httpd_resp_send_chunk(req, "--frame--\r\n", strlen("--frame--\r\n"));
    return ESP_OK;
}

httpd_handle_t start_webserver(void) {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;

    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_uri_t toggle_uri = {
            .uri = "/toggle",
            .method = HTTP_POST,
            .handler = toggle_handler
        };
        httpd_register_uri_handler(server, &toggle_uri);

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

    httpd_uri_t index_uri = {
    .uri = "/",
    .method = HTTP_GET,
    .handler = index_handler
    };
    httpd_register_uri_handler(server, &index_uri);

    
    return server;
}


static esp_err_t index_handler(httpd_req_t *req) {
    FILE *f = fopen("/spiffs/index.html", "r");
    if (!f) {
        httpd_resp_send_404(req);
        return ESP_FAIL;
    }

    char buf[1024];
    size_t read_bytes;
    httpd_resp_set_type(req, "text/html");

    while ((read_bytes = fread(buf, 1, sizeof(buf), f)) > 0) {
        httpd_resp_send_chunk(req, buf, read_bytes);
    }
    fclose(f);
    httpd_resp_send_chunk(req, NULL, 0);  // 结束响应
    return ESP_OK;
}




