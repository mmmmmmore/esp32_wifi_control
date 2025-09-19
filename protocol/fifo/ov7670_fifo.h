#ifndef OV7670_FIFO_H
#define OV7670_FIFO_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// 初始化 FIFO 控制引脚
void fifo_init(void);

// 复位 FIFO 读指针
void fifo_reset_read_pointer(void);

// 读取一个字节（8 位像素数据）
uint8_t fifo_read_byte(void);

// 读取一帧图像（用户可自定义缓冲区大小）
void fifo_read_frame(uint8_t *buffer, size_t size);

#endif // OV7670_FIFO_H
