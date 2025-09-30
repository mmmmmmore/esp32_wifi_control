#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "esp_rom_sys.h"
#include "esp_log.h"
#include "motor_handler.h"  // 添加 motor_handler 头文件



static esp_err_t control_handler(httpd_req_t *req) {
    ESP_LOGI(TAG, "HTTP GET /control");

    char query[128];
    motor_command_t cmd = {0};

    if (httpd_req_get_url_query_str(req, query, sizeof(query)) == ESP_OK) {
        char val[8];

        if (httpd_query_key_value(query, "forward", val, sizeof(val)) == ESP_OK) cmd.forward = atoi(val);
        if (httpd_query_key_value(query, "backward", val, sizeof(val)) == ESP_OK) cmd.backward = atoi(val);
        if (httpd_query_key_value(query, "left", val, sizeof(val)) == ESP_OK) cmd.left = atoi(val);
        if (httpd_query_key_value(query, "right", val, sizeof(val)) == ESP_OK) cmd.right = atoi(val);
        if (httpd_query_key_value(query, "crotator", val, sizeof(val)) == ESP_OK) cmd.crotator = atoi(val);
        if (httpd_query_key_value(query, "acrotator", val, sizeof(val)) == ESP_OK) cmd.acrotator = atoi(val);

        ESP_LOGI(TAG, "Motor State: F=%d B=%d L=%d R=%d C=%d AC=%d",
                 cmd.forward, cmd.backward, cmd.left, cmd.right, cmd.crotator, cmd.acrotator);

        motor_handler_update(&cmd);  // 调用 motor_handler 更新控制状态
    }

    httpd_resp_sendstr(req, "OK");
    return ESP_OK;
}


