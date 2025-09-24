#include "esp_http_server.h"
#include "stream_control.h"
#include "ov7670_fifo.h"
#include "esp_log.h"
#include "esp_jpeg.h"
#include "esp_http_server.h"
#include "stream_control.h"
#include "ov7670_fifo.h"
#include "esp_log.h"
#include "esp_new_jpeg.h"
#include "esp_heap_caps.h"


static void rgb565_to_rgb888(uint8_t *src, uint8_t *dst, size_t pixel_count) {
    for (size_t i = 0; i < pixel_count; i++) {
        uint16_t pixel = ((uint16_t *)src)[i];
        dst[i * 3 + 0] = (pixel >> 11) << 3;       // R
        dst[i * 3 + 1] = ((pixel >> 5) & 0x3F) << 2; // G
        dst[i * 3 + 2] = (pixel & 0x1F) << 3;       // B
    }
}


static esp_err_t toggle_handler(httpd_req_t *req) {
    char buf[8] ={0};
    int ret = httpd_req_recv(req, buf, sizeof(buf)-1);
    if (ret <= 0) {
        httpd_resp_send_500(req);
        return ESP_FAIL;
    }
    buf[ret] ='\0';
    ESP_LOGI("toggle_handler", "Received toggle command: %s", buf);

    if (strncmp(buf, "ON", 2) == 0) {
        capture_control_set(true);
        httpd_resp_sendstr(req, "Capture ON");
    } else {
        capture_control_set(false);
        httpd_resp_sendstr(req, "Capture OFF");
    }
    return ESP_OK;
}



static esp_err_t image_handler(httpd_req_t *req) {
    if (!capture_control_get()) {
        httpd_resp_sendstr(req, "Capture disabled");
        return ESP_OK;
    }

    size_t width = 320;
    size_t height = 240;
    size_t pixel_count = width * height;
    size_t frame_size = pixel_count * 2;  // RGB565

    uint8_t *rgb565_buf = heap_caps_malloc(frame_size, MALLOC_CAP_SPIRAM);
    if (!rgb565_buf) {
        ESP_LOGE("image_handler", "Failed to allocate RGB565 buffer");
        httpd_resp_send_500(req);
        return ESP_FAIL;
    }

    fifo_read_frame(rgb565_buf, frame_size);

    // 转换为 RGB888
    size_t rgb888_size = pixel_count * 3;
    uint8_t *rgb888_buf = heap_caps_malloc(rgb888_size, MALLOC_CAP_SPIRAM);
    if (!rgb888_buf) {
        ESP_LOGE("image_handler", "Failed to allocate RGB888 buffer");
        free(rgb565_buf);
        httpd_resp_send_500(req);
        return ESP_FAIL;
    }

    rgb565_to_rgb888(rgb565_buf, rgb888_buf, pixel_count);
    free(rgb565_buf);

    // JPEG 编码配置
    jpeg_encode_config_t cfg = {
        .width = width,
        .height = height,
        .src_type = JPEG_PIXEL_FORMAT_RGB888,
        .quality = 75,
        .subsampling = JPEG_SUBSAMPLE_420,
    };

    jpeg_encoder_handle_t encoder;
    jpeg_encoder_output_t output;

    esp_err_t ret = jpeg_new_encoder(&cfg, &encoder);
    if (ret != ESP_OK) {
        ESP_LOGE("image_handler", "Failed to create JPEG encoder");
        free(rgb888_buf);
        httpd_resp_send_500(req);
        return ESP_FAIL;
    }

    ret = jpeg_encoder_process(encoder, rgb888_buf, &output);
    jpeg_del_encoder(encoder);
    free(rgb888_buf);

    if (ret != ESP_OK) {
        ESP_LOGE("image_handler", "JPEG encoding failed");
        httpd_resp_send_500(req);
        return ESP_FAIL;
    }

    httpd_resp_set_type(req, "image/jpeg");
    httpd_resp_send(req, (const char *)output.buf, output.len);
    free(output.buf);

    return ESP_OK;
}


    fifo_read_frame(frame_buffer, frame_size);  // 从 OV7670 读取图像

    // JPEG 编码配置
    esp_jpeg_encoder_cfg_t jpeg_cfg = {
        .width = width,
        .height = height,
        .src_type = JPEG_RAW_TYPE_RGB565,
        .quality = 75,
        .out_buf_size = 64 * 1024
    };

    uint8_t *jpeg_buf = heap_caps_malloc(jpeg_cfg.out_buf_size, MALLOC_CAP_SPIRAM);
    if (!jpeg_buf) {
        ESP_LOGE("image_handler", "Failed to allocate JPEG buffer");
        free(frame_buffer);
        httpd_resp_send_500(req);
        return ESP_FAIL;
    }

    esp_jpeg_encoder_handle_t encoder;
    esp_err_t ret = esp_jpeg_encoder_create(&jpeg_cfg, &encoder);
    if (ret != ESP_OK) {
        ESP_LOGE("image_handler", "Failed to create JPEG encoder");
        free(frame_buffer);
        free(jpeg_buf);
        httpd_resp_send_500(req);
        return ESP_FAIL;
    }

    size_t jpeg_size = jpeg_cfg.out_buf_size;
    ret = esp_jpeg_encoder_process(encoder, frame_buffer, jpeg_buf, &jpeg_size);
    esp_jpeg_encoder_destroy(encoder);

    free(frame_buffer);

    if (ret != ESP_OK) {
        ESP_LOGE("image_handler", "JPEG encoding failed");
        free(jpeg_buf);
        httpd_resp_send_500(req);
        return ESP_FAIL;
    }

    httpd_resp_set_type(req, "image/jpeg");
    httpd_resp_send(req, (const char *)jpeg_buf, jpeg_size);
    free(jpeg_buf);

    return ESP_OK;
}


    size_t jpeg_size = 0;
    esp_err_t ret = esp_new_jpeg_encode(&jpeg_cfg, frame_buffer, jpeg_buf, &jpeg_size);
    free(frame_buffer);

    if (ret != ESP_OK) {
        ESP_LOGE("image_handler", "JPEG encoding failed");
        free(jpeg_buf);
        httpd_resp_send_500(req);
        return ESP_FAIL;
    }

    httpd_resp_set_type(req, "image/jpeg");
    httpd_resp_send(req, (const char *)jpeg_buf, jpeg_size);
    free(jpeg_buf);
    return ESP_OK;
}




