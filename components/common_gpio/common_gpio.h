#ifndef COMMON_GPIO_H
#define COMMON_GPIO_H

#pragma once

#include "driver/gpio.h"


#define OV7670_I2C_ADDR 0x21  // OV7670 write address

// FIFO 控制引脚
#define PIN_WRST   GPIO_NUM_12
#define PIN_WEN    GPIO_NUM_13
#define PIN_RRST   GPIO_NUM_11
#define PIN_RCLK   GPIO_NUM_14
#define PIN_OE     GPIO_NUM_10

// FIFO 数据引脚 D0~D7
#define PIN_D0     GPIO_NUM_4
#define PIN_D1     GPIO_NUM_5
#define PIN_D2     GPIO_NUM_6
#define PIN_D3     GPIO_NUM_7
#define PIN_D4     GPIO_NUM_15
#define PIN_D5     GPIO_NUM_16
#define PIN_D6     GPIO_NUM_17
#define PIN_D7     GPIO_NUM_18

// OV7670 同步信号
#define PIN_VSYNC  GPIO_NUM_9

// SCCB 通信引脚（用于 OV7670 寄存器配置）
#define PIN_SCL    GPIO_NUM_3
#define PIN_SDA    GPIO_NUM_8

#define I2C_MASTER_NUM I2C_NUM_0
//#define I2C_MASTER_SCL_IO PIN_SCL
//#define I2C_MASTER_SDA_IO PIN_SDA
#define I2C_MASTER_FREQ_HZ 100000
#define I2C_MASTER_TX_BUF_DISABLE 0
#define I2C_MASTER_RX_BUF_DISABLE 0

// GPIO 初始化函数
void fifo_gpio_init(void);

// 数据读取函数（可选）
//uint8_t fifo_read_byte(void);

esp_err_t sccb_read_register(uint8_t reg_addr, uint8_t *data);
esp_err_t sccb_write_register(uint8_t reg_addr, uint8_t data);


// 控制引脚设置函数（可选）
void fifo_set_rclk(bool level);
void fifo_set_rrst(bool level);
void fifo_set_oe(bool level);

#endif




