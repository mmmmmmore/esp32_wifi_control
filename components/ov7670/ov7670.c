#include "ov7670.h"
#include "sccb.h"
#include "ov7670_cfg.h"
#include "ov7670_gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdio.h>

#define OV7670_ADDR 0x42 >> 1  // OV7670 默认地址（写）

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

// 可选：设置窗口大小（如使用 AL422B FIFO）
void ov7670_window_set(uint16_t startX, uint16_t startY, uint16_t width, uint16_t height) {
    // 示例：设置窗口寄存器（需要根据实际寄存器定义调整）
    // sccb_write(OV7670_ADDR, REG_HSTART, startX >> 3);
    // sccb_write(OV7670_ADDR, REG_HSTOP, (startX + width) >> 3);
    // sccb_write(OV7670_ADDR, REG_VSTART, startY >> 2);
    // sccb_write(OV7670_ADDR, REG_VSTOP, (startY + height) >> 2);
}
