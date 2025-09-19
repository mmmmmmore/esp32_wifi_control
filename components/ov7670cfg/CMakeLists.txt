idf_component_register(
    SRCS "ov767_cfg.c"
    INCLUDE_DIRS "."
    REQUIRES esp_wifi esp_http_server nvs_flash driver
)
