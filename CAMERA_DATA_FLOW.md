# ESP32 Camera Project - Complete Data Flow Path

## 📋 Project Overview
This is an ESP32-based vehicle control system with real-time camera streaming, motor control via joystick, and rotation control. The system captures video from an OV7670 camera and streams it to a web browser with overlay controls.

---

## 🎬 Camera Capture & Streaming Path

### **Layer 1: Hardware & Capture**

```
┌─────────────────────────────────────────────────────────────────┐
│ 1. CAMERA HARDWARE (OV7670)                                     │
│ ───────────────────────────────────────────────────────────────│
│ • Sensor: OV7670 (320x240 QVGA)                                │
│ • Connection: Parallel 8-bit data bus (pins Y0-Y9)             │
│ • Control: SCCB (I2C-like protocol)                            │
│ • Clock: 20 MHz XCLK                                           │
│ • Signals: VSYNC (frame sync), HREF (line sync), PCLK (clock) │
└─────────────────────────────────────────────────────────────────┘
```

**GPIO Pins Used:**
```
CAM_PIN_XCLK   = GPIO15 (clock)
CAM_PIN_SIOD   = GPIO4  (SCCB data)
CAM_PIN_SIOC   = GPIO5  (SCCB clock)
CAM_PIN_Y9     = GPIO16 (data bit 7)
CAM_PIN_Y8     = GPIO17 (data bit 6)
CAM_PIN_Y7     = GPIO18 (data bit 5)
CAM_PIN_Y6     = GPIO8  (data bit 4)
CAM_PIN_Y5     = GPIO19 (data bit 3)
CAM_PIN_Y4     = GPIO20 (data bit 2)
CAM_PIN_Y3     = GPIO3  (data bit 1)
CAM_PIN_Y2     = GPIO46 (data bit 0)
CAM_PIN_VSYNC  = GPIO7  (vertical sync)
CAM_PIN_HREF   = GPIO6  (horizontal sync)
CAM_PIN_PCLK   = GPIO21 (pixel clock)
```

---

### **Layer 2: Driver & Buffer Management**

```
┌─────────────────────────────────────────────────────────────────┐
│ 2. ESP32-S3 CAMERA DRIVER (esp_camera)                         │
│ File: /components/camera/camera.c                              │
│ ───────────────────────────────────────────────────────────────│
│ Function: camera_init()                                         │
│   ↓                                                             │
│   • Initializes GPIO pins for camera                           │
│   • Sets up LEDC for XCLK generation                           │
│   • Configures DMA for parallel data capture                   │
│   • Format: PIXFORMAT_JPEG (hardware JPEG encoding)            │
│   • Resolution: FRAMESIZE_QVGA (320x240)                       │
│   • Quality: JPEG_QUALITY = 12 (lower = better compression)    │
│   • Buffer: 2 frame buffers in PSRAM (external RAM)            │
│   • Grab mode: CAMERA_GRAB_WHEN_EMPTY                          │
│                                                                 │
│ Function: camera_capture_jpeg()                                │
│   ↓                                                             │
│   1. Call esp_camera_fb_get()                                  │
│   2. Get raw frame buffer from camera driver                   │
│   3. If already JPEG format → copy to PSRAM                    │
│      else → convert to JPEG using frame2jpg()                  │
│   4. Return uint8_t* jpeg_data + size_t jpeg_size              │
│                                                                 │
│ Storage: PSRAM (8MB external memory)                           │
│   - Faster than internal RAM                                   │
│   - Enough space for multiple frames                           │
└─────────────────────────────────────────────────────────────────┘
```

**Key Configuration:**
```c
// From components/camera/camera.c
pixel_format = PIXFORMAT_JPEG,      // Already JPEG from hardware
frame_size = FRAMESIZE_QVGA,        // 320x240
jpeg_quality = 12,                  // Quality level
fb_count = 2,                       // 2 frame buffers
fb_location = CAMERA_FB_IN_PSRAM,   // Store in external RAM
grab_mode = CAMERA_GRAB_WHEN_EMPTY  // Grab when buffer ready
```

---

### **Layer 3: Frame Handler (Capture Interface)**