//static esp_err_t image_handler(httpd_req_t *req) {
//    if (!capture_control_get()) {
//        httpd_resp_sendstr(req, "Capture disabled");
//        return ESP_OK;
//    }
//
//    uint8_t *frame_buffer = malloc (640*480);
//    if (!frame_buffer){
//        httpd_resp_send_500(req);
//        return ESP_FAIL;
//    }
//    uint8_t frame_buffer[640 * 480];  // 示例：灰度图像
//    fifo_read_frame(frame_buffer, sizeof(frame_buffer));
//
//    httpd_resp_set_type(req, "application/octet-stream");
//    httpd_resp_send(req, (const char *)frame_buffer, sizeof(frame_buffer));
//    return ESP_OK;
//}


httpd_handle_t start_webserver(void) {
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;

    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_uri_t toggle_uri = {
            .uri = "/toggle",
            .method = HTTP_POST,
            .handler = toggle_handler
        };
        httpd_register_uri_handler(server, &toggle_uri);

        httpd_uri_t image_uri = {
            .uri = "/image",
            .method = HTTP_GET,
            .handler = image_handler
        };
        httpd_register_uri_handler(server, &image_uri);

        // 注册根路径处理器
        httpd_uri_t index_uri = {
            .uri = "/",
            .method = HTTP_GET,
            .handler = image_handler  // 或 index_handler，如果你启用 SPIFFS
        };
        httpd_register_uri_handler(server, &index_uri);
    }

    return server;
}



//
//httpd_handle_t start_webserver(void) {
//    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
//    httpd_handle_t server = NULL;
//
//    if (httpd_start(&server, &config) == ESP_OK) {
//        httpd_uri_t toggle_uri = {
//            .uri = "/toggle",
//            .method = HTTP_POST,
//            .handler = toggle_handler
//        };
//        httpd_register_uri_handler(server, &toggle_uri);
//
//        httpd_uri_t image_uri = {
//            .uri = "/image",
//            .method = HTTP_GET,
//            .handler = image_handler
//        };
//        httpd_register_uri_handler(server, &image_uri);
//    }
//
//    return server;
//}
//
static esp_err_t index_handler(httpd_req_t *req) {
    FILE *f = fopen("/spiffs/index.html", "r");
    if (!f) {
        httpd_resp_send_404(req);
        return ESP_FAIL;
    }

    char buf[1024];
    size_t read_bytes;
    httpd_resp_set_type(req, "text/html");

    while ((read_bytes = fread(buf, 1, sizeof(buf), f)) > 0) {
        httpd_resp_send_chunk(req, buf, read_bytes);
    }
    fclose(f);
    httpd_resp_send_chunk(req, NULL, 0);  // 结束响应
    return ESP_OK;
}

void register_static_handlers(httpd_handle_t server) {
    httpd_uri_t index_uri = {
        .uri = "/",
        .method = HTTP_GET,
        .handler = image_handler
    };
    httpd_register_uri_handler(server, &index_uri);
}





