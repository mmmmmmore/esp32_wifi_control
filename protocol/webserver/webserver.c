#include "webserver.h"
#include "webserver_camera.h"
#include "webserver_motor.h"
#include "esp_log.h"

static const char *TAG = "webserver";

static esp_err_t favicon_handler(httpd_req_t *req) {
    ESP_LOGI(TAG, "HTTP GET /favicon.ico");
    httpd_resp_set_type(req, "image/x-icon");
    httpd_resp_send(req, NULL, 0);  // 返回空内容
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

httpd_handle_t start_webserver(void) {
    ESP_LOGI(TAG, "Starting webserver...");
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;

    if (httpd_start(&server, &config) == ESP_OK) {
        ESP_LOGI(TAG, "Webserver started");

       
        
        register_camera_routes(server);
        register_motor_routes(server);

         httpd_uri_t favicon_uri = {
            .uri = "/favicon.ico",
            .method = HTTP_GET,
            .handler = favicon_handler
        };
        httpd_register_uri_handler(server, &favicon_uri);
        
        httpd_uri_t index_uri = {
            .uri = "/",
            .method = HTTP_GET,
            .handler = index_handler
        };
        httpd_register_uri_handler(server, &index_uri);


        
    } else {
        ESP_LOGE(TAG, "Failed to start webserver");
    }

    return server;
}



