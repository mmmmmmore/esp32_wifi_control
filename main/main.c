#include <stdio.h>
#include "wifi_ap.h"
#include "webserver.h"
#include "ov7670.h"

void app_main(void) {
    // 初始化 WiFi SoftAP
    wifi_init_softap();

    // 初始化摄像头（GPIO + SCCB + 寄存器配置）
    ov7670_init();

    // 启动 HTTP 服务器
    start_webserver();

    printf("系统初始化完成，等待客户端连接...\n");
}
