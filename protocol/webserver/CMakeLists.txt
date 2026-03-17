idf_component_register(
    SRCS 
        "webserver.c"
    INCLUDE_DIRS 
        "."
    REQUIRES 
        esp_wifi esp_http_server nvs_flash driver 
        json object_detector ov7670_handler faceid_handler
        )
