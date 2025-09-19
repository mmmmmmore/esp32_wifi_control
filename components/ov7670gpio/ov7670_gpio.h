
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#ifndef OV7670_GPIO_H
#define OV7670_GPIO_H


//define the I2C pin
#define OV7670_I2C_SDA 8
#define OV7670_I2C_SCL 9

#define OV7670_DATA_GPIO_NUM 8



//define the D0-D7 to GPIO
#define OV7670_FIFO_D0 0
#define OV7670_FIFO_D1 1
#define OV7670_FIFO_D2 2
#define OV7670_FIFO_D3 3
#define OV7670_FIFO_D4 4
#define OV7670_FIFO_D5 5
#define OV7670_FIFO_D6 6
#define OV7670_FIFO_D7 7

static const gpio_num_t ov7670_data_pins[OV7670_DATA_GPIO_NUM] = {
    OV7670_FIFO_D0,
    OV7670_FIFO_D1,
    OV7670_FIFO_D2,
    OV7670_FIFO_D3,
    OV7670_FIFO_D4,
    OV7670_FIFO_D5,
    OV7670_FIFO_D6,
    OV7670_FIFO_D7
};



//define control pin
#define OV7670_WRST 14
#define OV7670_WEN 15
#define OV7670_RRST 13
#define OV7670_RCLK 16

#define OV7670_VSYNC 10

void ov7670_gpio_init();

#endif //OV7670_GPIO_H