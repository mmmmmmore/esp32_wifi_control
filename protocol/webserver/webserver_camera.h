#ifndef WEBSERVER_CAMERA_H
#define WEBSERVER_CAMERA_H

#pragma once

#include "esp_http_server.h"

void register_camera_routes(httpd_handle_t server);



#endif