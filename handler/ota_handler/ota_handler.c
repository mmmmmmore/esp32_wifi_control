#include "ota_handler.h"
#include "esp_log.h"
#include "esp_http_client.h"
#include "esp_https_ota.h"
#include "esp_system.h"
#include "cJSON.h"
#include "esp_app_desc.h"
#include "mbedtls/sha256.h"

static const char *TAG = "ota_handler";

// OTA 状态：0=idle, 1=success, -1=failed
static int ota_result = 0;

int ota_get_result(void) {
    return ota_result;
}

static esp_err_t _http_event_handler(esp_http_client_event_t *evt) {
    switch (evt->event_id) {
        case HTTP_EVENT_ON_DATA:
            ESP_LOGI(TAG, "Received %d bytes", evt->data_len);
            break;
        case HTTP_EVENT_ERROR:
            ESP_LOGE(TAG, "HTTP_EVENT_ERROR");
            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGI(TAG, "Download finished");
            break;
        default:
            break;
    }
    return ESP_OK;
}

void ota_start(const char *manifest_url)
{
    ESP_LOGI(TAG, "Fetching manifest: %s", manifest_url);
    ota_result = 0; // 重置状态

    // 下载 manifest.json
    esp_http_client_config_t manifest_config = {
        .url = manifest_url,
        .event_handler = _http_event_handler,
        .timeout_ms = 5000,
    };

    esp_http_client_handle_t client = esp_http_client_init(&manifest_config);
    esp_err_t err = esp_http_client_open(client, 0);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to open manifest URL");
        ota_result = -1;
        return;
    }

    int content_length = esp_http_client_fetch_headers(client);
    char *buffer = malloc(content_length + 1);
    int read_len = esp_http_client_read_response(client, buffer, content_length);
    buffer[read_len] = '\0';
    esp_http_client_close(client);
    esp_http_client_cleanup(client);

    cJSON *root = cJSON_Parse(buffer);
    free(buffer);
    if (!root) {
        ESP_LOGE(TAG, "Failed to parse manifest JSON");
        ota_result = -1;
        return;
    }

    const char *latest_version = cJSON_GetObjectItem(root, "latest_version")->valuestring;
    const char *firmware_url   = cJSON_GetObjectItem(root, "firmware_url")->valuestring;
    cJSON_Delete(root);

    const esp_app_desc_t *app_desc = esp_app_get_description();
    ESP_LOGI(TAG, "Current version: %s, Latest: %s", app_desc->version, latest_version);

    if (strcmp(app_desc->version, latest_version) >= 0) {
        ESP_LOGI(TAG, "Already up-to-date");
        ota_result = 1; // 表示成功（无需升级）
        return;
    }

    // 执行 OTA
    ESP_LOGI(TAG, "Starting OTA from URL: %s", firmware_url);

    // 先定义 http_config
    esp_http_client_config_t http_config = {
        .url = firmware_url,
        .event_handler = _http_event_handler,
        .timeout_ms = 10000,
        .keep_alive_enable = true,
    };

    // 再封装成 ota_config
    esp_https_ota_config_t ota_config = {
        .http_config = &http_config,
        .http_client_init_cb = NULL;   
    //    .cert_pem = NULL,   // 如果有 HTTPS 证书，可以在这里配置
    //  .partial_http_download = false,
    };

    esp_err_t ret = esp_https_ota(&ota_config);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "OTA successful, restarting...");
        ota_result = 1;
        esp_restart();
    } else {
        ESP_LOGE(TAG, "OTA failed: %s", esp_err_to_name(ret));
        ota_result = -1;
    }
}

