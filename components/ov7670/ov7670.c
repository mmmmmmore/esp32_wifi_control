#include "ov7670.h"
#include "sccb.h"
#include "ov7670_cfg.h"
#include "ov7670_gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>

#define OV7670_ADDR 0x42 >> 1  // OV7670 默认地址（写）

#define SCCB_ADDR     0x42
//
//// AL422B FIFO control pins
#define OV7670_WRST     14
#define OV7670_WREN     15
#define OV7670_VSYNC    10


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
/*


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

*/

//define control pin
#define OV7670_WRST 14
#define OV7670_WEN 15
#define OV7670_RRST 13
#define OV7670_RCLK 16

#define OV7670_VSYNC 10


/*
void ov7670_init(void) {
    // 初始化 GPIO 和 SCCB
    ov7670_gpio_init();
    sccb_init(OV7670_I2C_SDA, OV7670_I2C_SCL);

    // 复位摄像头
    sccb_write(OV7670_ADDR, 0x12, 0x80);
    vTaskDelay(pdMS_TO_TICKS(100));

    // 写入初始化寄存器表
    for (size_t i = 0; i < ov7670_init_reg_tbl_size; ++i) {
        if (!sccb_write(OV7670_ADDR, ov7670_init_reg_tbl[i].reg, ov7670_init_reg_tbl[i].val)) {
            printf("寄存器写入失败: 0x%02X\n", ov7670_init_reg_tbl[i].reg);
        }
        vTaskDelay(pdMS_TO_TICKS(2));  // 可调节延迟
    }

    printf("OV7670 初始化完成。\n");
}

*/
// 可选：设置窗口大小（如使用 AL422B FIFO）
void ov7670_window_set(uint16_t startX, uint16_t startY, uint16_t width, uint16_t height) {
    // 示例：设置窗口寄存器（需要根据实际寄存器定义调整）
    // sccb_write(OV7670_ADDR, REG_HSTART, startX >> 3);
    // sccb_write(OV7670_ADDR, REG_HSTOP, (startX + width) >> 3);
    // sccb_write(OV7670_ADDR, REG_VSTART, startY >> 2);
    // sccb_write(OV7670_ADDR, REG_VSTOP, (startY + height) >> 2);
}
