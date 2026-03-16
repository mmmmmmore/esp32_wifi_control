/*
 * object_detector.cpp — real inference using ESP-DL 3.x + YOLO11n
 *
 * HOW TO GET THE MODEL FILE
 * ─────────────────────────
 * 1. Download yolo11n_192_esp32s3.espdl from Espressif's esp-who release:
 *      https://github.com/espressif/esp-who/releases
 *    (look for an asset named yolo11n_192.espdl or similar under the latest release)
 * 2. Copy the file into the spiffs/ folder in this project and rename it to
 *    yolo11n.espdl so the path becomes:  spiffs/yolo11n.espdl
 * 3. Run:  idf.py build flash   (the SPIFFS image will include the model)
 *
 * WITHOUT the model file the component falls back to returning no detections.
 */

#include "object_detector.h"

/* ── esp-dl C++ headers ─────────────────────────────────────────────────── */
#include "dl_detect_base.hpp"
#include "dl_detect_yolo11_postprocessor.hpp"
#include "dl_image_jpeg.hpp"
#include "dl_image_preprocessor.hpp"
#include "dl_model_base.hpp"
#include "fbs_model.hpp"

/* ── ESP-IDF ────────────────────────────────────────────────────────────── */
#include "esp_heap_caps.h"
#include "esp_log.h"
#include "esp_timer.h"
#include <cstdio>
#include <cstring>
#include <list>

static const char *TAG = "object_detector";

#ifndef OBJECT_DETECTOR_MODEL_EMBEDDED
#define OBJECT_DETECTOR_MODEL_EMBEDDED 0
#endif

#if OBJECT_DETECTOR_MODEL_EMBEDDED
extern const uint8_t _binary_yolo11n_espdl_start[] asm("_binary_yolo11n_espdl_start");
extern const uint8_t _binary_yolo11n_espdl_end[] asm("_binary_yolo11n_espdl_end");
#endif

/* ── COCO-80 class names (standard order) ───────────────────────────────── */
static const char *const COCO_LABELS[80] = {
    "person", "bicycle", "car", "motorcycle", "airplane", "bus", "train",
    "truck", "boat", "traffic light", "fire hydrant", "stop sign",
    "parking meter", "bench", "bird", "cat", "dog", "horse", "sheep", "cow",
    "elephant", "bear", "zebra", "giraffe", "backpack", "umbrella", "handbag",
    "tie", "suitcase", "frisbee", "skis", "snowboard", "sports ball", "kite",
    "baseball bat", "baseball glove", "skateboard", "surfboard",
    "tennis racket", "bottle", "wine glass", "cup", "fork", "knife", "spoon",
    "bowl", "banana", "apple", "sandwich", "orange", "broccoli", "carrot",
    "hot dog", "pizza", "donut", "cake", "chair", "couch", "potted plant",
    "bed", "dining table", "toilet", "tv", "laptop", "mouse", "remote",
    "keyboard", "cell phone", "microwave", "oven", "toaster", "sink",
    "refrigerator", "book", "clock", "vase", "scissors", "teddy bear",
    "hair drier", "toothbrush"
};

/* ── YOLO11 detector wrapper ────────────────────────────────────────────── */
/*
 * YOLO11n anchor-free detection:
 *   3 output stages with strides 8, 16, 32
 *   Input normalised to [0,1] by dividing by 255
 *   Letterboxed so any aspect ratio is handled
 */
class Yolo11Detector : public dl::detect::DetectImpl {
public:
    Yolo11Detector(const char *model_ref, fbs::model_location_type_t location, float score_thr, float nms_thr)
    {
        m_model = new dl::Model(model_ref,
                                location,
                                0,
                                dl::MEMORY_MANAGER_GREEDY);

        /* mean=0, std=255  →  pixel/255 normalisation */
        m_image_preprocessor = new dl::image::ImagePreprocessor(
            m_model,
            {0.f, 0.f, 0.f},
            {255.f, 255.f, 255.f});
        m_image_preprocessor->enable_letterbox({128, 128, 128});

        /* YOLO11 3-stage anchor-free: stride 8 / 16 / 32, no offset */
        std::vector<dl::detect::anchor_point_stage_t> stages = {
            {8,  8,  0, 0},
            {16, 16, 0, 0},
            {32, 32, 0, 0},
        };
        m_postprocessor = new dl::detect::yolo11PostProcessor(
            m_model, m_image_preprocessor,
            score_thr, nms_thr,
            /*top_k=*/10, stages);
    }

    std::list<dl::detect::result_t> &run_with_mode(const dl::image::img_t &img, dl::runtime_mode_t mode)
    {
        m_image_preprocessor->preprocess(img);
        m_model->run(mode);
        m_postprocessor->clear_result();
        m_postprocessor->postprocess();
        return m_postprocessor->get_result(img.width, img.height);
    }
};

/* ── Module state ────────────────────────────────────────────────────────── */
static detector_config_t s_cfg = {
    .enabled        = true,
    .input_width    = 192,
    .input_height   = 192,
    .score_threshold = 0.45f,
};

static Yolo11Detector *s_detector    = nullptr;
static bool            s_model_ready = false;
static uint32_t        s_frame_counter = 0;
static const char     *s_model_source = "none";

/* ── Public C API ────────────────────────────────────────────────────────── */

