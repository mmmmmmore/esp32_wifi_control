#include "jpeg_encoder.h"
#include <stdlib.h>
#include <string.h>

// 示例：JPEG 编码库头文件（请根据实际使用的库替换）
#include "tinyjpeg.h"  // 或者你集成的其他 JPEG 编码库

// 内部 JPEG 编码器上下文（根据库而定）
static struct jpeg_compress_struct encoder;
static struct jpeg_error_mgr jerr;

uint8_t* jpeg_encode_rgb565(const uint8_t* rgb_data, size_t rgb_len, uint16_t width, uint16_t height, size_t* jpeg_len) {
    if (!rgb_data || rgb_len == 0 || width == 0 || height == 0 || !jpeg_len) {
        return NULL;
    }

    // 估算 JPEG 输出缓冲区大小（通常压缩率为 1/2 到 1/10）
    size_t max_jpeg_size = rgb_len / 2;
    uint8_t* jpeg_buffer = malloc(max_jpeg_size);
    if (!jpeg_buffer) {
        return NULL;
    }

    // 初始化 JPEG 编码器（根据库而定）
    encoder.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&encoder);

    // 设置输出缓冲区
    jpeg_mem_dest(&encoder, &jpeg_buffer, &max_jpeg_size);

    // 设置图像参数
    encoder.image_width = width;
    encoder.image_height = height;
    encoder.input_components = 3; // RGB
    encoder.in_color_space = JCS_RGB;

    jpeg_set_defaults(&encoder);
    jpeg_set_quality(&encoder, 75, TRUE); // 可调节质量

    jpeg_start_compress(&encoder, TRUE);

    // 将 RGB565 转换为 RGB888 并写入编码器
    JSAMPROW row_pointer[1];
    uint8_t* rgb888_row = malloc(width * 3);
    if (!rgb888_row) {
        jpeg_destroy_compress(&encoder);
        free(jpeg_buffer);
        return NULL;
    }

    while (encoder.next_scanline < encoder.image_height) {
        for (int x = 0; x < width; x++) {
            uint16_t pixel = ((uint16_t*)rgb_data)[encoder.next_scanline * width + x];
            uint8_t r = (pixel >> 11) & 0x1F;
            uint8_t g = (pixel >> 5) & 0x3F;
            uint8_t b = pixel & 0x1F;

            rgb888_row[x * 3 + 0] = (r << 3);     // R
            rgb888_row[x * 3 + 1] = (g << 2);     // G
            rgb888_row[x * 3 + 2] = (b << 3);     // B
        }

        row_pointer[0] = rgb888_row;
        jpeg_write_scanlines(&encoder, row_pointer, 1);
    }

    jpeg_finish_compress(&encoder);
    jpeg_destroy_compress(&encoder);
    free(rgb888_row);

    *jpeg_len = max_jpeg_size;
    return jpeg_buffer;
}
