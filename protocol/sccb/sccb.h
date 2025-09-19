#ifndef SCCB_H
#define SCCB_H

#include <stdint.h>
#include "driver/gpio.h"

// SCCB 初始化
void sccb_init(gpio_num_t sda, gpio_num_t scl);

// 写寄存器
bool sccb_write(uint8_t slave_addr, uint8_t reg_addr, uint8_t data);

// 读寄存器（可选）
bool sccb_read(uint8_t slave_addr, uint8_t reg_addr, uint8_t *data);

#endif // SCCB_H
