idf_component_register(
    SRCS 
        "camera.c"
    INCLUDE_DIRS 
        "."
    REQUIRES 
        esp_wifi esp_http_server nvs_flash driver 
        common_gpio sccb jpeg ov7670
    )
