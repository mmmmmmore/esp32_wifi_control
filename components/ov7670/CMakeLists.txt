idf_component_register(
    SRCS "ov7670.c"
    INCLUDE_DIRS "."
    REQUIRES esp_wifi esp_http_server nvs_flash driver sccb ov7670cfg ov7670gpio)
