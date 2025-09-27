#include "capture_control.h"
#include "ov7670_handler.h"  // 假设你从这里读取图像数据

static bool capture_enabled = false;

void capture_control_set(bool enable) {
    capture_enabled = enable;
}

bool capture_control_get(void) {
    return capture_enabled;
}

void fifo_read_frame(uint8_t *buffer, size_t size) {
    // 这里假设 ov7670_handler 提供了读取图像的接口
    ov7670_read_frame(buffer, size);
}
