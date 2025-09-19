#include "esp_http_server.h"
#include "stream_control.h"
#include "ov7670_fifo.h"

static esp_err_t toggle_handler(httpd_req_t *req) {
    char buf[8];
    int ret = httpd_req_recv(req, buf, sizeof(buf));
    if (ret <= 0) {
        httpd_resp_send_500(req);
        return ESP_FAIL;
    }

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

    uint8_t frame_buffer[640 * 480];  // 示例：灰度图像
    fifo_read_frame(frame_buffer, sizeof(frame_buffer));

    httpd_resp_set_type(req, "application/octet-stream");
    httpd_resp_send(req, (const char *)frame_buffer, sizeof(frame_buffer));
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
    }

    return server;
}
//
//static esp_err_t index_handler(httpd_req_t *req) {
//    FILE *f = fopen("/spiffs/index.html", "r");
//    if (!f) {
//        httpd_resp_send_404(req);
//        return ESP_FAIL;
//    }
//
//    char buf[1024];
//    size_t read_bytes;
//    httpd_resp_set_type(req, "text/html");
//
//    while ((read_bytes = fread(buf, 1, sizeof(buf), f)) > 0) {
//        httpd_resp_send_chunk(req, buf, read_bytes);
//    }
//    fclose(f);
//    httpd_resp_send_chunk(req, NULL, 0);  // 结束响应
//    return ESP_OK;
//}

void register_static_handlers(httpd_handle_t server) {
    httpd_uri_t index_uri = {
        .uri = "/",
        .method = HTTP_GET,
        .handler = image_handler
    };
    httpd_register_uri_handler(server, &index_uri);
}
