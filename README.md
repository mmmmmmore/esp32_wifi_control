//
your_project/
├── main/
│   ├── main.c
│   └── CMakeLists.txt
├── CMakeLists.txt
└── sdkconfig

✅ 功能模块划分
1. Wi-Fi SoftAP 初始化模块
负责启动 ESP32 的热点功能，让手机或电脑连接。

2. HTTP Server 模块
负责监听 HTTP 请求，并根据 URI 执行对应的处理逻辑。

3. GPIO 控制模块
根据 HTTP 请求控制 GPIO（比如点亮或熄灭 LED）。


example code from copilot

#include <string.h>
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_http_server.h"
#include "driver/gpio.h"

#define WIFI_SSID "ESP32-AP"
#define WIFI_PASS "12345678"
#define LED_GPIO GPIO_NUM_2

static const char *TAG = "main";

// 初始化 GPIO
void init_gpio() {
    gpio_reset_pin(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);
}

// 处理根路径请求
esp_err_t root_get_handler(httpd_req_t *req) {
    const char *resp = "<h1>ESP32 控制面板</h1><p><a href=\"/led/on\">LED ON</a> | <a href=\"/led/off\">LED OFF</a></p>";
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

// 打开 LED
esp_err_t led_on_handler(httpd_req_t *req) {
    gpio_set_level(LED_GPIO, 1);
    httpd_resp_send(req, "LED is ON", HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

// 关闭 LED
esp_err_t led_off_handler(httpd_req_t *req) {
    gpio_set_level(LED_GPIO, 0);
    httpd_resp_send(req, "LED is OFF", HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

// 启动 HTTP 服务器
httpd_handle_t start_webserver(void) {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;

    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_uri_t root = {
            .uri = "/",
            .method = HTTP_GET,
            .handler = root_get_handler,
            .user_ctx = NULL
        };
        httpd_uri_t led_on = {
            .uri = "/led/on",
            .method = HTTP_GET,
            .handler = led_on_handler,
            .user_ctx = NULL
        };
        httpd_uri_t led_off = {
            .uri = "/led/off",
            .method = HTTP_GET,
            .handler = led_off_handler,
            .user_ctx = NULL
        };

        httpd_register_uri_handler(server, &root);
        httpd_register_uri_handler(server, &led_on);
        httpd_register_uri_handler(server, &led_off);
    }

    return server;
}

// 初始化 Wi-Fi SoftAP
void wifi_init_softap(void) {
    esp_netif_create_default_wifi_ap();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = WIFI_SSID,
            .ssid_len = strlen(WIFI_SSID),
            .password = WIFI_PASS,
            .max_connection = 4,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };

    esp_wifi_set_mode(WIFI_MODE_AP);
    esp_wifi_set_config(WIFI_IF_AP, &wifi_config);
    esp_wifi_start();

    ESP_LOGI(TAG, "Wi-Fi AP started. SSID:%s password:%s", WIFI_SSID, WIFI_PASS);
}

// 主函数入口
void app_main(void) {
    nvs_flash_init();
    esp_netif_init();
    esp_event_loop_create_default();

    init_gpio();
    wifi_init_softap();
    start_webserver();
}
