
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

// SCCB (I2C) configuration
//#define SCCB_SDA_GPIO 8
//#define SCCB_SCL_GPIO 9
#define SCCB_ADDR     0x42
//
//// AL422B FIFO control pins
#define OV7670_WRST     14
#define OV7670_WREN     15
#define OV7670_VSYNC    10

static const char *TAG = "OV7670";

// I2C initialization for SCCB
void sccb_init() {
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = SCCB_SDA_GPIO,
        .scl_io_num = SCCB_SCL_GPIO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000
    };
    ESP_ERROR_CHECK(i2c_param_config(I2C_NUM_0, &conf));
    ESP_ERROR_CHECK(i2c_driver_install(I2C_NUM_0, conf.mode, 0, 0, 0));
}

// Write register via SCCB
esp_err_t sccb_write(uint8_t reg, uint8_t data) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, SCCB_ADDR, true);
    i2c_master_write_byte(cmd, reg, true);
    i2c_master_write_byte(cmd, data, true);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(cmd);
    return ret;
}

// Read register via SCCB
uint8_t sccb_read(uint8_t reg) {
    uint8_t data = 0;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, SCCB_ADDR, true);
    i2c_master_write_byte(cmd, reg, true);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_NUM_0, cmd, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(cmd);

    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, SCCB_ADDR | 0x01, true);
    i2c_master_read_byte(cmd, &data, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_NUM_0, cmd, pdMS_TO_TICKS(100));
    i2c_cmd_link_delete(cmd);
    return data;
}

// VSYNC interrupt handler
static int ov_sta = 0;
void IRAM_ATTR vsync_isr_handler(void *arg) {
    if (ov_sta < 2) {
        if (ov_sta == 0) {
            gpio_set_level(OV7670_WRST, 0);
            gpio_set_level(OV7670_WRST, 1);
            gpio_set_level(OV7670_WREN, 1);
        } else {
            gpio_set_level(OV7670_WREN, 0);
            gpio_set_level(OV7670_WRST, 0);
            gpio_set_level(OV7670_WRST, 1);
        }
        ov_sta++;
    }
}

// GPIO initialization
void ov7670_gpio_init() {
    gpio_config_t io_conf = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = (1ULL << OV7670_WRST) | (1ULL << OV7670_WREN),
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);

    gpio_set_level(OV7670_WRST, 1);
    gpio_set_level(OV7670_WREN, 0);

    gpio_config_t vsync_conf = {
        .mode = GPIO_MODE_INPUT,
        .pin_bit_mask = (1ULL << OV7670_VSYNC),
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_POSEDGE
    };
    gpio_config(&vsync_conf);
    gpio_install_isr_service(0);
    gpio_isr_handler_add(OV7670_VSYNC, vsync_isr_handler, NULL);

    // ov7670 数据引脚属性定义
    for (int i =0; i < OV7670_DATA_GPIO_NUM; i++){
        gpio_config_t data_conf = {
            .mode = GPIO_MODE_INPUT,
            .pin_bit_mask = (1ULL << ov7670_data_pins[i]),
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
            .intr_type = GPIO_INTR_DISABLE
        };
        gpio_config(&data_conf)
    }

}





// OV7670 initialization
esp_err_t ov7670_init() {
    sccb_init();
    ov7670_gpio_init();

    sccb_write(0x12, 0x80); // Reset
    vTaskDelay(pdMS_TO_TICKS(50));

    uint8_t midh = sccb_read(0x0b);
    uint8_t midl = sccb_read(0x0a);
    if (midh != 0x73 || midl != 0x76) {
        ESP_LOGE(TAG, "OV7670 not detected");
        return ESP_FAIL;
    }

    // Example register configuration
    sccb_write(0x11, 0x01); // Clock settings
    sccb_write(0x6b, 0x0a); // PLL settings

    ESP_LOGI(TAG, "OV7670 initialized");
    return ESP_OK;
}

// Brightness control
void ov7670_set_brightness(uint8_t level) {
    uint8_t val = 0x00;
    switch (level) {
        case 0: val = 0xb0; break;
        case 1: val = 0x98; break;
        case 2: val = 0x00; break;
        case 3: val = 0x18; break;
        case 4: val = 0x30; break;
    }
    sccb_write(0x55, val);
}

// Contrast control
void ov7670_set_contrast(uint8_t level) {
    uint8_t val = 0x40;
    switch (level) {
        case 0: val = 0x30; break;
        case 1: val = 0x38; break;
        case 2: val = 0x40; break;
        case 3: val = 0x50; break;
        case 4: val = 0x60; break;
    }
    sccb_write(0x56, val);
}

// Special effects
void ov7670_set_effect(uint8_t effect) {
    uint8_t reg3a = 0x04, reg67 = 0xc0, reg68 = 0x80;
    switch (effect) {
        case 1: reg3a = 0x24; reg67 = 0x80; reg68 = 0x80; break;
        case 2: reg3a = 0x14; reg67 = 0x80; reg68 = 0x80; break;
        case 3: reg3a = 0x14; reg67 = 0xc0; reg68 = 0x80; break;
        case 4: reg3a = 0x14; reg67 = 0x40; reg68 = 0x40; break;
        case 5: reg3a = 0x14; reg67 = 0x80; reg68 = 0xc0; break;
        case 6: reg3a = 0x14; reg67 = 0xa0; reg68 = 0x40; break;
    }
    sccb_write(0x3a, reg3a);
    sccb_write(0x68, reg67);
    sccb_write(0x67, reg68);
}
