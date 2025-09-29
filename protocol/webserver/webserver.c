#include "webserver.h"
#include "webserver_camera.h"
#include "webserver_control.h"
#include "esp_log.h"

static const char *TAG = "webserver";

httpd_handle_t start_webserver(void) {
    ESP_LOGI(TAG, "Starting webserver...");
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;

    if (httpd_start(&server, &config) == ESP_OK) {
        ESP_LOGI(TAG, "Webserver started");
        register_camera_routes(server);
        register_control_routes(server);
    } else {
        ESP_LOGE(TAG, "Failed to start webserver");
    }

    return server;
}
