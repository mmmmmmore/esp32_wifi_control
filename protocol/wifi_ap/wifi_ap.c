#include "wifi_ap.h"
#include "sdkconfig.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include <string.h>

static const char *TAG = "wifi_ap";

// 从 sdkconfig 中读取 SSID 和密码
#define WIFI_SSID CONFIG_WIFI_SOFTAP_SSID
#define WIFI_PASS CONFIG_WIFI_SOFTAP_PASSWORD

void wifi_init_softap(void)
{
    esp_netif_t *netif = esp_netif_create_default_wifi_ap();
    if (netif == NULL){
        ESP_LOGE(TAG, "Fail to cteate the default wifi AP interface");
        return;
    }

    // 初始化 WiFi 驱动
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_err_t err = esp_wifi_init(&cfg);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_wifi_init failed: %s", esp_err_to_name(err));
        return;
    }

    // 配置 SoftAP 参数
    wifi_config_t wifi_config = {
        .ap = {
            .ssid = WIFI_SSID,
            .ssid_len = strlen(WIFI_SSID),
            .password = WIFI_PASS,
            .max_connection = 4,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };

    // 如果密码为空，则使用开放模式
    if (strlen(WIFI_PASS) == 0) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    err = esp_wifi_set_mode(WIFI_MODE_AP);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_wifi_set_mode failed: %s", esp_err_to_name(err));
        return;
    }

    err = esp_wifi_set_config(WIFI_IF_AP, &wifi_config);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_wifi_set_config failed: %s", esp_err_to_name(err));
        return;
    }

    err = esp_wifi_start();
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "esp_wifi_start failed: %s", esp_err_to_name(err));
        return;
    }

    ESP_LOGI(TAG, "WiFi SoftAP started. SSID: %s, Password: %s", WIFI_SSID, WIFI_PASS);
}
