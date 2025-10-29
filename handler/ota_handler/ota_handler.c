#include "ota_handler.h"
#include "esp_log.h"
#include "esp_http_client.h"
#include "esp_https_ota.h"
#include "esp_system.h"

static const char *TAG = "ota_handler";

void ota_start(const char *ota_url)
{
    ESP_LOGI(TAG, "Starting OTA from URL: %s", ota_url);

    esp_http_client_config_t config = {
        .url = ota_url,
        .timeout_ms = 5000,
        .keep_alive_enable = true,
    };

    esp_err_t ret = esp_https_ota(&config);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "OTA successful, restarting...");
        esp_restart();
    } else {
        ESP_LOGE(TAG, "OTA failed with error: %s", esp_err_to_name(ret));
    }
}