```
┌─────────────────────────────────────────────────────────────────┐
│ 3. OV7670 HANDLER                                               │
│ File: /handler/ov7670_handler/ov7670_handler.c                │
│ ───────────────────────────────────────────────────────────────│
│ Function: ov7670_handler_get_jpeg()                            │
│   ↓                                                             │
│   1. Call camera_capture_jpeg()                                │
│   2. Retrieve JPEG data from camera driver                     │
│   3. Return pointer to JPEG buffer + size                      │
│                                                                 │
│ Return: (uint8_t **jpeg_data, size_t *jpeg_size)              │
│   - jpeg_data: Points to JPEG image in PSRAM                   │
│   - jpeg_size: Size of JPEG in bytes (typically 10-40KB)       │
│   - Caller MUST free(jpeg_data) after use                      │
└─────────────────────────────────────────────────────────────────┘
```

---

### **Layer 4: Web Server - Streaming Endpoint**

```
┌─────────────────────────────────────────────────────────────────┐
│ 4. HTTP WEBSERVER - MJPEG STREAMING                            │
│ File: /protocol/webserver/webserver_camera.c                   │
│ ───────────────────────────────────────────────────────────────│
│ Endpoint: GET /stream                                          │
│   ↓                                                             │
│ HTTP Handler: stream_handler()                                 │
│   1. Set Content-Type: multipart/x-mixed-replace               │
│   2. Set boundary: --frame                                     │
│   ────────────────────────────────────────────────────          │
│   LOOP WHILE stream_active:                                    │
│   ├─ Call ov7670_handler_get_jpeg(&jpeg_data, &size)         │
│   ├─ Format MJPEG boundary + content-type header               │
│   ├─ Send header chunk via httpd_resp_send_chunk()            │
│   ├─ Send JPEG image chunk                                     │
│   ├─ Send footer (\\r\\n)                                       │
│   ├─ free(jpeg_data)                                           │
│   └─ vTaskDelay(100ms) → ~10 FPS                              │
│   ────────────────────────────────────────────────────          │
│   3. Send final boundary: --frame--                            │
│                                                                 │
│ Frame Format (MJPEG boundary):                                │
│   --frame\\r\\n                                                  │
│   Content-Type: image/jpeg\\r\\n                                │
│   Content-Length: {size}\\r\\n                                  │
│   \\r\\n                                                         │
│   {JPEG_IMAGE_BYTES}                                           │
│   \\r\\n                                                         │
│                                                                 │
│ Frame Rate: ~10 FPS (100ms per frame)                          │
│ Typical Frame Size: 10-40 KB                                   │
│ Max Bandwidth: ~400 KB/s                                       │
└─────────────────────────────────────────────────────────────────┘
```

---

### **Layer 5: Network Transmission**

```
┌─────────────────────────────────────────────────────────────────┐
│ 5. WiFi & NETWORK PROTOCOL STACK                               │
│ ───────────────────────────────────────────────────────────────│
│ • Mode: SoftAP (Access Point)                                  │
│ • File: /protocol/wifi_ap/wifi_ap.c                           │
│ • SSID: (configured, typically "ESP32-CAM")                    │
│ • IP: 192.168.4.1                                              │
│ • Protocol: HTTP (not HTTPS for simplicity)                    │
│                                                                 │
│ Data Flow:                                                      │
│   JPEGDATA → TCP Socket → WiFi TX → Browser WiFi RX           │
│                                                                 │
│ HTTP Response Headers:                                          │
│   HTTP/1.1 200 OK                                              │
│   Content-Type: multipart/x-mixed-replace; boundary=frame      │
│   Connection: keep-alive                                       │
│   Transfer-Encoding: chunked                                   │
└─────────────────────────────────────────────────────────────────┘
```

---

### **Layer 6: Frontend (Browser) - Display**

