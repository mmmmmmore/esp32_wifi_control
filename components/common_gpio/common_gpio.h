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

// ======================= DRV8833 电机驱动（2 x DRV8833 -> 4 motors） =======================
// DRV8833-Board_1: Motor A (Motor1) and Motor B (Motor2)
// DRV8833-Board_2: Motor C (Motor3) and Motor D (Motor4)
// 
// WARNING: GPIO6-11 are typically used for SPI flash. Ensure your ESP32-S3 board
// supports using these pins (e.g., boards with external PSRAM or OPI flash).
//
// Control Mode: Each motor uses two inputs (IN1/IN2) for direction and speed control.
// Apply PWM to IN1 or IN2 depending on desired rotation direction.

/* Motor 1 (Motor A on DRV8833-Board_1) */
#define GPIO_MOTOR1_IN1     19   // AIN1 on Board_1
#define GPIO_MOTOR1_IN2     20   // AIN2 on Board_1

/* Motor 2 (Motor B on DRV8833-Board_1) */
#define GPIO_MOTOR2_IN1     14   // BIN1 on Board_1
#define GPIO_MOTOR2_IN2     21   // BIN2 on Board_1

/* Motor 3 (Motor C on DRV8833-Board_2) */
#define GPIO_MOTOR3_IN1     1    // AIN1 on Board_2
#define GPIO_MOTOR3_IN2     2    // AIN2 on Board_2

/* Motor 4 (Motor D on DRV8833-Board_2) */
#define GPIO_MOTOR4_IN1     47   // BIN1 on Board_2
#define GPIO_MOTOR4_IN2     48   // BIN2 on Board_2

// Shared nSLEEP/STBY pin for both DRV8833 boards
#define GPIO_MOTOR_STBY     41

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

// 可选：电机 PWM 通道定义（根据需要使用）
#define LEDC_CHANNEL_MOTOR1_A  LEDC_CHANNEL_0
#define LEDC_CHANNEL_MOTOR1_B  LEDC_CHANNEL_1
#define LEDC_CHANNEL_MOTOR2_A  LEDC_CHANNEL_2
#define LEDC_CHANNEL_MOTOR2_B  LEDC_CHANNEL_3



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

/* ------------------------------------------------------------------
 * Compatibility aliases for existing motor abstraction code
 *
 * DRV8833 uses IN1/IN2 for each motor channel. For compatibility
 * with existing code that expects separate PWM pins, we map:
 * - HBH (High-side Bridge High) -> IN1
 * - HBL (High-side Bridge Low)  -> IN2
 * - PWM -> IN1 (apply PWM signal to IN1 for forward, or IN2 for reverse)
 *
 * NOTE: GPIO6-11 are used for SPI flash on some ESP32-S3 boards.
 * Verify your specific board supports using these pins for GPIO.
 * ------------------------------------------------------------------ */

/* Motor 1 (alias) */
#define M1_HBH  GPIO_MOTOR1_IN1
#define M1_HBL  GPIO_MOTOR1_IN2
#define M1_PWM  GPIO_MOTOR1_IN1    // PWM applied to IN1

/* Motor 2 (alias) */
#define M2_HBH  GPIO_MOTOR2_IN1
#define M2_HBL  GPIO_MOTOR2_IN2
#define M2_PWM  GPIO_MOTOR2_IN1    // PWM applied to IN1

/* Motor 3 (alias) */
#define M3_HBH  GPIO_MOTOR3_IN1
#define M3_HBL  GPIO_MOTOR3_IN2
#define M3_PWM  GPIO_MOTOR3_IN1    // PWM applied to IN1

/* Motor 4 (alias) */
#define M4_HBH  GPIO_MOTOR4_IN1
#define M4_HBL  GPIO_MOTOR4_IN2
#define M4_PWM  GPIO_MOTOR4_IN1    // PWM applied to IN1

#endif
