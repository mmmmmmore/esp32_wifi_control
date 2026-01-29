idf_component_register(
    SRCS 
        "webserver.c"
        "webserver_camera.c"
    INCLUDE_DIRS 
        "."
    REQUIRES 
        esp_wifi esp_http_server nvs_flash driver 
        motor_handler control_mgmt json
        sdcard ov7670_handler ota_handler
        )
