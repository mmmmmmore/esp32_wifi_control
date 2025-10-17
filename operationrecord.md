
I (1203) webserver: Registering motor URI handlers...
W (1213) httpd_uri: httpd_register_uri_handler: no slots left for registering handler
ESP_ERROR_CHECK failed: esp_err_t 0xb001 (ESP_ERR_HTTPD_HANDLERS_FULL) at 0x4200c36d
--- 0x4200c36d: webserver_motor_register at /Users/maochun/esp32prj/Project_CAM/branch/esp32_wifi_control/protocol/webserver/webserver_motor.c:174
file: "./protocol/webserver/webserver_motor.c" line 174
func: webserver_motor_register
expression: httpd_register_uri_handler(server, &control_request_uri)

abort() was called at PC 0x4037dd83 on core 0
--- 0x4037dd83: _esp_error_check_failed at /Users/maochun/esp32prj/esp-idf/components/esp_system/esp_err.c:49


Backtrace: 0x4037ddc5:0x3fca6fe0 0x4037dd8d:0x3fca7000 0x40384105:0x3fca7020 0x4037dd83:0x3fca7090 0x4200c36d:0x3fca70c0 0x4200bbce:0x3fca7110 0x4200bc92:0x3fca7130 0x4200bb2b:0x3fca71c0 0x420071e0:0x3fca71e0 0x42097a02:0x3fca7210
--- 0x4037ddc5: panic_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/panic.c:480
--- 0x4037dd8d: esp_system_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/esp_system_chip.c:87
--- 0x40384105: abort at /Users/maochun/esp32prj/esp-idf/components/newlib/src/abort.c:38
--- 0x4037dd83: _esp_error_check_failed at /Users/maochun/esp32prj/esp-idf/components/esp_system/esp_err.c:49
--- 0x4200c36d: webserver_motor_register at /Users/maochun/esp32prj/Project_CAM/branch/esp32_wifi_control/protocol/webserver/webserver_motor.c:174
--- 0x4200bbce: webserver_init at /Users/maochun/esp32prj/Project_CAM/branch/esp32_wifi_control/protocol/webserver/webserver.c:45
--- 0x4200bc92: start_webserver at /Users/maochun/esp32prj/Project_CAM/branch/esp32_wifi_control/protocol/webserver/webserver.c:27
--- 0x4200bb2b: app_main at /Users/maochun/esp32prj/Project_CAM/branch/esp32_wifi_control/main/main.c:80
--- 0x420071e0: main_task at /Users/maochun/esp32prj/esp-idf/components/freertos/app_startup.c:208
--- 0x42097a02: vPortTaskWrapper at /Users/maochun/esp32prj/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139




ELF file SHA256: bae856d08

Rebooting...
���ESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0xc (RTC_SW_CPU_RST),boot:0x8 (SPI_FAST_FLASH_BOOT)
Saved PC:0x4037df65
--- 0x4037df65: esp_restart_noos at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/soc/esp32s3/system_internal.c:164
SPIWP:0xee
mode:DIO, clock div:1
load:0x3fce2820,len:0x16fc
load:0x403c8700,len:0xf14
--- 0x403c8700: _stext at ??:?
load:0x403cb700,len:0x3214
entry 0x403c8930
--- 0x403c8930: call_start_cpu0 at /Users/maochun/esp32prj/esp-idf/components/bootloader/subproject/main/bootloader_start.c:25
I (29) boot: ESP-IDF v6.0-dev-2039-g2044fba6e7 2nd stage bootloader
I (29) boot: compile time Oct 15 2025 19:52:37