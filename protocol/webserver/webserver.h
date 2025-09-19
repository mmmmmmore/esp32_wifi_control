#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "esp_http_server.h"

// 启动 HTTP 服务器
httpd_handle_t start_webserver(void);

#endif // WEBSERVER_H
