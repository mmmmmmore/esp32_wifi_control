# Webserver API Definition (for APK integration)

This file is the **authoritative interface contract** for current firmware.

## 1) Protocol summary

- Base URL: `http://<device-ip>` (typically `192.168.4.1` in AP mode)
- Content types:
	- `application/json` for metadata/control endpoints
	- `image/jpeg` for snapshot
	- `multipart/x-mixed-replace; boundary=frame` for live stream
	- WebSocket text JSON on `/ws/detection`
- Auth: none (LAN/AP local access)

## 2) Active HTTP endpoints

| Method | Path | Query | Description | Response |
|---|---|---|---|---|
| GET | `/` | - | Health check | `text/plain`: `ok` |
| GET | `/start` | - | Enable stream loop flag | `text/plain`: `Stream started` |
| GET | `/stop` | - | Disable stream loop flag | `text/plain`: `Stream stopped` |
| GET | `/stream` | - | Continuous MJPEG stream (video only, no inline inference) | multipart JPEG frames |
| GET | `/snapshot` | - | Single JPEG capture only | JPEG binary |
| GET | `/detection` | - | Last detection result JSON (updated by background detector task) | JSON object (see section 4) |
| GET | `/detector` | `enable=1/0/true/false` (optional) | Read/update detector enable state | JSON: `{"enabled":true|false}` |
| GET | `/detector/status` | - | Detector runtime health | JSON status (see section 5) |

## 3) Active WebSocket endpoint

| Method | Path | Description | Payload |
|---|---|---|---|
| GET (WS handshake) | `/ws/detection` | Push detection JSON whenever the background detector finishes a run | Same JSON schema as `/detection` |

> Requires build option `CONFIG_HTTPD_WS_SUPPORT=y`.

## 4) `/detection` JSON schema

Returned when there is a valid detection result:

```json
{
	"frame_id": 123,
	"timestamp_ms": 456789,
	"frame_width": 640,
	"frame_height": 480,
	"enabled": true,
	"model_ready": true,
	"model_source": "embedded_rodata",
	"boxes": [
		{
			"label": "person",
			"score": 0.87,
			"x": 120,
			"y": 80,
			"w": 140,
			"h": 220
		}
	]
}
```

If no result exists yet, still returns HTTP 200 with:

```json
{
	"enabled": true,
	"model_ready": true,
	"model_source": "embedded_rodata",
	"message": "No detection result yet",
	"boxes": []
}
```

## 5) `/detector/status` JSON schema

```json
{
	"enabled": true,
	"model_ready": true,
	"model_source": "embedded_rodata",
	"has_result": false,
	"last_box_count": 0
}
```

## 6) POST support status

- **Current firmware has no POST HTTP interfaces** in `webserver.c`.
- APK should use GET endpoints above and WebSocket `/ws/detection`.

## 7) Legacy (lagency) interface compatibility

The following routes/features are **legacy only** from previous branches and are not part of this firmware:

- OTA routes (`/ota`, `/ota/status`, etc.)
- SPIFFS static files (`/index.html`, `/favicon.ico`, `/manifest.json` served by device)
- Motor/joystick routes (`/joystick`, `/rotate`, `/control/request`, `/control/release`)

For APK migration:

1. Remove calls to legacy routes above.
2. Use `/stream` for video and either poll `/detection` every 1-2s or subscribe to `/ws/detection` for live metadata updates.
3. Use `/detector?enable=1|0` and `/detector/status` for detector lifecycle.
4. Do not expect per-frame detection updates from `/stream` in current firmware.
 
