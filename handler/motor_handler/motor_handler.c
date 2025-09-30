static esp_err_t control_handler(httpd_req_t *req) {
    ESP_LOGI(TAG, "HTTP GET /control");

    char query[128];
    int forward = 0, backward = 0, left = 0, right = 0;
    int crotator = 0, acrotator = 0;

    if (httpd_req_get_url_query_str(req, query, sizeof(query)) == ESP_OK) {
        char val[8];

        if (httpd_query_key_value(query, "forward", val, sizeof(val)) == ESP_OK) {
            forward = atoi(val);
        }
        if (httpd_query_key_value(query, "backward", val, sizeof(val)) == ESP_OK) {
            backward = atoi(val);
        }
        if (httpd_query_key_value(query, "left", val, sizeof(val)) == ESP_OK) {
            left = atoi(val);
        }
        if (httpd_query_key_value(query, "right", val, sizeof(val)) == ESP_OK) {
            right = atoi(val);
        }
        if (httpd_query_key_value(query, "crotator", val, sizeof(val)) == ESP_OK) {
            crotator = atoi(val);
        }
        if (httpd_query_key_value(query, "acrotator", val, sizeof(val)) == ESP_OK) {
            acrotator = atoi(val);
        }

        ESP_LOGI(TAG, "Control States: F=%d, B=%d, L=%d, R=%d, C=%d, AC=%d",
                 forward, backward, left, right, crotator, acrotator);

        // TODO: 将这些状态传递给 motor_control_update() 或其他控制模块
    }

    httpd_resp_sendstr(req, "OK");
    return ESP_OK;
}
