idf_component_register(
    SRCS "webserver_control.c"
    INCLUDE_DIRS "."
    REQUIRES 
        esp_wifi esp_http_server nvs_flash driver 
        motor_handler
        webserver 
        common_gpio)
