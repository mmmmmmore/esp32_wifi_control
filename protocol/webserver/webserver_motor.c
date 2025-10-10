#include "webserver_control.h"
#include "esp_log.h"
#include "esp_http_server.h"
#include "common_gpio.h"
#include "motor_handler.h"

static const char *TAG = "webserver_control";

// HTTP POST 处理函数
esp_err_t joystick_post_handler(httpd_req_t *req) {
    char content[100];
    int ret = httpd_req_recv(req, content, sizeof(content));
    if (ret <= 0) {
        ESP_LOGE(TAG, "Failed to receive post data");
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to receive data");
        return ESP_FAIL;
    }

    content[ret] = '\0';
    ESP_LOGI(TAG, "Received joystick data: %s", content);

    // 解析 JSON 数据
    int angle = 0, distance = 0;
    sscanf(content, "{\"angle\":%d,\"distance\":%d}", &angle, &distance);

    // 传递给 motor_handler
    motor_handler_update(angle, distance);

    httpd_resp_sendstr(req, "OK");
    return ESP_OK;
}

// 注册 URI 处理器 register motor control relate uri of joystick handler

static esp_err_t register_motor_routes(httpd_handle_t server) {
    httpd_uri_t joystick_uri = {
        .uri       = "/joystick",
        .method    = HTTP_POST,
        .handler   = joystick_post_handler,
        .user_ctx  = NULL
    };
    return httpd_register_uri_handler(server, &joystick_uri);
}


