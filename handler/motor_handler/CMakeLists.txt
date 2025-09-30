idf_component_register(
    SRCS 
        "motor_handler.c"
    INCLUDE_DIRS 
        "."
    REQUIRES 
        esp_wifi esp_http_server nvs_flash driver 
        sccb camera common_gpio motor_pwm
        webserver wifi_ap
        webserver_control
        )
