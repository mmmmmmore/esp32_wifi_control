#pragma once

#include <stdint.h>
#include <stdbool.h>

// 图像尺寸结构体
typedef struct {
    uint16_t width;
    uint16_t height;
} image_size_t;

// 初始化采集任务（可选）
void ov7670_handler_init(void);

// 采集一帧图像，返回图像缓冲区指针和大小
uint8_t* ov7670_capture_frame(const image_size_t* size, size_t* out_len);