esp_err_t object_detector_init(const detector_config_t *cfg)
{
    if (cfg != NULL) {
        s_cfg = *cfg;
    }

    if (s_detector != nullptr) {
        delete s_detector;
        s_detector = nullptr;
    }
    s_model_ready = false;
    s_model_source = "none";

#if OBJECT_DETECTOR_MODEL_EMBEDDED
    size_t model_size = (size_t)(_binary_yolo11n_espdl_end - _binary_yolo11n_espdl_start);
    if (model_size == 0) {
        ESP_LOGW(TAG, "Embedded model symbol exists but size is 0; detector disabled");
        return ESP_OK;
    }

    ESP_LOGI(TAG, "Loading embedded YOLO11n model (%u bytes)", (unsigned int)model_size);
    s_detector = new Yolo11Detector((const char *)_binary_yolo11n_espdl_start,
                                    fbs::MODEL_LOCATION_IN_FLASH_RODATA,
                                    s_cfg.score_threshold,
                                    0.50f);
    s_model_ready = true;
    s_model_source = "embedded_rodata";
#else
    ESP_LOGW(TAG, "No embedded model found. Add model file at models/yolo11n.espdl and rebuild.");
    ESP_LOGW(TAG, "Detector will return empty boxes until model is embedded.");
#endif

    ESP_LOGI(TAG, "YOLO11n model ready (input %ux%u, score_thr=%.2f)",
             s_cfg.input_width, s_cfg.input_height,
             (double)s_cfg.score_threshold);
    return ESP_OK;
}

void object_detector_set_enabled(bool enabled)
{
    s_cfg.enabled = enabled;
}

bool object_detector_is_enabled(void)
{
    return s_cfg.enabled;
}

bool object_detector_model_ready(void)
{
    return s_model_ready;
}

const char *object_detector_model_source(void)
{
    return s_model_source;
}

esp_err_t object_detector_run(const uint8_t *jpeg_data, size_t jpeg_size,
                               detector_result_t *result)
{
    if (!jpeg_data || jpeg_size == 0 || !result) {
        return ESP_ERR_INVALID_ARG;
    }

    memset(result, 0, sizeof(*result));
    result->frame_id      = ++s_frame_counter;
    result->timestamp_ms  = (uint32_t)(esp_timer_get_time() / 1000ULL);
    result->frame_width   = s_cfg.input_width;
    result->frame_height  = s_cfg.input_height;

    if (!s_cfg.enabled || !s_model_ready) {
        return ESP_OK;   /* no-op — return empty result */
    }

    /* ── 1. Decode JPEG → RGB888 ─────────────────────────────────────────── */
    dl::image::jpeg_img_t jpeg_src = {
        .data     = (void *)jpeg_data,
        .data_len = jpeg_size,
    };
    dl::image::img_t img =
        dl::image::sw_decode_jpeg(jpeg_src, dl::image::DL_IMAGE_PIX_TYPE_RGB888);

    if (!img.data) {
        ESP_LOGE(TAG, "JPEG decode failed");
        return ESP_ERR_NO_MEM;
    }

    /* ── 2. Run YOLO11n inference ─────────────────────────────────────────── */
    int64_t t0 = esp_timer_get_time();
    std::list<dl::detect::result_t> &detections = s_detector->run_with_mode(img, dl::RUNTIME_MODE_MULTI_CORE);
    int64_t latency_ms = (esp_timer_get_time() - t0) / 1000;

    heap_caps_free(img.data);   /* release decoded frame buffer */

    ESP_LOGD(TAG, "inference %lld ms, %d boxes", latency_ms,
             (int)detections.size());

    /* ── 3. Copy results into C-compatible struct ────────────────────────── */
    result->frame_width  = img.width;
    result->frame_height = img.height;

    for (const dl::detect::result_t &d : detections) {
        if (result->box_count >= DETECTOR_MAX_BOXES) break;

        detector_box_t *b = &result->boxes[result->box_count++];

        /* category index → COCO label string */
        if (d.category >= 0 && d.category < 80) {
            strncpy(b->label, COCO_LABELS[d.category], sizeof(b->label) - 1);
        } else {
            strncpy(b->label, "unknown", sizeof(b->label) - 1);
        }
        b->label[sizeof(b->label) - 1] = '\0';

        b->score = d.score;
        b->x     = (uint16_t)(d.box[0] < 0 ? 0 : d.box[0]);
        b->y     = (uint16_t)(d.box[1] < 0 ? 0 : d.box[1]);
        b->w     = (uint16_t)(d.box[2] - d.box[0]);
        b->h     = (uint16_t)(d.box[3] - d.box[1]);
    }

    if (result->box_count > 0 && (result->frame_id % 10U) == 0U) {
        ESP_LOGI(TAG,
                 "frame=%lu boxes=%u top=%s score=%.2f box=[%u,%u,%u,%u] latency=%lldms",
                 (unsigned long)result->frame_id,
                 (unsigned int)result->box_count,
                 result->boxes[0].label,
                 (double)result->boxes[0].score,
                 (unsigned int)result->boxes[0].x,
                 (unsigned int)result->boxes[0].y,
                 (unsigned int)result->boxes[0].w,
                 (unsigned int)result->boxes[0].h,
                 latency_ms);
    }

    return ESP_OK;
}
