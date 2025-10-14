
I (1045) PSRAM: PSRAM size: 8388608 bytes
I (1045) PSRAM: Free heap: 8658964 bytes
I (1045) PSRAM: PSRAM is initialized and ready.
I (1055) PSRAM: Successfully allocated 1KB from PSRAM.
I (1055) common_gpio: Starting GPIO initialization...
I (1065) common_gpio: OV7670 GPIOs initialized
I (1065) common_gpio: Motor GPIOs initialized
I (1075) common_gpio: All GPIOs initialized
I (1075) common_gpio: LEDC channels initialized
I (1075) camera: Initializing camera module...
ESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0x8 (TG1WDT_SYS_RST),boot:0x8 (SPI_FAST_FLASH_BOOT)
Saved PC:0x40375714
--- 0x40375714: panic_enable_cache at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/panic_handler.c:277
SPIWP:0xee
mode:DIO, clock div:1
load:0x3fce2820,len:0x16fc
load:0x403c8700,len:0xf14
--- 0x403c8700: _stext at ??:?
load:0x403cb700,len:0x3214
entry 0x403c8930
--- 0x403c8930: call_start_cpu0 at /Users/maochun/esp32prj/esp-idf/components/bootloader/subproject/main/bootloader_start.c:25
I (29) boot: ESP-IDF v6.0-dev-2039-g2044fba6e7 2nd stage bootloader
I (29) boot: compile time Oct 14 2025 19:36:25
I (29) boot: Multicore bootloader
I (31) boot: chip revision: v0.2
I (34) boot: efuse block revision: v1.3
I (37) qio_mode: Enabling default flash chip QIO
I (42) boot.esp32s3: Boot SPI Speed : 80MHz
I (46) boot.esp32s3: SPI Mode       : QIO
I (49) boot.esp32s3: SPI Flash Size : 16MB
W (53) boot.esp32s3: PRO CPU has been reset by WDT.
W (58) boot.esp32s3: APP CPU has been reset by WDT.
I (62) boot: Enabling RNG early entropy source...