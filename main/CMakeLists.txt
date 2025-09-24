idf_component_register(
    SRCS "main.c"
    INCLUDE_DIRS "."
    REQUIRES 
        esp_wifi esp_http_server nvs_flash driver 
        camera jpeg ov7670 sccb global_gpio
        ov7670_handleer
        webserver wifi_ap 
        spiffs 
)
