#ifndef WEBSERVER_BASE_H
#define WEBSERVER_BASE_H

#pragma once

#include "esp_http_server.h"

esp_err_t webserver_base_register(httpd_handle_t server);

#endif  //define the head of webserver_base
