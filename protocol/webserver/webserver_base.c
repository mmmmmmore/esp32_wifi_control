#include "webserver_base.h"
#include "ota_handler.h"
#include "esp_log.h"
#include "esp_http_server.h"

static const char *TAG = "webserver_base";

static esp_err_t toggle_handler(httpd_req_t *req) {
    ESP_LOGI(TAG, "Toggle handler called");
    const char *resp_str = "Toggle action received";
    httpd_resp_send(req, resp_str, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

static esp_err_t favicon_handler(httpd_req_t *req) {
    ESP_LOGI(TAG, "Favicon handler called");
    httpd_resp_set_type(req, "image/x-icon");
    httpd_resp_send(req, NULL, 0);  // Empty response
    return ESP_OK;
}


static esp_err_t index_handler(httpd_req_t *req) {
    ESP_LOGI(TAG, "HTTP GET /");

    FILE *f = fopen("/spiffs/index.html", "r");
    if (!f) {
        ESP_LOGE(TAG, "Failed to open index.html");
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

//add ota handler process

static esp_err_t ota_handler(httpd_req_t *req) {
    ESP_LOGI(TAG, "OTA handler called");

    const char *ota_url = "http://192.168.4.2/firmware.bin";  // 替换为实际地址
    ota_start(ota_url);

    httpd_resp_send(req, "OTA started", HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

esp_err_t webserver_base_register(httpd_handle_t server) {
    httpd_uri_t toggle_uri = {
        .uri      = "/toggle",
        .method   = HTTP_GET,
        .handler  = toggle_handler,
        .user_ctx = NULL
    };

    httpd_uri_t favicon_uri = {
        .uri      = "/favicon.ico",
        .method   = HTTP_GET,
        .handler  = favicon_handler,
        .user_ctx = NULL
    };

    httpd_uri_t index_uri = {
        .uri      = "/",
        .method   = HTTP_GET,
        .handler  = index_handler
        };

    httpd_uri_t ota_uri = {
        .uri      = "/ota",
        .method   = HTTP_GET,
        .handler  = ota_handler,
        .user_ctx = NULL
    };

    
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &toggle_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &favicon_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &index_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &ota_uri));  // 注册 OTA URI
    ESP_LOGI(TAG, "Base URIs registered");
    return ESP_OK;
}

