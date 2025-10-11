idf_component_register(
    SRCS "webserver_motor.c" "webserver_camera.c" "webserver.c"
    INCLUDE_DIRS "."
    REQUIRES 
        esp_wifi esp_http_server nvs_flash driver 
        esp_jpeg jpeg 
        ov7670_handler motor_handler
        capture_control
        webserver_control
        sccb camera jpeg common_gpio)
