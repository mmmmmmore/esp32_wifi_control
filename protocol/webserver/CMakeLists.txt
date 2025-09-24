idf_component_register(
    SRCS "webserver.c"
    INCLUDE_DIRS "."
    REQUIRES 
        esp_wifi esp_http_server nvs_flash driver 
        esp_jpeg jpeg 
        sccb camera jpeg ov7670 common_gpio)
