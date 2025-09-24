idf_component_register(
    SRCS 
        "ov7670_handler.c"
    INCLUDE_DIRS 
        "."
    REQUIRES 
        esp_wifi esp_http_server nvs_flash driver 
        sccb camera global_gpio jpeg 
        webserver wifi_ap
        )
