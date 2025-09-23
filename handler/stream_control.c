#include "stream_control.h"
#include "esp_log.h"

static bool capture_enabled = false;

void capture_control_set(bool enabled) {
    capture_enabled = enabled;
}

bool capture_control_get(void) {
    return capture_enabled;
    ESP_LOGI("stream_control", "Capture set to: %s", enabled ? "ON" : "OFF");

}
