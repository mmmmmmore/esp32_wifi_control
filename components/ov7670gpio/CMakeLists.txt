idf_component_register(
    SRCS "ov7670_gpio.c"
    INCLUDE_DIRS "."
    REQUIRES esp_wifi esp_http_server nvs_flash driver freertos)
