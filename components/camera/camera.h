
#pragma once

#include "esp_err.h"
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CAMERA_FRAME_WIDTH   320
#define CAMERA_FRAME_HEIGHT  240
#define CAMERA_FRAME_SIZE    (CAMERA_FRAME_WIDTH * CAMERA_FRAME_HEIGHT)

// 初始化摄像头模块
esp_err_t camera_init(void);

// 采集一帧 JPEG，返回指针和长度（由调用方 free）
esp_err_t camera_capture_jpeg(uint8_t **jpeg_data, size_t *jpeg_size);

// 停止图像采集
void camera_stop(void);

#ifdef __cplusplus
}
#endif
