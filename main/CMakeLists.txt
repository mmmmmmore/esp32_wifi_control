idf_component_register(
    SRCS "main.c"
    INCLUDE_DIRS "."
    REQUIRES 
        esp_wifi esp_http_server nvs_flash driver 
        camera jpeg sccb common_gpio
        ov7670_handler init faceid_handler
        webserver wifi_ap 
        esp_system esp_psram spiffs
)