```
┌─────────────────────────────────────────────────────────────────┐
│ 6. BROWSER - HTML & JAVASCRIPT                                 │
│ File: /spiffs/index.html + /spiffs/js/app.js                 │
│ ───────────────────────────────────────────────────────────────│
│                                                                 │
│ HTML Element:                                                   │
│   <img id="video" src="" alt="Camera Feed" />                 │
│                                                                 │
│ JavaScript Stream Control:                                      │
│                                                                 │
│   function startStream() {                                      │
│     fetch('/start')                // Signal ESP32 to start    │
│     .then(() => {                                              │
│       video.src = '/stream';       // Point img to MJPEG stream│
│       streamActive = true;                                      │
│     });                                                         │
│   }                                                             │
│                                                                 │
│   function stopStream() {                                       │
│     fetch('/stop');                // Signal ESP32 to stop     │
│     video.src = '';                // Clear image              │
│     streamActive = false;                                       │
│   }                                                             │
│                                                                 │
│ How Browser Displays MJPEG:                                     │
│   1. <img src="/stream"> makes GET request to /stream          │
│   2. Browser receives multipart/x-mixed-replace response       │
│   3. Browser parses JPEG boundaries automatically              │
│   4. Each --frame--boundary marks new image                    │
│   5. Browser continuously updates <img> source                 │
│   6. User sees continuous video stream ~10 FPS                 │
│                                                                 │
│ Alternative (not used, commented):                            │
│   Could use <video> tag with Motion-JPEG codec                │
│   But <img> tag simpler for this application                  │
└─────────────────────────────────────────────────────────────────┘
```

---

## 📊 Complete Data Flow Diagram

```
╔═══════════════════════════════════════════════════════════════════════════╗
║                     CAMERA CAPTURE TO DISPLAY PATH                        ║
╚═══════════════════════════════════════════════════════════════════════════╝

ESP32 DEVICE
┌─────────────────────────────────────────────────────────────────────────┐
│                                                                          │
│  ┌──────────────────────────────────────────────────────────────────┐   │
│  │ OV7670 CAMERA SENSOR                                            │   │
│  │ (320x240 @ 20MHz, parallel 8-bit + control signals)            │   │
│  └──────────────────────┬───────────────────────────────────────────┘   │
│                         │ Parallel data + sync signals                    │
│                         ↓                                                 │
│  ┌──────────────────────────────────────────────────────────────────┐   │
│  │ ESP32-S3 CAMERA DRIVER                                          │   │
│  │ (DMA capture, hardware JPEG encoding)                           │   │
│  │ • Pins: Y0-Y9, VSYNC, HREF, PCLK                               │   │
│  │ • Storage: 2 frame buffers in PSRAM (8MB)                      │   │
│  │ • Output: JPEG frames (10-40KB each)                           │   │
│  └──────────────────────┬───────────────────────────────────────────┘   │
│                         │ JPEG Buffer Pointer + Size                      │
│                         ↓                                                 │
│  ┌──────────────────────────────────────────────────────────────────┐   │
│  │ OV7670 HANDLER                                                  │   │
│  │ ov7670_handler_get_jpeg()                                       │   │
│  │ • Calls: camera_capture_jpeg()                                 │   │
│  │ • Returns: (uint8_t *jpeg_data, size_t size)                  │   │
│  └──────────────────────┬───────────────────────────────────────────┘   │
│                         │ JPEG Data Buffer                                │
│                         ↓                                                 │
│  ┌──────────────────────────────────────────────────────────────────┐   │
│  │ HTTP WEBSERVER (ESP-IDF httpd)                                  │   │
│  │ Endpoints:                                                      │   │
│  │ • GET  /stream    → MJPEG stream (multipart/x-mixed-replace)   │   │
│  │ • GET  /snapshot  → Single JPEG frame                          │   │
│  │ • POST /start     → Enable streaming flag                      │   │
│  │ • POST /stop      → Disable streaming flag                     │   │
│  │                                                                 │   │
│  │ stream_handler():                                               │   │
│  │ ├─ Set Content-Type: multipart/x-mixed-replace                 │   │
│  │ ├─ LOOP:                                                        │   │
│  │ │  ├─ Get JPEG frame from ov7670_handler_get_jpeg()           │   │
│  │ │  ├─ Format MJPEG boundary + headers                          │   │
│  │ │  ├─ Send via httpd_resp_send_chunk()                        │   │
│  │ │  ├─ free(jpeg_data)                                          │   │
│  │ │  └─ vTaskDelay(100ms) [~10 FPS]                            │   │
│  │ └─ Send final boundary                                          │   │
│  └──────────────────────┬───────────────────────────────────────────┘   │
│                         │ MJPEG HTTP Response                             │
│                         │ (TCP stream: boundary + JPEG repeating)         │
│                         ↓                                                 │
│  ┌──────────────────────────────────────────────────────────────────┐   │
│  │ WiFi SoftAP                                                     │   │
│  │ • SSID: ESP32-CAM (or configured)                              │   │
│  │ • IP: 192.168.4.1                                              │   │
│  │ • Protocol: HTTP (port 80)                                     │   │
│  └──────────────────────┬───────────────────────────────────────────┘   │
│                         │ WiFi TX                                         │
└─────────────────────────┼─────────────────────────────────────────────────┘
                          │
                          │ WiFi Network (2.4GHz)
                          │
┌─────────────────────────┼─────────────────────────────────────────────────┐
│ USER'S DEVICE (Browser) │                                                 │
│                         ↓                                                 │
│  ┌──────────────────────────────────────────────────────────────────┐   │
│  │ BROWSER - JAVASCRIPT (app.js)                                   │   │
│  │                                                                 │   │
│  │ function startStream():                                         │   │
│  │   fetch('/start')  // Enable streaming on ESP32               │   │
│  │   video.src = '/stream'  // Set img source to stream URL       │   │
│  │                                                                 │   │
│  │ function stopStream():                                          │   │
│  │   fetch('/stop')   // Disable streaming on ESP32              │   │
│  │   video.src = ''   // Clear image                             │   │
│  │                                                                 │   │
│  └──────────────────────┬───────────────────────────────────────────┘   │
│                         │ HTTP GET /stream                                │
│                         ↓                                                 │
│  ┌──────────────────────────────────────────────────────────────────┐   │
│  │ BROWSER - HTML                                                  │   │
│  │                                                                 │   │
│  │ <img id="video" src="/stream" alt="Camera Feed" />            │   │
│  │                                                                 │   │
│  │ When src="/stream":                                            │   │
│  │ 1. Browser GET /stream                                         │   │
│  │ 2. Receives: multipart/x-mixed-replace; boundary=frame        │   │
│  │ 3. Parses boundaries automatically                             │   │
│  │ 4. Each boundary = new JPEG frame                             │   │
│  │ 5. <img> continuously updates showing live video              │   │
│  │ 6. Frame rate: ~10 FPS (100ms per frame)                      │   │
│  │                                                                 │   │
│  │ Result: User sees real-time camera stream                      │   │
│  └──────────────────────────────────────────────────────────────────┘   │
│                                                                          │
└──────────────────────────────────────────────────────────────────────────┘
```

