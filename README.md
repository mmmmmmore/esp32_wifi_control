# esp32_wifi_control (camera + detection edition)

This branch is now focused on camera stream and object-identification metadata for APK overlay.

## Implemented endpoints

- `GET /` - health check
- `GET /start` and `GET /stop` - stream control
- `GET /stream` - MJPEG stream
- `GET /snapshot` - single JPEG frame
- `GET /detection` - latest detection JSON
- `GET /detector?enable=true|false` - enable/disable detector
- `GET /detector/status` - detector health and model status
- `GET /ws/detection` - WebSocket detection stream (requires `CONFIG_HTTPD_WS_SUPPORT=y`)

Current firmware has no HTTP POST interface in the webserver component.

## Major branch change

Motor control code has been removed from this branch.

## Full solution document

See `docs/object_detection_solution.md` for:

- ESP32S3 feasible architecture
- TinyML migration path
- WebSocket payload contract
- APK overlay scaling rules
- production hardening checklist
