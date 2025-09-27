#include "common_gpio.h"




void fifo_gpio_init(void) {
    gpio_config_t io_conf = {0};

    // 控制引脚配置为输出
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << PIN_WRST) | (1ULL << PIN_WEN) |
                           (1ULL << PIN_RRST) | (1ULL << PIN_RCLK) |
                           (1ULL << PIN_OE);
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&io_conf);

    // 数据引脚配置为输入
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL << PIN_D0) | (1ULL << PIN_D1) | (1ULL << PIN_D2) |
                           (1ULL << PIN_D3) | (1ULL << PIN_D4) | (1ULL << PIN_D5) |
                           (1ULL << PIN_D6) | (1ULL << PIN_D7);
    gpio_config(&io_conf);

    // VSYNC 配置为输入（可用于中断）
    gpio_set_direction(PIN_VSYNC, GPIO_MODE_INPUT);

    // SCCB 引脚配置为输入输出（开漏）
    io_conf.mode = GPIO_MODE_INPUT_OUTPUT_OD;
    io_conf.pin_bit_mask = (1ULL << PIN_SCL) | (1ULL << PIN_SDA);
    gpio_config(&io_conf);
}

// 示例：读取一字节数据
//uint8_t fifo_read_byte(void) {
//    uint8_t data = 0;
//    data |= gpio_get_level(PIN_D0) << 0;
//    data |= gpio_get_level(PIN_D1) << 1;
//    data |= gpio_get_level(PIN_D2) << 2;
//    data |= gpio_get_level(PIN_D3) << 3;
//    data |= gpio_get_level(PIN_D4) << 4;
//    data |= gpio_get_level(PIN_D5) << 5;
//    data |= gpio_get_level(PIN_D6) << 6;
//   data |= gpio_get_level(PIN_D7) << 7;
//    return data;
//}

// 示例：控制引脚设置
void fifo_set_rclk(bool level) {
    gpio_set_level(PIN_RCLK, level);
}

void fifo_set_rrst(bool level) {
    gpio_set_level(PIN_RRST, level);
}

void fifo_set_oe(bool level) {
    gpio_set_level(PIN_OE, level);
}
