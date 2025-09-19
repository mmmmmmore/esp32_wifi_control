
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



void ov7670_gpio_init();

#endif //OV7670_GPIO_H