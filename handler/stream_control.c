#include "stream_control.h"
#include "esp_log.h"

static bool capture_enabled = false;

void capture_control_set(bool enabled) {
    ESP_LOGI("stream_control", "Capture set to: %s",enabled ? "ON":"OFF");
    capture_enabled = enabled;
}

bool capture_control_get(void) {
    ESP_LOGI("stream_control", "Capture set to: %s", capture_enabled ? "ON" : "OFF");
    return capture_enabled;
}
