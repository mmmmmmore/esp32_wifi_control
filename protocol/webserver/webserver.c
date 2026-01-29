#include "webserver.h"
#include "motor_handler.h"
#include "control_mgmt.h"
#include "webserver_camera.h"
#include "ota_handler.h"
#include "esp_http_server.h"
#include "esp_err.h"
#include "esp_log.h"
#include "cJSON.h"
#include <string.h>

static const char *TAG = "webserver";

// ========================================
// Static File Handlers
// ========================================

static esp_err_t index_handler(httpd_req_t *req) {
    ESP_LOGI(TAG, "HTTP GET /");

    FILE *f = fopen("/spiffs/index.html", "r");
    if (!f) {
        ESP_LOGE(TAG, "Failed to open index.html");
        httpd_resp_send_404(req);
        return ESP_FAIL;
    }

    char buf[1024];
    size_t read_bytes;
    httpd_resp_set_type(req, "text/html");

    while ((read_bytes = fread(buf, 1, sizeof(buf), f)) > 0) {
        httpd_resp_send_chunk(req, buf, read_bytes);
    }
    fclose(f);
    httpd_resp_send_chunk(req, NULL, 0);
    return ESP_OK;
}

static esp_err_t static_file_handler(httpd_req_t *req) {
    char filepath[600];
    snprintf(filepath, sizeof(filepath), "/spiffs%s", req->uri);
    
    ESP_LOGI(TAG, "Static file request: %s", filepath);

    FILE *f = fopen(filepath, "r");
    if (!f) {
        ESP_LOGE(TAG, "Failed to open file: %s", filepath);
        httpd_resp_send_404(req);
        return ESP_FAIL;
    }

    // Set content type based on file extension
    const char *ext = strrchr(req->uri, '.');
    if (ext != NULL) {
        if (strcmp(ext, ".css") == 0) {
            httpd_resp_set_type(req, "text/css");
        } else if (strcmp(ext, ".js") == 0) {
            httpd_resp_set_type(req, "application/javascript");
        } else if (strcmp(ext, ".json") == 0) {
            httpd_resp_set_type(req, "application/json");
        } else if (strcmp(ext, ".png") == 0) {
            httpd_resp_set_type(req, "image/png");
        } else if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0) {
            httpd_resp_set_type(req, "image/jpeg");
        } else if (strcmp(ext, ".svg") == 0) {
            httpd_resp_set_type(req, "image/svg+xml");
        } else if (strcmp(ext, ".ico") == 0) {
            httpd_resp_set_type(req, "image/x-icon");
        } else if (strcmp(ext, ".html") == 0) {
            httpd_resp_set_type(req, "text/html");
        } else {
            httpd_resp_set_type(req, "application/octet-stream");
        }
    }

    char buf[1024];
    size_t read_bytes;
    
    while ((read_bytes = fread(buf, 1, sizeof(buf), f)) > 0) {
        if (httpd_resp_send_chunk(req, buf, read_bytes) != ESP_OK) {
            fclose(f);
            ESP_LOGE(TAG, "Failed to send file chunk");
            return ESP_FAIL;
        }
    }
    
    fclose(f);
    httpd_resp_send_chunk(req, NULL, 0);
    return ESP_OK;
}

static esp_err_t favicon_handler(httpd_req_t *req) {
    ESP_LOGI(TAG, "Favicon handler called");
    httpd_resp_set_type(req, "image/x-icon");
    httpd_resp_send(req, NULL, 0);
    return ESP_OK;
}

// ========================================
// OTA Update Handlers
// ========================================

