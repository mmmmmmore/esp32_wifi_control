#include "stream_control.h"

static bool capture_enabled = false;

void capture_control_set(bool enabled) {
    capture_enabled = enabled;
}

bool capture_control_get(void) {
    return capture_enabled;
}
