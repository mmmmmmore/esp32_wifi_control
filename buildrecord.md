
/Users/maochun/esp32prj/Project_CAM/branch/esp32_wifi_control/handler/ota_handler/ota_handler.c: In function 'ota_start':
/Users/maochun/esp32prj/Project_CAM/branch/esp32_wifi_control/handler/ota_handler/ota_handler.c:93:35: error: passing argument 1 of 'esp_https_ota' from incompatible pointer type [-Wincompatible-pointer-types]
   93 |     esp_err_t ret = esp_https_ota(&ota_config);
      |                                   ^~~~~~~~~~~
      |                                   |
      |                                   esp_http_client_config_t *
In file included from /Users/maochun/esp32prj/Project_CAM/branch/esp32_wifi_control/handler/ota_handler/ota_handler.c:4:
/Users/maochun/esp32prj/esp-idf/components/esp_https_ota/include/esp_https_ota.h:114:55: note: expected 'const esp_https_ota_config_t *' but argument is of type 'esp_http_client_config_t *'
  114 | esp_err_t esp_https_ota(const esp_https_ota_config_t *ota_config);
      |                         ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^~~~~~~~~~