#include "camera.h"
#include "common_gpio.h"
#include "sccb.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "camera_reg.h"
#include "driver/i2c.h"
//#include "i2c_config.h"

#include "driver/gpio.h"
// static const char *TAG = "camera";



#define VSYNC_GPIO GPIO_NUM_21  // 根据你的定义修改

static const char *TAG = "VSYNC_DEBUG";

void vsync_debug_task(void *arg) {
    gpio_set_direction(VSYNC_GPIO, GPIO_MODE_INPUT);

    while (1) {
        int high_count = 0;
        int low_count = 0;

        for (int i = 0; i < 100; i++) {
            int level = gpio_get_level(VSYNC_GPIO);
            if (level) high_count++;
            else low_count++;
            vTaskDelay(pdMS_TO_TICKS(1));  // 每次采样间隔 1ms
        }

        ESP_LOGI(TAG, "VSYNC GPIO%d: High=%d, Low=%d", VSYNC_GPIO, high_count, low_count);

        vTaskDelay(pdMS_TO_TICKS(1000));  // 每秒打印一次
    }
}




void i2c_master_init() {
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = PIN_SDA,
        .scl_io_num = PIN_SCL,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };
    i2c_param_config(I2C_MASTER_NUM, &conf);
    i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);
}


esp_err_t write_register(uint8_t reg, uint8_t val) {
    uint8_t data[2] = { reg, val };
    return i2c_master_write_to_device(
        I2C_MASTER_NUM, 
        OV7670_I2C_ADDR, 
        data, sizeof(data), 
        1000 / portTICK_PERIOD_MS
    );
}




const struct regval_list ov7670_qvga_rgb565[] = {
    { REG_COM7, 0x80 },     //reverse
    { REG_CLKRC, 0x80 },    //use external clk signal
    { REG_COM11, 0x0A },    //use BD50ST and expourse time smaller
    { REG_COM7, 0x04 },     //output RGB mode
    { REG_RGB444, 0x00 },    //RGB44 disable
    { REG_COM15, 0xD0 },    //output 00-FF, RGB565 match with RGB444 low
    { REG_COM1, 0x00 },    ///disable general control 
    { REG_COM9, 0x6A },     //128X gain, 
    { REG_COM3, 0x04 },    //enable com3 
    { REG_COM14, 0x19 },    // SCW maunal adjust, /2
    { REG_SCALING_XSC, 0x3A },    //default value
    { REG_SCALING_YSC, 0x35 },    //default value
    { REG_SCALING_DCWCTR, 0x03 },    //horizen 8-->1
    { REG_HSTART, 0x16 },        // low bit 110
    { REG_HSTOP, 0x04 },        // low bit 100
    { REG_HREF, 0x24 },        //100 110 match with HSTART and HSTOP
    { REG_VSTART, 0x02 },    // 11
    { REG_VSTOP, 0x7A },    //11
    { REG_VREF, 0x0A },    //
};

void ov7670_init_qvga_rgb565() {
    for (int i = 0; i < sizeof(ov7670_qvga_rgb565)/sizeof(ov7670_qvga_rgb565[0]); i++) {
        write_register(ov7670_qvga_rgb565[i].reg, ov7670_qvga_rgb565[i].val);
    }
}


bool ov7670_config(void){
    ov7670_init_qvga_rgb565();
    return true;
}


bool camera_init(void) {
    ESP_LOGI("camera: ", "Initializing camera sensor...");

    fifo_gpio_init();      // Initialize all GPIOs
    sccb_init();         // Initialize SCCB communication


    sccb_write_register(0x12, 0x80);
    xTaskDelay(pdMS_TO_TICKS(10));
    uint8_t com10 = sccb_read_register(0x15);
    ESP_LOGI("CAMERA", "COM10 = 0x %02X", com10);
    // xTaskCreate(vsync_debug_task, "vsync_debug_task", 2048, NULL, 5, NULL);
    
    if (!ov7670_config()) {
        ESP_LOGE("camera: ", "Failed to configure OV7670 registers");
        return false;
    }

    // Optional: check VSYNC signal
    if (gpio_get_level(PIN_VSYNC) == 0) {
        ESP_LOGW("camera: ", "VSYNC signal not detected");
    }

    ESP_LOGI("camera: ", "Camera sensor initialization complete.");
    return true;
}
