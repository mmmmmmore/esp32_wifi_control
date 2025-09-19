#ifndef OV7670_H
#define OV7670_H

#include <stdint.h>
#include <stdbool.h>

// 初始化摄像头
void ov7670_init(void);

// 可选：设置窗口大小（如使用 AL422B FIFO）
void ov7670_window_set(uint16_t startX, uint16_t startY, uint16_t width, uint16_t height);

#endif // OV7670_H
