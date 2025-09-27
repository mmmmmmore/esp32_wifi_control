#ifndef SCCB_H
#define SCCB_H

#pragma once

#include <stdint.h>
#include <stdbool.h>

// 初始化 SCCB 通信接口
bool sccb_init(void);

// 向摄像头寄存器写入数据
bool sccb_write(uint8_t reg_addr, uint8_t data);

// 从摄像头寄存器读取数据
bool sccb_read(uint8_t reg_addr, uint8_t *data);


#endif