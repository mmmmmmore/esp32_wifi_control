## WebServer Component Architecture

### webserver.c (Main Webserver)
Central webserver implementation that handles all HTTP endpoints:

**Static File Handlers:**
- `/` - Serves index.html
- `/index.html` - Index page
- `/favicon.ico` - Favicon
- `/css/*` - CSS files
- `/js/*` - JavaScript files
- `/assets/*` - Asset files
- `/manifest.json` - PWA manifest

**OTA Update Handlers:**
- `/ota` - Trigger OTA firmware update
- `/ota/status` - Query OTA update status

**Motor Control Handlers:**
- `/joystick` (POST) - Receive joystick/movement commands (angle, distance)
- `/rotate` (POST) - Receive rotation commands (direction, degrees)
- `/control/request` (POST) - Request control permission
- `/control/release` (POST) - Release control permission

**Features:**
- JSON-based request/response format
- UUID-based access control
- Permission management (single controller system)
- Real-time motor command handling

### webserver_camera.c (Camera Module)
Independent camera streaming component, registers its own URI handlers:
- `/stream` - Live video streaming with optional SD card recording
- `/snapshot` - Single frame JPEG capture
- `/start` - Start streaming
- `/stop` - Stop streaming

**Features:**
- MJPEG multipart streaming
- Optional SD card video recording
- Automatic frame rate control (10 fps)

### Architecture
- **Modular design**: Camera functionality is in separate module for independence
- **Centralized motor control**: All motor handlers in main webserver.c for consistency
- **OTA support**: Built-in firmware update mechanism
- **SD card recording**: Optional video recording during streaming
- **Control permission system**: Prevents simultaneous control from multiple sources

