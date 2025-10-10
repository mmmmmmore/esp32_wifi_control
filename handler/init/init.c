// handler/init/init.c
#include "init.h"
#include "stream_handler.h"
#include "joystick_handler.h"
#include "webserver_control.h"
#include "common_gpio.h"
#include "camera.h"
#include "log_handler.h"

void platform_init(void) {
    // 初始化 NVS 已在 app_main 中完成
    init_gpio();               // 初始化所有 GPIO
    init_log_handler();       // 初始化日志模块
    camera_init();            // 初始化摄像头
    stream_handler_init();    // 初始化图像流处理
    joystick_handler_init();  // 初始化摇杆处理
    webserver_control_init(); // 初始化 WebServer 控制逻辑
}
