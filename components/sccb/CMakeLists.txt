idf_component_register(
    SRCS "sccb.c"
    INCLUDE_DIRS "."
    REQUIRES 
        esp_wifi esp_http_server nvs_flash driver 
        camera common_gpio jpeg  
        ov7670_handler
        webserver wifi_ap
    )
