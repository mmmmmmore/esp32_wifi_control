#ifndef WEBSERVER_H
#define WEBSERVER_H

#pragma once
#include "esp_http_server.h"

/**
 * @brief Start HTTP WebServer and register all URI handlers
 * @return httpd_handle_t Server handle, NULL if failed
 */
httpd_handle_t start_webserver(void);

#endif // WEBSERVER_H