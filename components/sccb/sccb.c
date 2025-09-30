
#include "sccb.h"
#include "common_gpio.h"
#include "driver/i2c.h"
#include "esp_log.h"



#define SCCB_ID_WRITE (OV7670_I2C_ADDR << 1 | 0)
#define SCCB_ID_READ  (OV7670_I2C_ADDR << 1 | 1)

static const char *TAG = "SCCB";

bool sccb_init(void) {
    // 配置 I2C 参数
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = PIN_SDA,
        .scl_io_num = PIN_SCL,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    esp_err_t err = i2c_param_config(I2C_MASTER_NUM, &conf);
    ESP_LOGI(TAG, "i2c_param_config returned: %d (%s)", err, esp_err_to_name(err));
    if (err != ESP_OK) {
        return false;
    }

    err = i2c_driver_install(I2C_MASTER_NUM, conf.mode,
                             I2C_MASTER_RX_BUF_DISABLE,
                             I2C_MASTER_TX_BUF_DISABLE, 0);
    ESP_LOGI(TAG, "i2c_driver_install returned: %d (%s)", err, esp_err_to_name(err));
    if (err != ESP_OK) {
        return false;
    }

    return true;
}

esp_err_t sccb_write_register(uint8_t reg_addr, uint8_t data) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    esp_err_t ret;

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, SCCB_ID_WRITE, true);
    i2c_master_write_byte(cmd, reg_addr, true);
    i2c_master_write_byte(cmd, data, true);
    i2c_master_stop(cmd);

    ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, pdMS_TO_TICKS(1000));
    i2c_cmd_link_delete(cmd);

    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Write failed: reg=0x%02X, data=0x%02X", reg_addr, data);
    }

    return ret;
}

esp_err_t sccb_read_register(uint8_t reg_addr, uint8_t *data) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    esp_err_t ret;

    // 写入寄存器地址
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, SCCB_ID_WRITE, true);
    i2c_master_write_byte(cmd, reg_addr, true);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, pdMS_TO_TICKS(1000));
    i2c_cmd_link_delete(cmd);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Write phase failed: reg=0x%02X", reg_addr);
        return ret;
    }

    // 读取数据
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, SCCB_ID_READ, true);
    i2c_master_read_byte(cmd, data, I2C_MASTER_NACK);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, pdMS_TO_TICKS(1000));
    i2c_cmd_link_delete(cmd);

    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Read failed: reg=0x%02X", reg_addr);
    }

    return ret;
}
