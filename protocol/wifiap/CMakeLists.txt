idf_component_register(
    SRCS "wifiap.c"
    INCLUDE_DIRS "."
    REQUIRES esp_wifi esp_http_server nvs_flash driver )