static esp_err_t ota_handler(httpd_req_t *req) {
    ESP_LOGI(TAG, "OTA handler called");

    const char *manifest_url = "https://192.168.4.2:8000/firmware/manifest.json";
    ota_start(manifest_url);

    httpd_resp_send(req, "OTA started", HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

static esp_err_t ota_status_handler(httpd_req_t *req) {
    ESP_LOGI(TAG, "OTA status handler called");

    int result = ota_get_result();
    char resp[64];
    snprintf(resp, sizeof(resp), "{\"result\": %d}", result);

    httpd_resp_set_type(req, "application/json");
    httpd_resp_send(req, resp, HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

// ========================================
// Motor Control Handlers
// ========================================

static esp_err_t joystick_handler(httpd_req_t *req) {
    char content[200];
    int ret = httpd_req_recv(req, content, sizeof(content) - 1);
    if (ret <= 0) {
        ESP_LOGE(TAG, "Failed to receive joystick data");
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to receive data");
        return ESP_FAIL;
    }

    content[ret] = '\0';
    ESP_LOGI(TAG, "Received joystick data: %s", content);

    cJSON *json = cJSON_Parse(content);
    if (!json) {
        ESP_LOGE(TAG, "Invalid JSON format");
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Invalid JSON");
        return ESP_FAIL;
    }

    cJSON *uuid_item = cJSON_GetObjectItem(json, "uuid");
    cJSON *angle_item = cJSON_GetObjectItem(json, "angle");
    cJSON *distance_item = cJSON_GetObjectItem(json, "distance");

    if (!cJSON_IsString(uuid_item) || !cJSON_IsNumber(angle_item) || !cJSON_IsNumber(distance_item)) {
        ESP_LOGW(TAG, "Missing or invalid fields in joystick data");
        cJSON_Delete(json);
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Missing or invalid fields");
        return ESP_FAIL;
    }

    const char *uuid = uuid_item->valuestring;
    int angle = angle_item->valueint;
    int distance = distance_item->valueint;

    // Verify control permission
    if (!control_is_owner(uuid)) {
        ESP_LOGW(TAG, "Unauthorized joystick control attempt by UUID: %s", uuid);
        cJSON_Delete(json);
        httpd_resp_send_err(req, HTTPD_403_FORBIDDEN, "Not authorized");
        return ESP_FAIL;
    }

    // Send to motor handler
    motor_handler_update(angle, distance);
    cJSON_Delete(json);

    httpd_resp_sendstr(req, "OK");
    return ESP_OK;
}

static esp_err_t rotation_handler(httpd_req_t *req) {
    char content[200];
    int ret = httpd_req_recv(req, content, sizeof(content) - 1);
    if (ret <= 0) {
        ESP_LOGE(TAG, "Failed to receive rotation data");
        httpd_resp_send_err(req, HTTPD_500_INTERNAL_SERVER_ERROR, "Failed to receive data");
        return ESP_FAIL;
    }

    content[ret] = '\0';
    ESP_LOGI(TAG, "Received rotation data: %s", content);

    cJSON *json = cJSON_Parse(content);
    if (!json) {
        ESP_LOGE(TAG, "Invalid JSON format for rotation");
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Invalid JSON");
        return ESP_FAIL;
    }

    cJSON *uuid_item = cJSON_GetObjectItem(json, "uuid");
    cJSON *direction_item = cJSON_GetObjectItem(json, "direction");
    cJSON *degrees_item = cJSON_GetObjectItem(json, "degrees");

    if (!cJSON_IsString(uuid_item) || !cJSON_IsString(direction_item) || !cJSON_IsNumber(degrees_item)) {
        ESP_LOGW(TAG, "Missing or invalid fields in rotation data");
        cJSON_Delete(json);
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Missing or invalid fields");
        return ESP_FAIL;
    }

    const char *uuid = uuid_item->valuestring;
    const char *direction = direction_item->valuestring;
    int degrees = degrees_item->valueint;

    // Verify control permission
    if (!control_is_owner(uuid)) {
        ESP_LOGW(TAG, "Unauthorized rotation attempt by UUID: %s", uuid);
        cJSON_Delete(json);
        httpd_resp_send_err(req, HTTPD_403_FORBIDDEN, "Not authorized");
        return ESP_FAIL;
    }

    bool clockwise;
    if (strcmp(direction, "cw") == 0) {
        clockwise = true;
    } else if (strcmp(direction, "ccw") == 0) {
        clockwise = false;
    } else if (strcmp(direction, "stop") == 0) {
        clockwise = true; // direction irrelevant when degrees==0
        degrees = 0;
    } else {
        ESP_LOGW(TAG, "Invalid rotation direction: %s", direction);
        cJSON_Delete(json);
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Invalid direction");
        return ESP_FAIL;
    }

    motor_handler_rotate(clockwise, degrees);
    cJSON_Delete(json);

    httpd_resp_sendstr(req, "OK");
    return ESP_OK;
}

static esp_err_t control_request_handler(httpd_req_t *req) {
    char content[128];
    int ret = httpd_req_recv(req, content, sizeof(content));
    if (ret <= 0) {
        ESP_LOGW(TAG, "Failed to receive control request");
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Invalid request");
        return ESP_FAIL;
    }

    content[ret] = '\0';

    char uuid[64] = {0};
    char *uuid_start = strstr(content, "\"uuid\":\"");
    if (uuid_start) {
        uuid_start += strlen("\"uuid\":\"");
        char *uuid_end = strchr(uuid_start, '"');
        if (uuid_end && (uuid_end - uuid_start) < sizeof(uuid)) {
            strncpy(uuid, uuid_start, uuid_end - uuid_start);
            uuid[uuid_end - uuid_start] = '\0';
        }
    }

    if (strlen(uuid) == 0) {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Missing UUID");
        return ESP_FAIL;
    }

    bool granted = control_request(uuid);

    char response[128];
    snprintf(response, sizeof(response),
             "{ \"granted\": %s, \"current_owner\": \"%s\" }",
             granted ? "true" : "false",
             control_get_current());

    httpd_resp_set_type(req, "application/json");
    httpd_resp_send(req, response, strlen(response));
    
    ESP_LOGI(TAG, "Control %s for UUID: %s", granted ? "granted" : "denied", uuid);
    return ESP_OK;
}

static esp_err_t control_release_handler(httpd_req_t *req) {
    char content[128];
    int ret = httpd_req_recv(req, content, sizeof(content));
    if (ret <= 0) {
        ESP_LOGW(TAG, "Failed to receive control release");
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Invalid request");
        return ESP_FAIL;
    }

    content[ret] = '\0';

    char uuid[64] = {0};
    char *uuid_start = strstr(content, "\"uuid\":\"");
    if (uuid_start) {
        uuid_start += strlen("\"uuid\":\"");
        char *uuid_end = strchr(uuid_start, '"');
        if (uuid_end && (uuid_end - uuid_start) < sizeof(uuid)) {
            strncpy(uuid, uuid_start, uuid_end - uuid_start);
            uuid[uuid_end - uuid_start] = '\0';
        }
    }

    if (strlen(uuid) == 0) {
        httpd_resp_send_err(req, HTTPD_400_BAD_REQUEST, "Missing UUID");
        return ESP_FAIL;
    }

    bool released = control_release(uuid);

    char response[128];
    snprintf(response, sizeof(response),
             "{ \"released\": %s, \"new_owner\": \"%s\" }",
             released ? "true" : "false",
             control_get_current());

    httpd_resp_set_type(req, "application/json");
    httpd_resp_send(req, response, strlen(response));
    
    ESP_LOGI(TAG, "Control %s by UUID: %s", released ? "released" : "not released", uuid);
    return ESP_OK;
}

// ========================================
// WebServer Initialization
// ========================================

httpd_handle_t start_webserver(void) {
    ESP_LOGI(TAG, "Starting webserver...");
    
    // Initialize control manager
    control_manager_init();
    
    // Configure HTTP server
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.max_uri_handlers = 32;              // Increased from 16 to accommodate all handlers
    config.stack_size = 8192;                  // Increased from 4096 to prevent stack overflow during JPEG streaming
    config.uri_match_fn = httpd_uri_match_wildcard;
    httpd_handle_t server = NULL;

    if (httpd_start(&server, &config) != ESP_OK) {
        ESP_LOGE(TAG, "Failed to start webserver");
        return NULL;
    }

    ESP_LOGI(TAG, "Webserver started, registering URI handlers...");

    // Register root and static files
    httpd_uri_t index_uri = {
        .uri = "/",
        .method = HTTP_GET,
        .handler = index_handler,
        .user_ctx = NULL
    };
    
    httpd_uri_t index_html_uri = {
        .uri = "/index.html",
        .method = HTTP_GET,
        .handler = static_file_handler,
        .user_ctx = NULL
    };

    httpd_uri_t favicon_uri = {
        .uri = "/favicon.ico",
        .method = HTTP_GET,
        .handler = favicon_handler,
        .user_ctx = NULL
    };

    httpd_uri_t css_uri = {
        .uri = "/css/*",
        .method = HTTP_GET,
        .handler = static_file_handler,
        .user_ctx = NULL
    };

    httpd_uri_t js_uri = {
        .uri = "/js/*",
        .method = HTTP_GET,
        .handler = static_file_handler,
        .user_ctx = NULL
    };

    httpd_uri_t assets_uri = {
        .uri = "/assets/*",
        .method = HTTP_GET,
        .handler = static_file_handler,
        .user_ctx = NULL
    };

    httpd_uri_t manifest_uri = {
        .uri = "/manifest.json",
        .method = HTTP_GET,
        .handler = static_file_handler,
        .user_ctx = NULL
    };

    // OTA update endpoints
    httpd_uri_t ota_uri = {
        .uri = "/ota",
        .method = HTTP_GET,
        .handler = ota_handler,
        .user_ctx = NULL
    };

    httpd_uri_t ota_status_uri = {
        .uri = "/ota/status",
        .method = HTTP_GET,
        .handler = ota_status_handler,
        .user_ctx = NULL
    };

    // Register motor control endpoints
    httpd_uri_t joystick_uri = {
        .uri = "/joystick",
        .method = HTTP_POST,
        .handler = joystick_handler,
        .user_ctx = NULL
    };

    httpd_uri_t rotation_uri = {
        .uri = "/rotate",
        .method = HTTP_POST,
        .handler = rotation_handler,
        .user_ctx = NULL
    };

    httpd_uri_t control_request_uri = {
        .uri = "/control/request",
        .method = HTTP_POST,
        .handler = control_request_handler,
        .user_ctx = NULL
    };

    httpd_uri_t control_release_uri = {
        .uri = "/control/release",
        .method = HTTP_POST,
        .handler = control_release_handler,
        .user_ctx = NULL
    };

    // Register all handlers
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &index_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &index_html_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &favicon_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &css_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &js_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &assets_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &manifest_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &ota_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &ota_status_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &joystick_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &rotation_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &control_request_uri));
    ESP_ERROR_CHECK(httpd_register_uri_handler(server, &control_release_uri));

    esp_err_t cam_res = webserver_camera_register(server);
    if (cam_res != ESP_OK) {
        ESP_LOGE(TAG, "Failed to register camera handlers: %s", esp_err_to_name(cam_res));
    }

    ESP_LOGI(TAG, "All URI handlers registered successfully");
    return server;
}