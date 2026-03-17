#pragma once

#include "esp_err.h"
#include "esp_http_server.h"

/**
 * @brief Start the HTTP server and register all URI handlers.
 *        Handlers covered:
 *          - Health        : GET /
 *          - Camera stream : GET /start  GET /stop  GET /stream  GET /snapshot
 *          - Detection     : GET /detection  GET /detector?enable=0|1  GET /detector/status
 *          - WebSocket     : GET /ws and GET /ws/detection (if CONFIG_HTTPD_WS_SUPPORT)
 *        Detection results are produced by a background task and exposed
 *        through /detection and pushed as JSON events over WebSocket.
 *        WebSocket also accepts bi-directional JSON commands for detector
 *        control and face ID mode/enroll/identify operations.
 * @return httpd_handle_t  Server handle, or NULL on failure.
 */
httpd_handle_t start_webserver(void);

/**
 * @brief Push the latest detection result to a connected WebSocket client.
 * @param server  Handle returned by start_webserver().
 * @return ESP_OK, ESP_ERR_INVALID_STATE (no result yet), ESP_ERR_NOT_FOUND
 *         (no client), or ESP_ERR_NOT_SUPPORTED (WS disabled).
 */
esp_err_t webserver_push_detection(httpd_handle_t server);