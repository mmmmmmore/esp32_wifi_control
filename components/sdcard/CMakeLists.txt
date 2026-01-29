idf_component_register(
    SRCS "sdcard.c"
    INCLUDE_DIRS "."
    REQUIRES driver fatfs sdmmc esp_timer common_gpio
)
