idf_component_register(
    SRCS "stream_control.c"
    INCLUDE_DIRS "."
    REQUIRES 
        esp_wifi esp_http_server nvs_flash driver 
        camera common_gpio jpeg ov7670 
        ov7670_handler
        webserver wifi_ap
    )
