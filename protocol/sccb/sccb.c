#include "sccb.h"
#include "global_gpio.h"
#include "driver/gpio.h"
#include "freertos/task.h"

#define SCCB_DELAY_US 5

static void sccb_delay() {
    ets_delay_us(SCCB_DELAY_US);
}

static void sccb_start() {
    gpio_set_level(GPIO_SDA, 1);
    gpio_set_level(GPIO_SCL, 1);
    sccb_delay();
    gpio_set_level(GPIO_SDA, 0);
    sccb_delay();
    gpio_set_level(GPIO_SCL, 0);
}

static void sccb_stop() {
    gpio_set_level(GPIO_SDA, 0);
    gpio_set_level(GPIO_SCL, 1);
    sccb_delay();
    gpio_set_level(GPIO_SDA, 1);
    sccb_delay();
}

static bool sccb_write_byte(uint8_t data) {
    for (int i = 0; i < 8; i++) {
        gpio_set_level(GPIO_SDA, (data >> (7 - i)) & 0x01);
        sccb_delay();
        gpio_set_level(GPIO_SCL, 1);
        sccb_delay();
        gpio_set_level(GPIO_SCL, 0);
    }

    // ACK bit
    gpio_set_direction(GPIO_SDA, GPIO_MODE_INPUT);
    gpio_set_level(GPIO_SCL, 1);
    sccb_delay();
    bool ack = !gpio_get_level(GPIO_SDA);
    gpio_set_level(GPIO_SCL, 0);
    gpio_set_direction(GPIO_SDA, GPIO_MODE_OUTPUT);
    return ack;
}

bool sccb_write(uint8_t reg_addr, uint8_t data) {
    sccb_start();
    if (!sccb_write_byte(0x42)) return false;  // OV7670 write address
    if (!sccb_write_byte(reg_addr)) return false;
    if (!sccb_write_byte(data)) return false;
    sccb_stop();
    return true;
}

bool sccb_init(void) {
    // GPIO 已在 global_gpio_init() 中初始化
    return true;
}
