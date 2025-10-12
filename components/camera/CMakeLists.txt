idf_component_register(
    SRCS 
        "camera.c"
    INCLUDE_DIRS 
        "."
    REQUIRES 
        nvs_flash driver 
        common_gpio sccb jpeg 
    )
