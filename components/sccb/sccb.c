#include "sccb.h"
#include "common_gpio.h"

esp_err_t sccb_write(uint8_t reg_addr, uint8_t data) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (OV7670_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg_addr, true);
    i2c_master_write_byte(cmd, data, true);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}

esp_err_t sccb_read(uint8_t reg_addr, uint8_t *data) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (OV7670_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg_addr, true);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    if (ret != ESP_OK) return ret;

    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (OV7670_ADDR << 1) | I2C_MASTER_READ, true);
    i2c_master_read_byte(cmd, data, I2C_MASTER_NACK);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, I2C_MASTER_TIMEOUT_MS / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}


esp_err_t ov7670_init(void) {
    esp_err_t ret;

    // 示例：设置 COM7 寄存器为复位
    ret = sccb_write(0x12, 0x80);  // COM7: Reset
    if (ret != ESP_OK) return ret;
    vTaskDelay(pdMS_TO_TICKS(100));  // 等待复位完成

    // 设置输出格式为 RGB565
    ret = sccb_write(0x12, 0x04);  // COM7: RGB
    if (ret != ESP_OK) return ret;

    // 更多寄存器配置（分辨率、颜色格式、时序等）可根据 OV7670 datasheet 添加

    return ESP_OK;
}
