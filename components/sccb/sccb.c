#include "sccb.h"
#include "common_gpio.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "camera_reg.h"
#include "esp_rom_sys.h"
#include "driver/i2c.h"

#define I2C_MASTER_NUM I2C_NUM_0
#define I2C_MASTER_SCL_IO PIN_SCL
#define I2C_MASTER_SDA_IO PIN_SDA
#define I2C_MASTER_FREQ_HZ 100000
#define I2C_MASTER_TX_BUF_DISABLE 0
#define I2C_MASTER_RX_BUF_DISABLE 0

#define SCCB_DELAY_US 5
#define SCCB_ID_WRITE (OV7670_I2C_ADDR << 1 | 0)        //0x42
#define SCCB_ID_READ  (OV7670_I2C_ADDR << 1 | 1)        //0x43

static void sccb_delay() {
    esp_rom_delay_us(SCCB_DELAY_US);
}

static void sccb_start() {
    gpio_set_level(PIN_SDA, 1);
    gpio_set_level(PIN_SCL, 1);
    sccb_delay();
    gpio_set_level(PIN_SDA, 0);
    sccb_delay();
    gpio_set_level(PIN_SCL, 0);
}

static void sccb_stop() {
    gpio_set_level(PIN_SDA, 0);
    gpio_set_level(PIN_SCL, 1);
    sccb_delay();
    gpio_set_level(PIN_SDA, 1);
    sccb_delay();
}

static bool sccb_write_byte(uint8_t data) {
    for (int i = 0; i < 8; i++) {
        gpio_set_level(PIN_SDA, (data >> (7 - i)) & 0x01);
        sccb_delay();
        gpio_set_level(PIN_SCL, 1);
        sccb_delay();
        gpio_set_level(PIN_SCL, 0);
    }

    // ACK bit
    gpio_set_direction(PIN_SDA, GPIO_MODE_INPUT);
    gpio_set_level(PIN_SCL, 1);
    sccb_delay();
    bool ack = !gpio_get_level(PIN_SDA);
    gpio_set_level(PIN_SCL, 0);
    gpio_set_direction(PIN_SDA, GPIO_MODE_OUTPUT);
    return ack;
}

static uint8_t sccb_read_byte(bool ack) {
    uint8_t data = 0;
    gpio_set_direction(PIN_SDA, GPIO_MODE_INPUT);

    for (int i = 0; i < 8; i++) {
        gpio_set_level(PIN_SCL, 1);
        sccb_delay();
        data <<= 1;
        data |= gpio_get_level(PIN_SDA);
        gpio_set_level(PIN_SCL, 0);
        sccb_delay();
    }

    gpio_set_direction(PIN_SDA, GPIO_MODE_OUTPUT);
    gpio_set_level(PIN_SDA, ack ? 0 : 1);
    gpio_set_level(PIN_SCL, 1);
    sccb_delay();
    gpio_set_level(PIN_SCL, 0);
    gpio_set_level(PIN_SDA, 1);
    return data;
}

bool sccb_write(uint8_t reg_addr, uint8_t data) {
    sccb_start();
    if (!sccb_write_byte(SCCB_ID_WRITE)) return false;
    if (!sccb_write_byte(reg_addr)) return false;
    if (!sccb_write_byte(data)) return false;
    sccb_stop();
    return true;
}

bool sccb_read(uint8_t reg_addr, uint8_t *data) {
    sccb_start();
    if (!sccb_write_byte(SCCB_ID_WRITE)) return false;
    if (!sccb_write_byte(reg_addr)) return false;
    sccb_stop();

    sccb_start();
    if (!sccb_write_byte(SCCB_ID_READ)) return false;
    *data = sccb_read_byte(false);
    sccb_stop();
    return true;
}



bool sccb_init(void) {
    // 初始化 GPIO（如果未在其他地方初始化）
    gpio_set_direction(PIN_SCL, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_SDA, GPIO_MODE_OUTPUT);
    gpio_set_level(PIN_SCL, 1);
    gpio_set_level(PIN_SDA, 1);

    // 配置 I2C 参数
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };
    esp_err_t err = i2c_param_config(I2C_MASTER_NUM, &conf);
    if (err != ESP_OK) {
        return false;
    }

    // 安装 I2C 驱动
    err = i2c_driver_install(I2C_MASTER_NUM, conf.mode,
                             I2C_MASTER_RX_BUF_DISABLE,
                             I2C_MASTER_TX_BUF_DISABLE, 0);
    if (err != ESP_OK) {
        return false;
    }

    return true;
}