---

## 🔄 Request/Response Flow

### **User Clicks "Start Stream":**

```
Browser (User) 
    ↓
JavaScript: startStream()
    ↓
fetch('/start')  ← POST request
    ↓
[WiFi Network]
    ↓
ESP32 HTTP Server
    ↓
start_handler()
    ├─ stream_active = true
    └─ Return "Stream started"
    ↓
Browser receives response
    ↓
JavaScript sets: video.src = '/stream'
    ↓
Browser makes GET /stream request
    ↓
ESP32 stream_handler()
    ├─ Check stream_active flag
    ├─ Set HTTP response headers (multipart/x-mixed-replace)
    └─ Loop:
        ├─ ov7670_handler_get_jpeg(&data, &size)
        ├─ Format MJPEG frame boundary
        ├─ httpd_resp_send_chunk() × 3 (header, data, footer)
        ├─ free(jpeg_data)
        └─ vTaskDelay(100ms)
    ↓
Browser receives multipart stream
    ↓
Browser parses MJPEG:
    ├─ Detect --frame boundary
    ├─ Extract JPEG from content-length
    ├─ Update <img> display
    ├─ Detect next --frame boundary
    └─ Repeat...
    ↓
USER SEES LIVE VIDEO STREAM (10 FPS)
```

---

## 📝 File Locations & Key Functions

| Component | File Path | Key Functions |
|-----------|-----------|---|
| **Camera Driver** | `components/camera/camera.c` | `camera_init()`, `camera_capture_jpeg()` |
| **OV7670 Handler** | `handler/ov7670_handler/ov7670_handler.c` | `ov7670_handler_get_jpeg()` |
| **Web Server** | `protocol/webserver/webserver.c` | `start_webserver()`, `index_handler()` |
| **Camera Streaming** | `protocol/webserver/webserver_camera.c` | `stream_handler()`, `snapshot_handler()` |
| **Frontend** | `spiffs/index.html` | HTML structure with `<img id="video">` |
| **JavaScript** | `spiffs/js/app.js` | `startStream()`, `stopStream()`, control functions |
| **WiFi AP** | `protocol/wifi_ap/wifi_ap.c` | `wifi_init_softap()` |

