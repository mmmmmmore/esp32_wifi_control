idf_component_register(
    SRCS 
        "ota_handler.c"
    INCLUDE_DIRS 
        "."
    REQUIRES 
        esp_wifi esp_http_server nvs_flash driver 
        sccb camera common_gpio jpeg 
        webserver wifi_ap
        )
