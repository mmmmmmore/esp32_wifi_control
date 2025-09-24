#include "camera.h"
#include "global_gpio.h"
#include "sccb.h"
#include "ov7670_config.h"
#include "esp_log.h"
#include "freertos/task.h"
#include "camera_reg.h"


static const char *TAG = "camera";

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
    { REG_VSTART, 0x02 },    //
    { REG_VSTOP, 0x7A },
    { REG_VREF, 0x0A },
};

void ov7670_init_qvga_rgb565() {
    for (int i = 0; i < sizeof(ov7670_qvga_rgb565)/sizeof(ov7670_qvga_rgb565[0]); i++) {
        write_register(ov7670_qvga_rgb565[i].reg, ov7670_qvga_rgb565[i].val);
    }
}


bool camera_init(void) {
    ESP_LOGI(TAG, "Initializing camera sensor...");

    global_gpio_init();  // Initialize all GPIOs
    sccb_init();         // Initialize SCCB communication

    if (!ov7670_config()) {
        ESP_LOGE(TAG, "Failed to configure OV7670 registers");
        return false;
    }

    // Optional: check VSYNC signal
    if (gpio_get_level(GPIO_VSYNC) == 0) {
        ESP_LOGW(TAG, "VSYNC signal not detected");
    }

    ESP_LOGI(TAG, "Camera sensor initialization complete.");
    return true;
}
