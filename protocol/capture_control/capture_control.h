#ifndef CAPTURE_CONTROL_H
#define CAPTURE_CONTROL_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// 控制是否启用图像采集
void capture_control_set(bool enable);
bool capture_control_get(void);

// 从 FIFO 中读取一帧图像数据
void fifo_read_frame(uint8_t *buffer, size_t size);

#endif // CAPTURE_CONTROL_H
