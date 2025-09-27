#include "jpeg.h"
#include "tiny_jpeg.h"
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

typedef struct {
    uint8_t* buffer;
    size_t size;
    size_t capacity;
} jpeg_mem_context;

static void jpeg_mem_writer(void* context, void* data, int size) {
    jpeg_mem_context* ctx = (jpeg_mem_context*)context;
    if (ctx->size + size > ctx->capacity) return;
    memcpy(ctx->buffer + ctx->size, data, size);
    ctx->size += size;
}

uint8_t* jpeg_encode_rgb565(const uint8_t* rgb_data, size_t rgb_len, uint16_t width, uint16_t height, size_t* jpeg_len) {
    if (!rgb_data || rgb_len == 0 || width == 0 || height == 0 || !jpeg_len) {
        return NULL;
    }

    size_t max_jpeg_size = rgb_len / 2;
    uint8_t* jpeg_buffer = malloc(max_jpeg_size);
    if (!jpeg_buffer) {
        return NULL;
    }

    uint8_t* rgb888 = malloc(width * height * 3);
    if (!rgb888) {
        free(jpeg_buffer);
        return NULL;
    }

    for (size_t i = 0; i < width * height; i++) {
        uint16_t pixel = ((uint16_t*)rgb_data)[i];
        uint8_t r = (pixel >> 11) & 0x1F;
        uint8_t g = (pixel >> 5) & 0x3F;
        uint8_t b = pixel & 0x1F;

        rgb888[i * 3 + 0] = r << 3;
        rgb888[i * 3 + 1] = g << 2;
        rgb888[i * 3 + 2] = b << 3;
    }

    jpeg_mem_context ctx = {
        .buffer = jpeg_buffer,
        .size = 0,
        .capacity = max_jpeg_size
    };

    tje_encode_with_func(jpeg_mem_writer, &ctx, 3, width, height, 3, rgb888);

    free(rgb888);

    if (ctx.size == 0) {
        free(jpeg_buffer);
        return NULL;
    }

    *jpeg_len = ctx.size;
    return jpeg_buffer;
}