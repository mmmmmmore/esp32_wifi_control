#ifndef COMMON_GPIO_H
#define COMMON_GPIO_H

#pragma once

#include "driver/gpio.h"

// FIFO 控制引脚
#define PIN_WRST   GPIO_NUM_2
#define PIN_WEN    GPIO_NUM_3
#define PIN_RRST   GPIO_NUM_4
#define PIN_RCLK   GPIO_NUM_5
#define PIN_OE     GPIO_NUM_14

// FIFO 数据引脚 D0~D7
#define PIN_D0     GPIO_NUM_6
#define PIN_D1     GPIO_NUM_7
#define PIN_D2     GPIO_NUM_8
#define PIN_D3     GPIO_NUM_9
#define PIN_D4     GPIO_NUM_10
#define PIN_D5     GPIO_NUM_11
#define PIN_D6     GPIO_NUM_12
#define PIN_D7     GPIO_NUM_13

// OV7670 同步信号
#define PIN_VSYNC  GPIO_NUM_21

// SCCB 通信引脚（用于 OV7670 寄存器配置）
#define PIN_SCL    GPIO_NUM_18
#define PIN_SDA    GPIO_NUM_19

// GPIO 初始化函数
void fifo_gpio_init(void);

// 数据读取函数（可选）
//uint8_t fifo_read_byte(void);

// 控制引脚设置函数（可选）
void fifo_set_rclk(bool level);
void fifo_set_rrst(bool level);
void fifo_set_oe(bool level);

#endif
