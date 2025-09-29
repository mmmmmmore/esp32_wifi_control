#include "webserver_control.h"
#include "esp_http_server.h"
#include "esp_log.h"
#include "capture_control.h"
#include <string.h>
#include <stdlib.h>

static const char *TAG = "webserver_control";

static esp_err_t toggle_handler(httpd_req_t *req) {
    ESP_LOGI(TAG, "HTTP POST /toggle");
    char buf[8] = {0};
    int ret = httpd_req_recv(req, buf, sizeof(buf) - 1);
    if (ret <= 0) {
        ESP_LOGE(TAG, "Failed to receive toggle command");
        httpd_resp_send_500(req);
        return ESP_FAIL;
    }
    buf[ret] = '\0';
    ESP_LOGI(TAG, "Received toggle command: %s", buf);

    if (strncmp(buf, "ON", 2) == 0) {
        capture_control_set(true);
        httpd_resp_sendstr(req, "Capture ON");
    } else {
        capture_control_set(false);
        httpd_resp_sendstr(req, "Capture OFF");
    }
    return ESP_OK;
}

static esp_err_t control_handler(httpd_req_t *req) {
    ESP_LOGI(TAG, "HTTP GET /control");

    char query[64];
    char dir[16] = {0};
    char state_str[8] = {0};
    int state = 0;

    if (httpd_req_get_url_query_str(req, query, sizeof(query)) == ESP_OK) {
        httpd_query_key_value(query, "dir", dir, sizeof(dir));
        httpd_query_key_value(query, "state", state_str, sizeof(state_str));
        state = atoi(state_str);
        ESP_LOGI(TAG, "Direction: %s, State: %d", dir, state);
        // TODO: update control state
    }

    httpd_resp_sendstr(req, "OK");
    return ESP_OK;
}

void register_control_routes(httpd_handle_t server) {
    httpd_uri_t toggle_uri = {
        .uri = "/toggle",
        .method = HTTP_POST,
        .handler = toggle_handler
    };
    httpd_register_uri_handler(server, &toggle_uri);

    httpd_uri_t control_uri = {
        .uri = "/control",
        .method = HTTP_GET,
        .handler = control_handler
    };
    httpd_register_uri_handler(server, &control_uri);
}