---

## 🔌 Supported Endpoints

| Method | Endpoint | Purpose |
|--------|----------|---------|
| GET | `/` | Serve index.html |
| GET | `/stream` | MJPEG stream (multipart) |
| GET | `/snapshot` | Single JPEG frame |
| POST | `/start` | Enable streaming |
| POST | `/stop` | Disable streaming |
| POST | `/control/request` | Request device control |
| POST | `/control/release` | Release device control |
| POST | `/joystick` | Send joystick data (angle, distance) |
| POST | `/rotation` | Send rotation data (direction, angle) |
| POST | `/motor` | Direct motor control commands |
| GET | `/css/*` | Serve CSS files |
| GET | `/js/*` | Serve JavaScript files |
| GET | `/manifest.json` | App manifest |

---

## 💾 Memory Usage

| Resource | Location | Size | Purpose |
|----------|----------|------|---------|
| **Frame Buffers** | PSRAM | 2 × frame size | Double buffering for smooth capture |
| **JPEG Data** | PSRAM | 10-40 KB | Compressed image data per frame |
| **Web Server** | Internal RAM | ~50 KB | HTTP server task stack |
| **Drivers** | Internal RAM | ~20 KB | Camera driver, WiFi driver |
| **SPIFFS** | Flash | ~512 KB | HTML, CSS, JS files |

---

## 🚀 Initialization Sequence

```
main()
  ↓
nvs_flash_init()           // Initialize non-volatile storage
  ↓
wifi_init_softap()         // Start WiFi AP (192.168.4.1)
  ↓
check_psram_status()       // Verify PSRAM available (8MB)
  ↓
platform_init()            // Initialize GPIO, I2C, SPI
  ↓
init_spiffs()              // Mount SPIFFS filesystem
  ↓
start_webserver()          // Start HTTP server
  ├─ Register: /stream, /snapshot
  ├─ Register: /start, /stop
  ├─ Register: /joystick, /rotation
  ├─ Register: / (index.html)
  └─ Register: /css/*, /js/* (static files)
  ↓
Ready for connections
```

---

## 📡 Data Compression

```
Original Frame: 320×240×3 bytes (RGB) = 230.4 KB

JPEG Compression (quality=12):
└─ Hardware JPEG encoder in ESP32-S3
   └─ Output: ~10-40 KB per frame
   └─ Compression ratio: 5:1 to 20:1
   └─ At 10 FPS: ~100-400 KB/sec bandwidth required
```

---

## ⚠️ Important Notes

1. **Stream Flag:** The `stream_active` flag controls whether frames are captured and sent. This is separate from the HTTP connection.
2. **Frame Timing:** Each frame has 100ms delay → ~10 FPS. This can be adjusted in `webserver_camera.c` line with `vTaskDelay()`.
3. **Memory Safety:** JPEG data is allocated from PSRAM and MUST be freed after sending. This is handled by `free(jpeg_data)`.
4. **WiFi Limitations:** Using 2.4GHz WiFi with SoftAP mode. Range is ~20-30 meters.
5. **Concurrent Access:** Only one client can receive stream data at a time (controlled by HTTP server).
6. **Encoding:** Already JPEG from camera hardware (not software-converted unless needed).

---

## 🔍 Debugging Tips

**To verify streaming works:**
```bash
# Connect to ESP32 WiFi (SSID: ESP32-CAM, IP: 192.168.4.1)
# Then in browser or terminal:

# Start stream:
curl http://192.168.4.1/start

# Get single frame:
curl http://192.168.4.1/snapshot > frame.jpg

# View stream (saves to file):
curl http://192.168.4.1/stream > stream.mjpeg

# Stop stream:
curl http://192.168.4.1/stop
```

**To view logs:**
- Use ESP-IDF monitor: `idf.py monitor`
- Tags: `camera`, `webserver`, `webserver_camera`, `ov7670_handler`

