#include <stdio.h>
#include "wifi_ap.h"
#include "webserver.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_event.h"
//#include "camera.h"
#include "common_gpio.h"
#include "jpeg.h"
#include "ov7670_handler.h"
#include "object_detector.h"
#include "faceid_handler.h"
#include "init.h"
#include "sccb.h"
//#include "spiffs.h"
#include "esp_psram.h"
#include "esp_heap_caps.h"



void check_psram_status() {
    ESP_LOGI("PSRAM", "PSRAM size: %d bytes", esp_psram_get_size());
    ESP_LOGI("PSRAM", "Free heap: %d bytes", esp_get_free_heap_size());

    if (esp_psram_is_initialized()) {
        ESP_LOGI("PSRAM", "PSRAM is initialized and ready.");
    } else {
        ESP_LOGE("PSRAM", "PSRAM is NOT initialized.");
    }

    void *test_ptr = heap_caps_malloc(1024, MALLOC_CAP_SPIRAM);
    if (test_ptr) {
        ESP_LOGI("PSRAM", "Successfully allocated 1KB from PSRAM.");
        free(test_ptr);
    } else {
        ESP_LOGE("PSRAM", "Failed to allocate memory from PSRAM.");
    }
}

void app_main(void) {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    printf("ESP32S3 Boot Success...\n");
    // 初始化 WiFi SoftAP
    wifi_init_softap();

    //初始化网络协议栈
    //ESP_ERROR_CHECK(esp_netif_init());
    //ESP_ERROR_CHECK(esp_event_loop_create_default());

    check_psram_status();

    detector_config_t detector_cfg = {
        .enabled = true,
        .input_width = 320,
        .input_height = 240,
        .score_threshold = 0.45f,
    };
    object_detector_init(&detector_cfg);

    ret = faceid_handler_init();
    if (ret != ESP_OK) {
        ESP_LOGW("FACEID", "Face ID init failed: %s", esp_err_to_name(ret));
    }
    

    platform_init();
    //camera_init();
    // 初始化摄像头（GPIO + SCCB + 寄存器配置）
    //ov7670_config();

    // 启动 HTTP 服务器
    start_webserver();

    printf("系统初始化完成，等待客户端连接...\n");
}
