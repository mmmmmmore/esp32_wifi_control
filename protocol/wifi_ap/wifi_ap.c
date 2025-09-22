#include "wifi_ap.h"
#include "sdkconfig.h"


#define WIFI_SSID "ESP32-AP"
#define WIFI_PASS "12345678"
#define LED_GPIO GPIO_NUM_2

//static const char *TAG = "main";

// 从 sdkconfig 中读取 SSID 和密码
const char* ssid = CONFIG_WIFI_SOFTAP_SSID;
const char* password = CONFIG_WIFI_SOFTAP_PASSWORD;

static const char *TAG = "wifi_ap";

void wifi_init_softap(void) {
    esp_netif_create_default_wifi_ap();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = "",
            .ssid_len = strlen(ssid),
            .max_connection = 4,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };

    strncpy((char*)wifi_config.ap.ssid, ssid, sizeof(wifi_config.ap.ssid));
    strncpy((char*)wifi_config.ap.password, password, sizeof(wifi_config.ap.password));

    esp_wifi_set_mode(WIFI_MODE_AP);
    esp_wifi_set_config(WIFI_IF_AP, &wifi_config);
    esp_wifi_start();

    ESP_LOGI(TAG, "WiFi SoftAP started. SSID: ESP32-SoftAP");
}

