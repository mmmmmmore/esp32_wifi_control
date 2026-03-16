#ifndef COMMON_GPIO_H
#define COMMON_GPIO_H

#pragma once

#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_err.h"

#pragma once



// ======================= ESP32-S3-CAM Pin Map =======================
// SCCB / I2C
#define CAM_PIN_SIOD         4     // SIOD / SDA
#define CAM_PIN_SIOC         5     // SIOC / SCL

// Power/reset (not used on this hardware)
#define CAM_PIN_PWDN        -1
#define CAM_PIN_RESET       -1

// Pixel data
#define CAM_PIN_Y9           16
#define CAM_PIN_Y8           17
#define CAM_PIN_Y7           18
#define CAM_PIN_Y6           12
#define CAM_PIN_Y5           10
#define CAM_PIN_Y4           8
#define CAM_PIN_Y3           9
#define CAM_PIN_Y2           11

// Sync / clock
#define CAM_PIN_VSYNC        6
#define CAM_PIN_HREF         7
#define CAM_PIN_PCLK         13
#define CAM_PIN_XCLK         15

// Compatibility aliases for legacy SCCB helpers
#define GPIO_SCL             CAM_PIN_SIOC
#define GPIO_SDA             CAM_PIN_SIOD

// ======================= 其他功能引脚 =======================
#define GPIO_LED_STATUS      42    // 状态指示灯（避免与摄像头数据线冲突）
//#define GPIO_WEBSERVER_CTRL  44     // WebServer 控制信号（注意 GPIO0 启动模式影响）

// ======================= I2C 参数定义 =======================
#define I2C_MASTER_NUM       I2C_NUM_0          // 使用 I2C 控制器编号
#define I2C_MASTER_FREQ_HZ   100000             // I2C 通信频率（100kHz）
#define I2C_MASTER_TX_BUF_DISABLE 0             // 不使用 TX 缓冲区
#define I2C_MASTER_RX_BUF_DISABLE 0             // 不使用 RX 缓冲区
#define I2C_MASTER_TIMEOUT_MS    1000           // I2C 操作超时时间（毫秒）

// ======================= LEDC 参数定义 =======================
#define LEDC_TIMER           LEDC_TIMER_0       // 使用 LEDC 定时器 0
#define LEDC_MODE            LEDC_LOW_SPEED_MODE
#define LEDC_DUTY_RES        LEDC_TIMER_10_BIT  // PWM 分辨率：10 位
#define LEDC_FREQUENCY       5000               // PWM 频率：5kHz



void common_gpio_init(void);
void ledc_init(void);
void i2c_master_init(void);

// GPIO 初始化函数
void fifo_gpio_init(void);

// 数据读取函数（可选）
//uint8_t fifo_read_byte(void);

// 控制引脚设置函数（可选）
void fifo_set_rclk(bool level);
void fifo_set_rrst(bool level);
void fifo_set_oe(bool level);

#endif
