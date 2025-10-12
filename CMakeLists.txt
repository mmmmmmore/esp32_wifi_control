cmake_minimum_required(VERSION 3.5)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

# 添加额外组件目录
set(EXTRA_COMPONENT_DIRS 
        components/camera
        components/common_gpio
        components/jpeg
        components/sccb
        protocol/webserver
        protocol/wifi_ap 
        handler/init
        handler/ov7670_handler 
        handler/motor_handler
        spiffs 
        )

project(esp32_wifi_control)

# SPIFFS 构建规则（如果启用）
spiffs_create_partition_image(spiffs spiffs FLASH_IN_PROJECT "spiffs")

