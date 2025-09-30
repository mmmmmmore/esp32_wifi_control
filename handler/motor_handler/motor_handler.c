
#include "motor_handler.h"
#include "esp_http_server.h"
#include "esp_log.h"
#include "motor_pwm.h"
#include <string.h>
#include <stdlib.h>

static const char *TAG = "motor_handler";

// 接收 HTTP 控制请求并解析方向状态
esp_err_t motor_control_http_handler(httpd_req_t *req) {
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

        motor_handler_update(&cmd);
    }

    httpd_resp_sendstr(req, "OK");
    return ESP_OK;
}

// 根据方向状态更新电机控制逻辑void motor_handler_update(const motor_command_t *cmd) {
    pwm_stop_all_motors();

    // 前进：1-4 正转
    if (cmd->forward) {
        ESP_LOGI(TAG, "Action: FORWARD   _-||-_");
        for (int i = 1; i <= 4; i++) {
            pwm_set_motor_direction(i, true);
            pwm_set_motor_speed(i, 80);
        }
    }
    // 后退：1-4 反转
    else if (cmd->backward) {
        ESP_LOGI(TAG, "Action: BACKWARD  ##||## ");
        for (int i = 1; i <= 4; i++) {
            pwm_set_motor_direction(i, false);
            pwm_set_motor_speed(i, 80);
        }
    }
    // 右移：1-4 反转，2-3 正转
    else if (cmd->right) {
        ESP_LOGI(TAG, "Action: RIGHT >>>");
        pwm_set_motor_direction(1, false);
        pwm_set_motor_direction(2, true);
        pwm_set_motor_direction(3, true);
        pwm_set_motor_direction(4, false);
        for (int i = 1; i <= 4; i++) {
            pwm_set_motor_speed(i, 80);
        }
    }
    // 左移：1-4 正转，2-3 反转
    else if (cmd->left) {
        ESP_LOGI(TAG, "Action: LEFT<<<");
        pwm_set_motor_direction(1, true);
        pwm_set_motor_direction(2, false);
        pwm_set_motor_direction(3, false);
        pwm_set_motor_direction(4, true);
        for (int i = 1; i <= 4; i++) {
            pwm_set_motor_speed(i, 80);
        }
    }

    // 顺时针旋转：1-3 反转，2-4 正转
    if (cmd->crotator) {
        ESP_LOGI(TAG, "Action: Clock_Rotor");
        pwm_set_motor_direction(1, false);
        pwm_set_motor_direction(2, true);
        pwm_set_motor_direction(3, false);
        pwm_set_motor_direction(4, true);
        for (int i = 1; i <= 4; i++) {
            pwm_set_motor_speed(i, 80);
        }
    }
    // 逆时针旋转：1-3 正转，2-4 反转
    else if (cmd->acrotator) {
        ESP_LOGI(TAG, "Action: Wise-Clock_Rotor");
        pwm_set_motor_direction(1, true);
        pwm_set_motor_direction(2, false);
        pwm_set_motor_direction(3, true);
        pwm_set_motor_direction(4, false);
        for (int i = 1; i <= 4; i++) {
            pwm_set_motor_speed(i, 80);
        }
    }
}

