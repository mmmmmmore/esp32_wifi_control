# WebSocket Interface Contract (for APK redesign)

This document defines the **current firmware WebSocket protocol** implemented in `protocol/webserver/webserver.c`.

## 1) Connection

- Base URL: `ws://192.168.4.2/ws`
- Compatible alias: `ws://192.168.4.2/ws/detection` (same handler/behavior)
- Data format: text JSON frames only
- Build requirement: `CONFIG_HTTPD_WS_SUPPORT=y`
- Current implementation keeps one active WS client socket (`s_ws_fd`), so treat connection as **single-client**.

After handshake, device sends a welcome event:

```json
{
	"type": "event",
	"event": "ws.connected",
	"detector": {
		"enabled": true,
		"model_ready": true,
		"model_source": "embedded_rodata",
		"has_result": false,
		"last_box_count": 0
	},
	"face": {
		"ready": true,
		"mode": "idle",
		"enrolled_count": 0,
		"max_ids": 5,
		"match_threshold": 0.9
	}
}
```

## 2) Common message envelope

### Request (APK -> device)

```json
{
	"cmd": "face.identify",
	"request_id": "optional-client-id"
}
```

- `cmd` is required.
- `request_id` is optional; if provided it will be echoed in response.

### Response (device -> APK)

```json
{
	"type": "response",
	"cmd": "face.identify",
	"ok": true,
	"request_id": "optional-client-id",
	"payload": {}
}
```

- `ok=false` means command failed or validation failed.
- On some failures, response may include `message` and/or `error`.

### Async event (device -> APK)

```json
{
	"type": "event",
	"event": "detector.result",
	"payload": {}
}
```

## 3) Supported commands

| Command | Required fields | Purpose | Response payload |
|---|---|---|---|
| `ping` | - | Connectivity check | `{ "message": "pong" }` (as top-level `message`) |
| `detector.status` | - | Get detector runtime status | detector status object |
| `detector.set_enabled` | `enabled` (bool/0/1/"true"/"false") | Enable/disable object detector | detector status object |
| `detector.get_latest` | - | Read latest detection snapshot | detection result object |
| `face.mode.set` | `mode` = `idle` \| `setup` \| `identify` | Switch FaceID mode | face status object |
| `face.mode.get` | - | Get current FaceID mode/status | face status object |
| `face.status` | - | Alias of `face.mode.get` | face status object |
| `face.list` | - | List enrolled identities | `{ "count": n, "faces": [{"id":1,"name":"Alice"}] }` |
| `face.enroll.confirm` | `name` (string, optional but recommended) | Capture current frame and enroll face in setup flow | face result object |
| `face.identify` | - | Capture current frame and identify face | face result object |
| `face.delete_last` | - | Remove most recent enrolled identity | face result object |
| `face.clear` | - | Remove all enrolled identities | face result object |

Unknown/malformed command returns `ok=false` with `message`.

## 4) Payload schemas

### 4.1 Detector status payload

```json
{
	"enabled": true,
	"model_ready": true,
	"model_source": "embedded_rodata",
	"has_result": true,
	"last_box_count": 1
}
```

### 4.2 Detection result payload (`detector.get_latest` and `detector.result` event)

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

### 4.3 Face status payload

```json
{
	"ready": true,
	"mode": "idle",
	"enrolled_count": 0,
	"max_ids": 5,
	"match_threshold": 0.9
}
```

### 4.4 Face result payload

```json
{
	"success": true,
	"matched": true,
	"id": 1,
	"similarity": 0.93,
	"detected_face_count": 1,
	"enrolled_count": 3,
	"name": "Alice",
	"message": "Identify success",
	"mode": "identify"
}
```

Notes:
- If similarity does not reach threshold, firmware returns `name: "unknown"` and `matched: false`.
- `face.enroll.confirm`, `face.identify`, `face.delete_last`, `face.clear` can include top-level `error` when ESP-IDF API returns an error code.

## 5) APK redesign guidance

- Use `/ws` as the primary endpoint; keep `/ws/detection` as compatibility fallback.
- Treat WS as command+event bus (request/response + async events) instead of detection-only stream.
- Include `request_id` on every command so APK can map UI actions to responses.
- Keep reconnect logic: on reconnect, wait for `ws.connected`, then query `face.status` and `face.list` to rebuild UI state.
 
