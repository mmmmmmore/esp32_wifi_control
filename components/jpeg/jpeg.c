#include "jpeg.h"
#include "tiny_jpeg.h"
#include <stdlib.h>
#include <string.h>

uint8_t* jpeg_encode_rgb565(const uint8_t* rgb_data, size_t rgb_len, uint16_t width, uint16_t height, size_t* jpeg_len) {
    if (!rgb_data || rgb_len == 0 || width == 0 || height == 0 || !jpeg_len) {
        return NULL;
    }

    // 估算 JPEG 输出缓冲区大小（压缩率约为 1/2 到 1/10）
    size_t max_jpeg_size = rgb_len / 2;
    uint8_t* jpeg_buffer = malloc(max_jpeg_size);
    if (!jpeg_buffer) {
        return NULL;
    }

    // TinyJPEG 要求输入为 RGB888 格式
    uint8_t* rgb888 = malloc(width * height * 3);
    if (!rgb888) {
        free(jpeg_buffer);
        return NULL;
    }

    // 将 RGB565 转换为 RGB888
    for (size_t i = 0; i < width * height; i++) {
        uint16_t pixel = ((uint16_t*)rgb_data)[i];
        uint8_t r = (pixel >> 11) & 0x1F;
        uint8_t g = (pixel >> 5) & 0x3F;
        uint8_t b = pixel & 0x1F;

        rgb888[i * 3 + 0] = r << 3;
        rgb888[i * 3 + 1] = g << 2;
        rgb888[i * 3 + 2] = b << 3;
    }

    // 调用 TinyJPEG 编码函数
    int result = tinyjpeg_encode(jpeg_buffer, max_jpeg_size, rgb888, width, height, 3); // quality = 3 (best)

    free(rgb888);

    if (result <= 0) {
        free(jpeg_buffer);
        return NULL;
    }

    *jpeg_len = result;
    return jpeg_buffer;
}
