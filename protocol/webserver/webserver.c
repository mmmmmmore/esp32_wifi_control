#include "webserver.h"
#include "webserver_camera.h"
#include "webserver_control.h"
#include "esp_log.h"

static const char *TAG = "webserver";

static esp_err_t favicon_handler(httpd_req_t *req) {
    ESP_LOGI(TAG, "HTTP GET /favicon.ico");
    httpd_resp_set_type(req, "image/x-icon");
    httpd_resp_send(req, NULL, 0);  // 返回空内容
    return ESP_OK;
}


httpd_handle_t start_webserver(void) {
    ESP_LOGI(TAG, "Starting webserver...");
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;

    if (httpd_start(&server, &config) == ESP_OK) {
        ESP_LOGI(TAG, "Webserver started");

        httpd_uri_t favicon_uri = {
            .uri = "/favicon.ico",
            .method = HTTP_GET,
            .handler = favicon_handler
        };
        httpd_register_uri_handler(server, &favicon_uri);
        
        register_camera_routes(server);
        register_control_routes(server);
    } else {
        ESP_LOGE(TAG, "Failed to start webserver");
    }

    return server;
}

