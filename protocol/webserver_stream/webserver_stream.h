#pragma once

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

// 初始化图像传输 WebSer

esp_err_t webserver_stream_register_handlers(httpd_handle_t server);

#ifdef __cplusplus
}
#endif