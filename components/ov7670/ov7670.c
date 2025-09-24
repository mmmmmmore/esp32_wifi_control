#include "sccb.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "ov7670_config";

bool ov7670_config(void) {
    ESP_LOGI(TAG, "Resetting OV7670...");
    if (!sccb_write(0x12, 0x80)) return false;  // COM7: Reset
    vTaskDelay(pdMS_TO_TICKS(10));

    ESP_LOGI(TAG, "Configuring OV7670 for RGB565 QVGA...");

    // 设置输出格式为 RGB565
    if (!sccb_write(0x12, 0x14)) return false;  // COM7: RGB output
    if (!sccb_write(0x40, 0xd0)) return false;  // COM15: RGB565

    // 设置分辨率为 QVGA（320x240）
    if (!sccb_write(0x11, 0x01)) return false;  // CLKRC: Internal clock prescaler
    if (!sccb_write(0x0C, 0x00)) return false;  // COM3: No scaling
    if (!sccb_write(0x3E, 0x00)) return false;  // COM14: No scaling
    if (!sccb_write(0x70, 0x3A)) return false;  // Scaling X
    if (!sccb_write(0x71, 0x35)) return false;  // Scaling Y
    if (!sccb_write(0x72, 0x11)) return false;  // Scaling control
    if (!sccb_write(0x73, 0xf0)) return false;  // Scaling control
    if (!sccb_write(0xa2, 0x02)) return false;  // Pixel clock delay

    // 图像窗口设置（QVGA）
    if (!sccb_write(0x17, 0x16)) return false;  // HSTART
    if (!sccb_write(0x18, 0x04)) return false;  // HSTOP
    if (!sccb_write(0x32, 0x80)) return false;  // HREF
    if (!sccb_write(0x19, 0x02)) return false;  // VSTART
    if (!sccb_write(0x1A, 0x7a)) return false;  // VSTOP
    if (!sccb_write(0x03, 0x0a)) return false;  // VREF

    // Gamma curve and color matrix (optional tuning)
    if (!sccb_write(0x7a, 0x20)) return false;
    if (!sccb_write(0x7b, 0x10)) return false;
    if (!sccb_write(0x7c, 0x1e)) return false;
    if (!sccb_write(0x7d, 0x35)) return false;
    if (!sccb_write(0x7e, 0x5a)) return false;
    if (!sccb_write(0x7f, 0x69)) return false;
    if (!sccb_write(0x80, 0x76)) return false;
    if (!sccb_write(0x81, 0x80)) return false;
    if (!sccb_write(0x82, 0x88)) return false;
    if (!sccb_write(0x83, 0x8f)) return false;
    if (!sccb_write(0x84, 0x96)) return false;
    if (!sccb_write(0x85, 0xa3)) return false;
    if (!sccb_write(0x86, 0xaf)) return false;
    if (!sccb_write(0x87, 0xc4)) return false;
    if (!sccb_write(0x88, 0xd7)) return false;
    if (!sccb_write(0x89, 0xe8)) return false;

    ESP_LOGI(TAG, "OV7670 configuration complete.");
    return true;
}
