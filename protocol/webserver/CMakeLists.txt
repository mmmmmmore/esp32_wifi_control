idf_component_register(
    SRCS "webserver.c"
    INCLUDE_DIRS "."
    REQUIRES 
        esp_wifi esp_http_server nvs_flash driver 
        esp_jpeg jpeg 
        ov7670_handler
        capture_control
        sccb camera jpeg common_gpio)
