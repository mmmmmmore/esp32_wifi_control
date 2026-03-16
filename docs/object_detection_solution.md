# ESP32S3 Camera Object Identification + APK Overlay Solution

## 1) What is implemented in this branch

This branch now contains:

- Camera streaming API (`/stream`, `/snapshot`)
- Detection metadata API (`/detection`)
- Detector runtime toggle API (`/detector?enable=true|false`)
- WebSocket detection channel (`/ws/detection`) when `CONFIG_HTTPD_WS_SUPPORT=y`
- Motor control code and motor endpoints removed

Current detector implementation is a runtime-safe placeholder in `handler/object_detector/object_detector.c` so the protocol and APK integration can be developed immediately.

## 2) Why not OpenCV on ESP32S3

OpenCV is not practical on ESP32S3 due to RAM/flash and CPU constraints.

Use one of these two production paths instead:

1. TinyML on ESP32S3 (recommended)
   - TensorFlow Lite Micro or ESP-DL/ESP-PPQ flow
   - Quantized model (int8), low input size (96x96 or 128x128)
   - Classes: keep small (2~6)

2. Hybrid edge architecture
   - ESP32S3 sends JPEG to phone/app backend
   - Detection runs on phone (PyTorch Mobile / ONNX Runtime / ncnn)
   - ESP32 receives control/policy only, APK renders overlays

## 3) Recommended production architecture

### Device (ESP32S3)

- Camera capture in JPEG (`camera_capture_jpeg`)
- Detector inference for each frame (or every N frames)
- Keep latest detection result in memory
- Push result over WebSocket as JSON

### APK

- Display MJPEG stream from `/stream`
- Open WebSocket to `/ws/detection`
- For each JSON message:
  - Parse `frame_id`, `frame_width`, `frame_height`, `boxes[]`
  - Scale boxes to ImageView preview size
  - Draw overlay rectangles and labels

## 4) WebSocket payload contract

Detection message (`/ws/detection`):

```json
{
  "frame_id": 123,
  "timestamp_ms": 45678,
  "frame_width": 320,
  "frame_height": 240,
  "boxes": [
    {
      "label": "person",
      "score": 0.88,
      "x": 50,
      "y": 40,
      "w": 100,
      "h": 120
    }
  ]
}
```

Coordinate system is in camera frame pixels.

## 5) APK overlay scaling formula

If camera frame is `fw x fh` and preview canvas is `vw x vh`:

- `sx = vw / fw`
- `sy = vh / fh`
- draw rect at:
  - `left = x * sx`
  - `top = y * sy`
  - `right = (x + w) * sx`
  - `bottom = (y + h) * sy`

If your preview uses crop/fit-center, apply the same transform matrix used by the image renderer.

## 6) Upgrade plan: placeholder -> TinyML detector

1. Build dataset for your real objects (label + box)
2. Train lightweight model (MobileNetV2-SSD small head or YOLO-nano style)
3. Quantize to int8
4. Convert to TFLM-compatible flatbuffer
5. Replace `object_detector_run()` with real inference pipeline:
   - JPEG decode/resize
   - normalize/quantize
   - invoke model
   - NMS
   - fill `detector_result_t`

## 7) Performance targets for ESP32S3

- Input: 96x96 or 128x128
- Inference interval: every 2~4 frames
- End-to-end latency target: < 300 ms
- FPS target with overlay updates: 4~10 updates/s

## 8) Configuration checklist

- Enable WebSocket in ESP-IDF:
  - `CONFIG_HTTPD_WS_SUPPORT=y`
- Keep PSRAM enabled
- Use QVGA stream initially (320x240)
- Keep class count small to reduce model size and false positives

## 9) Security and robustness

- Add token auth on HTTP and WebSocket routes for production
- Add heartbeat/ping on WS and reconnect logic in APK
- Add rate limit for `/snapshot` and `/stream` clients
- Validate JSON payload bounds in APK

## 10) Removed motor functionality

Removed from this branch:

- motor handler component
- motor pwm component
- motor web routes (`/joystick`, `/rotate`, `/control/request`, `/control/release`)
- motor GPIO aliases in shared GPIO header

This branch is now camera + detection pipeline focused.
