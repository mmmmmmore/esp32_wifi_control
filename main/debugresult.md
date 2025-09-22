
Rebooting...
���ESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0xc (RTC_SW_CPU_RST),boot:0x28 (SPI_FAST_FLASH_BOOT)
Saved PC:0x4037c941
--- 0x4037c941: esp_restart_noos at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/soc/esp32s3/system_internal.c:164
SPIWP:0xee
mode:DIO, clock div:1
load:0x3fce2820,len:0x1588
load:0x403c8700,len:0xd7c
--- 0x403c8700: _stext at ??:?
load:0x403cb700,len:0x2f80
entry 0x403c8908
--- 0x403c8908: call_start_cpu0 at /Users/maochun/esp32prj/esp-idf/components/bootloader/subproject/main/bootloader_start.c:25
I (29) boot: ESP-IDF v6.0-dev-2039-g2044fba6e7 2nd stage bootloader
I (29) boot: compile time Sep 22 2025 20:38:53
I (29) boot: Multicore bootloader
I (31) boot: chip revision: v0.2
I (34) boot: efuse block revision: v1.3
I (37) boot.esp32s3: Boot SPI Speed : 80MHz
I (41) boot.esp32s3: SPI Mode       : DIO
I (45) boot.esp32s3: SPI Flash Size : 2MB
I (49) boot: Enabling RNG early entropy source...
I (53) boot: Partition Table:
I (56) boot: ## Label            Usage          Type ST Offset   Length
I (62) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (69) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (75) boot:  2 factory          factory app      00 00 00010000 00100000
I (82) boot: End of partition table
I (85) esp_image: segment 0: paddr=00010020 vaddr=3c090020 size=1cad4h (117460) map
I (114) esp_image: segment 1: paddr=0002cafc vaddr=3fc98e00 size=0351ch ( 13596) load
I (117) esp_image: segment 2: paddr=00030020 vaddr=42000020 size=8e110h (581904) map
I (222) esp_image: segment 3: paddr=000be138 vaddr=3fc9c31c size=016e0h (  5856) load
I (223) esp_image: segment 4: paddr=000bf820 vaddr=40374000 size=14d4ch ( 85324) load
I (244) esp_image: segment 5: paddr=000d4574 vaddr=50000000 size=00020h (    32) load
I (254) boot: Loaded app from partition at offset 0x10000
I (254) boot: Disabling RNG early entropy source...
I (264) cpu_start: Multicore app
I (272) cpu_start: GPIO 44 and 43 are used as console UART I/O pins
I (273) cpu_start: Pro cpu start user code
I (273) cpu_start: cpu freq: 160000000 Hz
I (275) app_init: Application information:
I (278) app_init: Project name:     esp32_wifi_control
I (283) app_init: App version:      97eea4e-dirty
I (288) app_init: Compile time:     Sep 22 2025 20:38:30
I (293) app_init: ELF file SHA256:  d1a4a3d79...
I (297) app_init: ESP-IDF:          v6.0-dev-2039-g2044fba6e7
I (303) efuse_init: Min chip rev:     v0.0
I (306) efuse_init: Max chip rev:     v0.99 
I (310) efuse_init: Chip rev:         v0.2
I (314) heap_init: Initializing. RAM available for dynamic allocation:
I (321) heap_init: At 3FCA15E8 len 00048128 (288 KiB): RAM
I (326) heap_init: At 3FCE9710 len 00005724 (21 KiB): RAM
I (331) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (336) heap_init: At 600FE000 len 00001FE8 (7 KiB): RTCRAM
I (343) spi_flash: detected chip: boya
I (345) spi_flash: flash io: dio
W (348) spi_flash: Detected size(16384k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
W (360) i2c: This driver is an old driver, please migrate your application code to adapt `driver/i2c_master.h`
I (370) sleep_gpio: Configure to isolate all GPIO pins in sleep state
I (376) sleep_gpio: Enable automatic switching of GPIO sleep configuration
I (383) main_task: Started on CPU0
I (393) main_task: Calling app_main()
ESP32S3 Boot Success...
ESP_ERROR_CHECK failed: esp_err_t 0x103 (ESP_ERR_INVALID_STATE) at 0x420138b5
--- 0x420138b5: esp_netif_create_default_wifi_ap at /Users/maochun/esp32prj/esp-idf/components/esp_wifi/src/wifi_default.c:410
file: "/IDF/components/esp_wifi/src/wifi_default.c" line 410
func: esp_netif_create_default_wifi_ap
expression: esp_wifi_set_default_wifi_ap_handlers()

abort() was called at PC 0x4037c7af on core 0
--- 0x4037c7af: _esp_error_check_failed at /Users/maochun/esp32prj/esp-idf/components/esp_system/esp_err.c:49


Backtrace: 0x4037c7f1:0x3fca4e30 0x4037c7b9:0x3fca4e50 0x40382955:0x3fca4e70 0x4037c7af:0x3fca4ee0 0x420138b5:0x3fca4f10 0x4200abe3:0x3fca4f40 0x4200a9ac:0x3fca50c0 0x42006964:0x3fca50e0 0x4208adb6:0x3fca5110
--- 0x4037c7f1: panic_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/panic.c:480
--- 0x4037c7b9: esp_system_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/esp_system_chip.c:87
--- 0x40382955: abort at /Users/maochun/esp32prj/esp-idf/components/newlib/src/abort.c:38
--- 0x4037c7af: _esp_error_check_failed at /Users/maochun/esp32prj/esp-idf/components/esp_system/esp_err.c:49
--- 0x420138b5: esp_netif_create_default_wifi_ap at /Users/maochun/esp32prj/esp-idf/components/esp_wifi/src/wifi_default.c:410
--- 0x4200abe3: wifi_init_softap at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/protocol/wifi_ap/wifi_ap.c:17
--- 0x4200a9ac: app_main at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/main/main.c:18
--- 0x42006964: main_task at /Users/maochun/esp32prj/esp-idf/components/freertos/app_startup.c:208
--- 0x4208adb6: vPortTaskWrapper at /Users/maochun/esp32prj/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139




ELF file SHA256: d1a4a3d79

Rebooting...
���ESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0xc (RTC_SW_CPU_RST),boot:0x28 (SPI_FAST_FLASH_BOOT)
Saved PC:0x4037c941
--- 0x4037c941: esp_restart_noos at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/soc/esp32s3/system_internal.c:164
SPIWP:0xee
mode:DIO, clock div:1
load:0x3fce2820,len:0x1588
load:0x403c8700,len:0xd7c
--- 0x403c8700: _stext at ??:?
load:0x403cb700,len:0x2f80
entry 0x403c8908
--- 0x403c8908: call_start_cpu0 at /Users/maochun/esp32prj/esp-idf/components/bootloader/subproject/main/bootloader_start.c:25
I (29) boot: ESP-IDF v6.0-dev-2039-g2044fba6e7 2nd stage bootloader
I (29) boot: compile time Sep 22 2025 20:38:53
I (29) boot: Multicore bootloader
I (31) boot: chip revision: v0.2
I (34) boot: efuse block revision: v1.3
I (37) boot.esp32s3: Boot SPI Speed : 80MHz
I (41) boot.esp32s3: SPI Mode       : DIO
I (45) boot.esp32s3: SPI Flash Size : 2MB
I (49) boot: Enabling RNG early entropy source...
I (53) boot: Partition Table:
I (56) boot: ## Label            Usage          Type ST Offset   Length
I (62) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (69) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (75) boot:  2 factory          factory app      00 00 00010000 00100000
I (82) boot: End of partition table
I (85) esp_image: segment 0: paddr=00010020 vaddr=3c090020 size=1cad4h (117460) map
I (114) esp_image: segment 1: paddr=0002cafc vaddr=3fc98e00 size=0351ch ( 13596) load
I (117) esp_image: segment 2: paddr=00030020 vaddr=42000020 size=8e110h (581904) map
I (222) esp_image: segment 3: paddr=000be138 vaddr=3fc9c31c size=016e0h (  5856) load
I (223) esp_image: segment 4: paddr=000bf820 vaddr=40374000 size=14d4ch ( 85324) load
I (244) esp_image: segment 5: paddr=000d4574 vaddr=50000000 size=00020h (    32) load
I (254) boot: Loaded app from partition at offset 0x10000
I (254) boot: Disabling RNG early entropy source...
I (264) cpu_start: Multicore app
I (272) cpu_start: GPIO 44 and 43 are used as console UART I/O pins
I (273) cpu_start: Pro cpu start user code
I (273) cpu_start: cpu freq: 160000000 Hz
I (275) app_init: Application information:
I (278) app_init: Project name:     esp32_wifi_control
I (283) app_init: App version:      97eea4e-dirty
I (288) app_init: Compile time:     Sep 22 2025 20:38:30
I (293) app_init: ELF file SHA256:  d1a4a3d79...
I (297) app_init: ESP-IDF:          v6.0-dev-2039-g2044fba6e7
I (303) efuse_init: Min chip rev:     v0.0
I (306) efuse_init: Max chip rev:     v0.99 
I (310) efuse_init: Chip rev:         v0.2
I (314) heap_init: Initializing. RAM available for dynamic allocation:
I (321) heap_init: At 3FCA15E8 len 00048128 (288 KiB): RAM
I (326) heap_init: At 3FCE9710 len 00005724 (21 KiB): RAM
I (331) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (336) heap_init: At 600FE000 len 00001FE8 (7 KiB): RTCRAM
I (342) spi_flash: detected chip: boya
I (345) spi_flash: flash io: dio
W (348) spi_flash: Detected size(16384k) larger than the size in the binary image header(2048k). Using the size in the binary image header.