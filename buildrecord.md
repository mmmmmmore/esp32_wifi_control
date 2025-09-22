

ELF file SHA256: 418e3a066

Rebooting...
ESP-ROM:esp32s3-20210327
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
I (29) boot: compile time Sep 19 2025 15:50:55
I (29) boot: Multicore bootloader
I (31) boot: chip revision: v0.2
.I (34) boot: efuse block revision: v1.3
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
I (85) esp_image: segment 0: paddr=00010020 vaddr=3c0a0020 size=1cf74h (118644) map
I (114) esp_image: segment 1: paddr=0002cf9c vaddr=3fc98e00 size=0307ch ( 12412) load
I (117) esp_image: segment 2: paddr=00030020 vaddr=42000020 size=904f4h (591092) map
I (224) esp_image: segment 3: paddr=000c051c vaddr=3fc9be7c size=01b80h (  7040) load
I (225) esp_image: segment 4: paddr=000c20a4 vaddr=40374000 size=14d4ch ( 85324) load
I (246) esp_image: segment 5: paddr=000d6df8 vaddr=50000000 size=00020h (    32) load
I (255) boot: Loaded app from partition at offset 0x10000
I (256) boot: Disabling RNG early entropy source...
I (266) cpu_start: Multicore app
I (274) cpu_start: GPIO 44 and 43 are used as console UART I/O pins
I (275) cpu_start: Pro cpu start user code
I (275) cpu_start: cpu freq: 160000000 Hz
I (276) app_init: Application information:
I (280) app_init: Project name:     esp32_wifi_control
I (285) app_init: App version:      b414e4e-dirty
I (290) app_init: Compile time:     Sep 22 2025 18:30:53
I (295) app_init: ELF file SHA256:  418e3a066...
I (299) app_init: ESP-IDF:          v6.0-dev-2039-g2044fba6e7
I (304) efuse_init: Min chip rev:     v0.0
I (308) efuse_init: Max chip rev:     v0.99 
I (312) efuse_init: Chip rev:         v0.2
I (316) heap_init: Initializing. RAM available for dynamic allocation:
I (322) heap_init: At 3FCA1708 len 00048008 (288 KiB): RAM
I (327) heap_init: At 3FCE9710 len 00005724 (21 KiB): RAM
I (333) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (338) heap_init: At 600FE000 len 00001FE8 (7 KiB): RTCRAM
I (344) spi_flash: detected chip: boya
I (347) spi_flash: flash io: dio
W (350) spi_flash: Detected size(16384k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
W (362) i2c: This driver is an old driver, please migrate your application code to adapt `driver/i2c_master.h`
I (372) sleep_gpio: Configure to isolate all GPIO pins in sleep state
I (378) sleep_gpio: Enable automatic switching of GPIO sleep configuration
I (385) main_task: Started on CPU0
I (395) main_task: Calling app_main()
ESP32S3 Boot Success...
I (415) pp: pp rom version: e7ae62f
I (415) net80211: net80211 rom version: e7ae62f
I (425) wifi:wifi driver task: 3fced4fc, prio:23, stack:6656, core=0
I (425) wifi:wifi firmware version: df85326
I (425) wifi:wifi certification version: v7.0
I (425) wifi:config NVS flash: enabled
I (435) wifi:config nano formatting: disabled
I (435) wifi:Init data frame dynamic rx buffer num: 32
I (435) wifi:Init static rx mgmt buffer num: 5
I (445) wifi:Init management short buffer num: 32
I (445) wifi:Init dynamic tx buffer num: 32
I (455) wifi:Init static tx FG buffer num: 2
I (455) wifi:Init static rx buffer size: 1600
I (455) wifi:Init static rx buffer num: 10
I (465) wifi:Init dynamic rx buffer num: 32
I (465) wifi_init: rx ba win: 6
I (475) wifi_init: accept mbox: 6
I (475) wifi_init: tcpip mbox: 32
I (475) wifi_init: udp mbox: 6
I (475) wifi_init: tcp mbox: 6
I (485) wifi_init: tcp tx win: 5760
I (485) wifi_init: tcp rx win: 5760
I (485) wifi_init: tcp mss: 1440
I (495) wifi_init: WiFi IRAM OP enabled
I (495) wifi_init: WiFi RX IRAM OP enabled
I (505) phy_init: phy_version 701,f4f1da3a,Mar  3 2025,15:50:10
I (545) wifi:mode : softAP (dc:b4:d9:04:7c:05)
I (555) wifi:Total power save buffer number: 16
I (555) wifi:Init max length of beacon: 752/752
I (555) wifi:Init max length of beacon: 752/752
I (555) wifi_ap: WiFi SoftAP started. SSID: ESP32-SoftAP
I (555) esp_netif_lwip: DHCP server started on interface WIFI_AP_DEF with IP: 192.168.4.1
ESP_ERROR_CHECK failed: esp_err_t 0x103 (ESP_ERR_INVALID_STATE) at 0x4200aef4
--- 0x4200aef4: app_main at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/main/main.c:22
file: "./main/main.c" line 22
func: app_main
expression: esp_event_loop_create_default()

abort() was called at PC 0x4037c7af on core 0
--- 0x4037c7af: _esp_error_check_failed at /Users/maochun/esp32prj/esp-idf/components/esp_system/esp_err.c:49


Backtrace: 0x4037c7f1:0x3fca5100 0x4037c7b9:0x3fca5120 0x40382955:0x3fca5140 0x4037c7af:0x3fca51b0 0x4200aef4:0x3fca51e0 0x42006ac0:0x3fca5200 0x4208d09e:0x3fca5230
--- 0x4037c7f1: panic_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/panic.c:480
--- 0x4037c7b9: esp_system_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/esp_system_chip.c:87
--- 0x40382955: abort at /Users/maochun/esp32prj/esp-idf/components/newlib/src/abort.c:38
--- 0x4037c7af: _esp_error_check_failed at /Users/maochun/esp32prj/esp-idf/components/esp_system/esp_err.c:49
--- 0x4200aef4: app_main at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/main/main.c:22
--- 0x42006ac0: main_task at /Users/maochun/esp32prj/esp-idf/components/freertos/app_startup.c:208
--- 0x4208d09e: vPortTaskWrapper at /Users/maochun/esp32prj/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139




ELF file SHA256: 418e3a066
.
Rebooting...
ESP-ROM:esp32s3-20210327
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
I (29) boot: compile time Sep 19 2025 15:50:55
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
I (85) esp_image: segment 0: paddr=00010020 vaddr=3c0a0020 size=1cf74h (118644) map
I (114) esp_image: segment 1: paddr=0002cf9c vaddr=3fc98e00 size=0307ch ( 12412) load
I (117) esp_image: segment 2: paddr=00030020 vaddr=42000020 size=904f4h (591092) map
I (224) esp_image: segment 3: paddr=000c051c vaddr=3fc9be7c size=01b80h (  7040) load
I (225) esp_image: segment 4: paddr=000c20a4 vaddr=40374000 size=14d4ch ( 85324) load
I (246) esp_image: segment 5: paddr=000d6df8 vaddr=50000000 size=00020h (    32) load
I (255) boot: Loaded app from partition at offset 0x10000
I (256) boot: Disabling RNG early entropy source...
I (266) cpu_start: Multicore app
I (274) cpu_start: GPIO 44 and 43 are used as console UART I/O pins
I (275) cpu_start: Pro cpu start user code
I (275) cpu_start: cpu freq: 160000000 Hz
I (276) app_init: Application information:
I (280) app_init: Project name:     esp32_wifi_control
I (285) app_init: App version:      b414e4e-dirty
I (290) app_init: Compile time:     Sep 22 2025 18:30:53
I (295) app_init: ELF file SHA256:  418e3a066...
I (299) app_init: ESP-IDF:          v6.0-dev-2039-g2044fba6e7
I (304) efuse_init: Min chip rev:     v0.0
I (308) efuse_init: Max chip rev:     v0.99 
I (312) efuse_init: Chip rev:         v0.2
I (316) heap_init: Initializing. RAM available for dynamic allocation:
I (322) heap_init: At 3FCA1708 len 00048008 (288 KiB): RAM
I (327) heap_init: At 3FCE9710 len 00005724 (21 KiB): RAM
I (333) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (338) heap_init: At 600FE000 len 00001FE8 (7 KiB): RTCRAM
I (344) spi_flash: detected chip: boya
I (347) spi_flash: flash io: dio
W (350) spi_flash: Detected size(16384k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
W (362) i2c: This driver is an old driver, please migrate your application code to adapt `driver/i2c_master.h`
I (372) sleep_gpio: Configure to isolate all GPIO pins in sleep state
I (378) sleep_gpio: Enable automatic switching of GPIO sleep configuration
I (385) main_task: Started on CPU0
I (395) main_task: Calling app_main()
ESP32S3 Boot Success...
I (415) pp: pp rom version: e7ae62f
I (415) net80211: net80211 rom version: e7ae62f
I (425) wifi:wifi driver task: 3fced4fc, prio:23, stack:6656, core=0
I (425) wifi:wifi firmware version: df85326
I (425) wifi:wifi certification version: v7.0
I (425) wifi:config NVS flash: enabled
I (435) wifi:config nano formatting: disabled
I (435) wifi:Init data frame dynamic rx buffer num: 32
I (435) wifi:Init static rx mgmt buffer num: 5
I (445) wifi:Init management short buffer num: 32
I (445) wifi:Init dynamic tx buffer num: 32
I (455) wifi:Init static tx FG buffer num: 2
I (455) wifi:Init static rx buffer size: 1600
I (455) wifi:Init static rx buffer num: 10
I (465) wifi:Init dynamic rx buffer num: 32
I (465) wifi_init: rx ba win: 6
I (475) wifi_init: accept mbox: 6
I (475) wifi_init: tcpip mbox: 32
I (475) wifi_init: udp mbox: 6
I (475) wifi_init: tcp mbox: 6
I (485) wifi_init: tcp tx win: 5760
I (485) wifi_init: tcp rx win: 5760
I (485) wifi_init: tcp mss: 1440
I (495) wifi_init: WiFi IRAM OP enabled
I (495) wifi_init: WiFi RX IRAM OP enabled
I (505) phy_init: phy_version 701,f4f1da3a,Mar  3 2025,15:50:10
I (545) wifi:mode : softAP (dc:b4:d9:04:7c:05)
I (545) wifi:Total power save buffer number: 16
I (555) wifi:Init max length of beacon: 752/752
I (555) wifi:Init max length of beacon: 752/752
I (555) wifi_ap: WiFi SoftAP started. SSID: ESP32-SoftAP
I (555) esp_netif_lwip: DHCP server started on interface WIFI_AP_DEF with IP: 192.168.4.1
ESP_ERROR_CHECK failed: esp_err_t 0x103 (ESP_ERR_INVALID_STATE) at 0x4200aef4
--- 0x4200aef4: app_main at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/main/main.c:22
file: "./main/main.c" line 22
func: app_main
expression: esp_event_loop_create_default()

abort() was called at PC 0x4037c7af on core 0
--- 0x4037c7af: _esp_error_check_failed at /Users/maochun/esp32prj/esp-idf/components/esp_system/esp_err.c:49


Backtrace: 0x4037c7f1:0x3fca5100 0x4037c7b9:0x3fca5120 0x40382955:0x3fca5140 0x4037c7af:0x3fca51b0 0x4200aef4:0x3fca51e0 0x42006ac0:0x3fca5200 0x4208d09e:0x3fca5230
.--- 0x4037c7f1: panic_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/panic.c:480
--- 0x4037c7b9: esp_system_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/esp_system_chip.c:87
--- 0x40382955: abort at /Users/maochun/esp32prj/esp-idf/components/newlib/src/abort.c:38
--- 0x4037c7af: _esp_error_check_failed at /Users/maochun/esp32prj/esp-idf/components/esp_system/esp_err.c:49
--- 0x4200aef4: app_main at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/main/main.c:22
--- 0x42006ac0: main_task at /Users/maochun/esp32prj/esp-idf/components/freertos/app_startup.c:208
--- 0x4208d09e: vPortTaskWrapper at /Users/maochun/esp32prj/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139




ELF file SHA256: 418e3a066
