#include "webserver_base.h"
#include "ota_handler.h"
#include "esp_log.h"
#include "esp_http_server.h"
#include <string.h>

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

// OTA 触发接口
static esp_err_t ota_handler(httpd_req_t *req) {
    ESP_LOGI(TAG, "OTA handler called");

    const char *manifest_url = "https://192.168.4.2:8000/firmware/manifest.json";  // 替换为实际manifest url地址
    ota_start(manifest_url);

    httpd_resp_send(req, "OTA started", HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

// OTA 状态查询接口
static esp_err_t ota_status_handler(httpd_req_t *req) {
    ESP_LOGI(TAG, "OTA status handler called");

    int result = ota_get_result();
    char resp[64];
    snprintf(resp, sizeof(resp), "{\"result\": %d}", result);

    httpd_resp_set_type(req, "application/json");
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

// Generic static file handler for CSS, JS, and assets
static esp_err_t static_file_handler(httpd_req_t *req) {
    char filepath[128];
    snprintf(filepath, sizeof(filepath), "/spiffs%s", req->uri);
    
    ESP_LOGI(TAG, "Static file request: %s", filepath);

    FILE *f = fopen(filepath, "r");
    if (!f) {
        ESP_LOGE(TAG, "Failed to open file: %s", filepath);
        httpd_resp_send_404(req);
        return ESP_FAIL;
    }

    // Set content type based on file extension
    const char *ext = strrchr(req->uri, '.');
    if (ext != NULL) {
        if (strcmp(ext, ".css") == 0) {
            httpd_resp_set_type(req, "text/css");
        } else if (strcmp(ext, ".js") == 0) {
            httpd_resp_set_type(req, "application/javascript");
        } else if (strcmp(ext, ".json") == 0) {
            httpd_resp_set_type(req, "application/json");
        } else if (strcmp(ext, ".png") == 0) {
            httpd_resp_set_type(req, "image/png");
        } else if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0) {
            httpd_resp_set_type(req, "image/jpeg");
        } else if (strcmp(ext, ".svg") == 0) {
            httpd_resp_set_type(req, "image/svg+xml");
        } else if (strcmp(ext, ".ico") == 0) {
            httpd_resp_set_type(req, "image/x-icon");
        } else if (strcmp(ext, ".html") == 0) {
            httpd_resp_set_type(req, "text/html");
        } else {
            httpd_resp_set_type(req, "application/octet-stream");
        }
    }

    char buf[1024];
    size_t read_bytes;
    
    while ((read_bytes = fread(buf, 1, sizeof(buf), f)) > 0) {
        if (httpd_resp_send_chunk(req, buf, read_bytes) != ESP_OK) {
            fclose(f);
            ESP_LOGE(TAG, "Failed to send file chunk");
            return ESP_FAIL;
        }
    }
    
    fclose(f);
    httpd_resp_send_chunk(req, NULL, 0);  // End response
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

    httpd_uri_t ota_status_uri = {
        .uri      = "/ota/status",
        .method   = HTTP_GET,
        .handler  = ota_status_handler,
        .user_ctx = NULL
    };

    // Static file handlers
    httpd_uri_t css_uri = {
        .uri      = "/css/*",
        .method   = HTTP_GET,
        .handler  = static_file_handler,
        .user_ctx = NULL
    };

    httpd_uri_t js_uri = {
        .uri      = "/js/*",
        .method   = HTTP_GET,
        .handler  = static_file_handler,
        .user_ctx = NULL
    };

    httpd_uri_t assets_uri = {
        .uri      = "/assets/*",
        .method   = HTTP_GET,
        .handler  = static_file_handler,
        .user_ctx = NULL
    };

    httpd_uri_t manifest_uri = {
        .uri      = "/manifest.json",
        .method   = HTTP_GET,
        .handler  = static_file_handler,
        .user_ctx = NULL
    };

    httpd_uri_t index_html_uri = {
        .uri      = "/index.html",
        .method   = HTTP_GET,
        .handler  = static_file_handler,
        .user_ctx = NULL
    };

    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &toggle_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &favicon_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &index_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &ota_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &ota_status_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &css_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &js_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &assets_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &manifest_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &index_html_uri));
    ESP_LOGI(TAG, "Base URIs registered");
    return ESP_OK;
}
