 (62) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (69) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (75) boot:  2 factory          factory app      00 00 00010000 00100000
I (82) boot: End of partition table
I (85) esp_image: segment 0: paddr=00010020 vaddr=3c090020 size=1b248h (111176) map
I (112) esp_image: segment 1: paddr=0002b270 vaddr=3fc98e00 size=04bech ( 19436) load
I (117) esp_image: segment 2: paddr=0002fe64 vaddr=40374000 size=001b4h (   436) load
I (117) esp_image: segment 3: paddr=00030020 vaddr=42000020 size=870a0h (553120) map
I (223) esp_image: segment 4: paddr=000b70c8 vaddr=403741b4 size=14b5ch ( 84828) load
I (242) esp_image: segment 5: paddr=000cbc2c vaddr=50000000 size=00020h (    32) load
I (251) boot: Loaded app from partition at offset 0x10000
I (251) boot: Disabling RNG early entropy source...
I (261) cpu_start: Multicore app
I (270) cpu_start: GPIO 44 and 43 are used as console UART I/O pins
I (271) cpu_start: Pro cpu start user code
I (271) cpu_start: cpu freq: 160000000 Hz
I (272) app_init: Application information:
I (276) app_init: Project name:     esp32_wifi_control
I (281) app_init: App version:      c0cfc69-dirty
I (285) app_init: Compile time:     Sep 19 2025 15:33:14
I (290) app_init: ELF file SHA256:  1c705fd7e...
I (295) app_init: ESP-IDF:          v6.0-dev-2039-g2044fba6e7
I (300) efuse_init: Min chip rev:     v0.0
I (304) efuse_init: Max chip rev:     v0.99 
I (308) efuse_init: Chip rev:         v0.2
I (312) heap_init: Initializing. RAM available for dynamic allocation:
I (318) heap_init: At 3FCA1410 len 00048300 (288 KiB): RAM
I (323) heap_init: At 3FCE9710 len 00005724 (21 KiB): RAM
I (328) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (333) heap_init: At 600FE000 len 00001FE8 (7 KiB): RTCRAM
I (340) spi_flash: detected chip: boya
I (342) spi_flash: flash io: dio
W (345) spi_flash: Detected size(16384k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
W (358) i2c: This driver is an old driver, please migrate your application code to adapt `driver/i2c_master.h`
I (367) sleep_gpio: Configure to isolate all GPIO pins in sleep state
I (374) sleep_gpio: Enable automatic switching of GPIO sleep configuration
I (381) main_task: Started on CPU0
I (391) main_task: Calling app_main()
ESP32S3 Boot Success...
I (411) pp: pp rom version: e7ae62f
I (411) net80211: net80211 rom version: e7ae62f
I (421) wifi:wifi driver task: 3fcec904, prio:23, stack:6656, core=0
I (421) wifi:wifi firmware version: df85326
I (421) wifi:wifi certification version: v7.0
I (421) wifi:config NVS flash: enabled
I (421) wifi:config nano formatting: disabled
I (431) wifi:Init data frame dynamic rx buffer num: 32
I (431) wifi:Init static rx mgmt buffer num: 5
I (441) wifi:Init management short buffer num: 32
I (441) wifi:Init dynamic tx buffer num: 32
I (451) wifi:Init static tx FG buffer num: 2
I (451) wifi:Init static rx buffer size: 1600
I (451) wifi:Init static rx buffer num: 10
I (461) wifi:Init dynamic rx buffer num: 32
I (461) wifi_init: rx ba win: 6
I (461) wifi_init: accept mbox: 6
I (471) wifi_init: tcpip mbox: 32
I (471) wifi_init: udp mbox: 6
I (471) wifi_init: tcp mbox: 6
I (481) wifi_init: tcp tx win: 5760
I (481) wifi_init: tcp rx win: 5760
I (481) wifi_init: tcp mss: 1440
I (491) wifi_init: WiFi IRAM OP enabled
I (491) wifi_init: WiFi RX IRAM OP enabled
I (501) phy_init: phy_version 701,f4f1da3a,Mar  3 2025,15:50:10
E (541) wifi:failed to post WiFi event=43 ret=259
I (541) wifi:mode : softAP (dc:b4:d9:04:7c:05)
I (541) wifi:Total power save buffer number: 16
I (541) wifi:Init max length of beacon: 752/752
I (551) wifi:Init max length of beacon: 752/752
E (551) wifi:failed to post WiFi event=12 ret=259
I (551) wifi_ap: WiFi SoftAP started. SSID: ESP32-SoftAP
I (611) OV7670: OV7670 initialized

assert failed: tcpip_send_msg_wait_sem /IDF/components/lwip/lwip/src/api/tcpip.c:454 (Invalid mbox)


Backtrace: 0x4037c7e5:0x3fca4b90 0x4037c7ad:0x3fca4bb0 0x40382a31:0x3fca4bd0 0x42053953:0x3fca4cf0 0x4205f67e:0x3fca4d20 0x4205f712:0x3fca4d40 0x420537a1:0x3fca4d90 0x42014669:0x3fca4db0 0x42014d34:0x3fca4e10 0x4200a8b8:0x3fca4e40 0x4200a7aa:0x3fca4ef0 0x420067b0:0x3fca4f10 0x42083ef6:0x3fca4f40
--- 0x4037c7e5: panic_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/panic.c:480
--- 0x4037c7ad: esp_system_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/esp_system_chip.c:87
--- 0x40382a31: __assert_func at /Users/maochun/esp32prj/esp-idf/components/newlib/src/assert.c:81
--- 0x42053953: tcpip_send_msg_wait_sem at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/tcpip.c:454
--- 0x4205f67e: netconn_apimsg at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/api_lib.c:134
--- 0x4205f712: netconn_new_with_proto_and_callback at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/api_lib.c:164
--- 0x420537a1: lwip_socket at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/sockets.c:1759
--- 0x42014669: socket at /Users/maochun/esp32prj/esp-idf/components/lwip/include/lwip/sockets.h:70
--- (inlined by) httpd_server_init at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/esp_http_server/src/httpd_main.c:358
--- 0x42014d34: httpd_start at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/esp_http_server/src/httpd_main.c:525
--- 0x4200a8b8: start_webserver at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/protocol/webserver/webserver.c:41
--- 0x4200a7aa: app_main at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/main/main.c:21
--- 0x420067b0: main_task at /Users/maochun/esp32prj/esp-idf/components/freertos/app_startup.c:208
--- 0x42083ef6: vPortTaskWrapper at /Users/maochun/esp32prj/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139




ELF file SHA256: 1c705fd7e

Rebooting...
���ESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0xc (RTC_SW_CPU_RST),boot:0x8 (SPI_FAST_FLASH_BOOT)
Saved PC:0x4037c935
--- 0x4037c935: esp_restart_noos at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/soc/esp32s3/system_internal.c:164
SPIWP:0xee
mode:DIO, clock div:1
load:0x3fce2820,len:0x1588
load:0x403c8700,len:0xd7c
--- 0x403c8700: _stext at ??:?
load:0x403cb700,len:0x2f80
entry 0x403c8908
--- 0x403c8908: call_start_cpu0 at /Users/maochun/esp32prj/esp-idf/components/bootloader/subproject/main/bootloader_start.c:25
I (29) boot: ESP-IDF v6.0-dev-2039-g2044fba6e7 2nd stage bootloader
I (29) boot: compile time Sep 19 2025 15:33:39
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
I (85) esp_image: segment 0: paddr=00010020 vaddr=3c090020 size=1b248h (111176) map
I (112) esp_image: segment 1: paddr=0002b270 vaddr=3fc98e00 size=04bech ( 19436) load
I (117) esp_image: segment 2: paddr=0002fe64 vaddr=40374000 size=001b4h (   436) load
I (117) esp_image: segment 3: paddr=00030020 vaddr=42000020 size=870a0h (553120) map
I (223) esp_image: segment 4: paddr=000b70c8 vaddr=403741b4 size=14b5ch ( 84828) load
I (242) esp_image: segment 5: paddr=000cbc2c vaddr=50000000 size=00020h (    32) load
I (251) boot: Loaded app from partition at offset 0x10000
I (251) boot: Disabling RNG early entropy source...
I (261) cpu_start: Multicore app
I (270) cpu_start: GPIO 44 and 43 are used as console UART I/O pins
I (271) cpu_start: Pro cpu start user code
I (271) cpu_start: cpu freq: 160000000 Hz
I (272) app_init: Application information:
I (276) app_init: Project name:     esp32_wifi_control
I (281) app_init: App version:      c0cfc69-dirty
I (285) app_init: Compile time:     Sep 19 2025 15:33:14
I (290) app_init: ELF file SHA256:  1c705fd7e...
I (295) app_init: ESP-IDF:          v6.0-dev-2039-g2044fba6e7
I (300) efuse_init: Min chip rev:     v0.0
I (304) efuse_init: Max chip rev:     v0.99 
I (308) efuse_init: Chip rev:         v0.2
I (312) heap_init: Initializing. RAM available for dynamic allocation:
I (318) heap_init: At 3FCA1410 len 00048300 (288 KiB): RAM
I (323) heap_init: At 3FCE9710 len 00005724 (21 KiB): RAM
I (328) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (333) heap_init: At 600FE000 len 00001FE8 (7 KiB): RTCRAM
I (340) spi_flash: detected chip: boya
I (342) spi_flash: flash io: dio
W (345) spi_flash: Detected size(16384k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
W (358) i2c: This driver is an old driver, please migrate your application code to adapt `driver/i2c_master.h`
I (367) sleep_gpio: Configure to isolate all GPIO pins in sleep state
I (374) sleep_gpio: Enable automatic switching of GPIO sleep configuration
I (381) main_task: Started on CPU0
I (391) main_task: Calling app_main()
ESP32S3 Boot Success...
I (411) pp: pp rom version: e7ae62f
I (411) net80211: net80211 rom version: e7ae62f
I (421) wifi:wifi driver task: 3fcec904, prio:23, stack:6656, core=0
I (421) wifi:wifi firmware version: df85326
I (421) wifi:wifi certification version: v7.0
I (421) wifi:config NVS flash: enabled
I (421) wifi:config nano formatting: disabled
I (431) wifi:Init data frame dynamic rx buffer num: 32
I (431) wifi:Init static rx mgmt buffer num: 5
I (441) wifi:Init management short buffer num: 32
I (441) wifi:Init dynamic tx buffer num: 32
I (451) wifi:Init static tx FG buffer num: 2
I (451) wifi:Init static rx buffer size: 1600
I (451) wifi:Init static rx buffer num: 10
I (461) wifi:Init dynamic rx buffer num: 32
I (461) wifi_init: rx ba win: 6
I (461) wifi_init: accept mbox: 6
I (471) wifi_init: tcpip mbox: 32
I (471) wifi_init: udp mbox: 6
I (471) wifi_init: tcp mbox: 6
I (481) wifi_init: tcp tx win: 5760
I (481) wifi_init: tcp rx win: 5760
I (481) wifi_init: tcp mss: 1440
I (491) wifi_init: WiFi IRAM OP enabled
I (491) wifi_init: WiFi RX IRAM OP enabled
I (501) phy_init: phy_version 701,f4f1da3a,Mar  3 2025,15:50:10
E (541) wifi:failed to post WiFi event=43 ret=259
I (541) wifi:mode : softAP (dc:b4:d9:04:7c:05)
I (541) wifi:Total power save buffer number: 16
I (551) wifi:Init max length of beacon: 752/752
I (551) wifi:Init max length of beacon: 752/752
E (551) wifi:failed to post WiFi event=12 ret=259
I (551) wifi_ap: WiFi SoftAP started. SSID: ESP32-SoftAP
I (611) OV7670: OV7670 initialized

assert failed: tcpip_send_msg_wait_sem /IDF/components/lwip/lwip/src/api/tcpip.c:454 (Invalid mbox)


Backtrace: 0x4037c7e5:0x3fca4b90 0x4037c7ad:0x3fca4bb0 0x40382a31:0x3fca4bd0 0x42053953:0x3fca4cf0 0x4205f67e:0x3fca4d20 0x4205f712:0x3fca4d40 0x420537a1:0x3fca4d90 0x42014669:0x3fca4db0 0x42014d34:0x3fca4e10 0x4200a8b8:0x3fca4e40 0x4200a7aa:0x3fca4ef0 0x420067b0:0x3fca4f10 0x42083ef6:0x3fca4f40
--- 0x4037c7e5: panic_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/panic.c:480
--- 0x4037c7ad: esp_system_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/esp_system_chip.c:87
--- 0x40382a31: __assert_func at /Users/maochun/esp32prj/esp-idf/components/newlib/src/assert.c:81
--- 0x42053953: tcpip_send_msg_wait_sem at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/tcpip.c:454
--- 0x4205f67e: netconn_apimsg at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/api_lib.c:134
--- 0x4205f712: netconn_new_with_proto_and_callback at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/api_lib.c:164
--- 0x420537a1: lwip_socket at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/sockets.c:1759
--- 0x42014669: socket at /Users/maochun/esp32prj/esp-idf/components/lwip/include/lwip/sockets.h:70
--- (inlined by) httpd_server_init at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/esp_http_server/src/httpd_main.c:358
--- 0x42014d34: httpd_start at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/esp_http_server/src/httpd_main.c:525
--- 0x4200a8b8: start_webserver at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/protocol/webserver/webserver.c:41
--- 0x4200a7aa: app_main at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/main/main.c:21
--- 0x420067b0: main_task at /Users/maochun/esp32prj/esp-idf/components/freertos/app_startup.c:208
--- 0x42083ef6: vPortTaskWrapper at /Users/maochun/esp32prj/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139




ELF file SHA256: 1c705fd7e

Rebooting...
���ESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0xc (RTC_SW_CPU_RST),boot:0x8 (SPI_FAST_FLASH_BOOT)
Saved PC:0x4037c935
--- 0x4037c935: esp_restart_noos at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/soc/esp32s3/system_internal.c:164
SPIWP:0xee
mode:DIO, clock div:1
load:0x3fce2820,len:0x1588
load:0x403c8700,len:0xd7c
--- 0x403c8700: _stext at ??:?
load:0x403cb700,len:0x2f80
entry 0x403c8908
--- 0x403c8908: call_start_cpu0 at /Users/maochun/esp32prj/esp-idf/components/bootloader/subproject/main/bootloader_start.c:25
I (29) boot: ESP-IDF v6.0-dev-2039-g2044fba6e7 2nd stage bootloader
I (29) boot: compile time Sep 19 2025 15:33:39
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
I (85) esp_image: segment 0: paddr=00010020 vaddr=3c090020 size=1b248h (111176) map
I (112) esp_image: segment 1: paddr=0002b270 vaddr=3fc98e00 size=04bech ( 19436) load
I (117) esp_image: segment 2: paddr=0002fe64 vaddr=40374000 size=001b4h (   436) load
I (117) esp_image: segment 3: paddr=00030020 vaddr=42000020 size=870a0h (553120) map
I (223) esp_image: segment 4: paddr=000b70c8 vaddr=403741b4 size=14b5ch ( 84828) load
I (242) esp_image: segment 5: paddr=000cbc2c vaddr=50000000 size=00020h (    32) load
I (251) boot: Loaded app from partition at offset 0x10000
I (251) boot: Disabling RNG early entropy source...
I (261) cpu_start: Multicore app
I (270) cpu_start: GPIO 44 and 43 are used as console UART I/O pins
I (271) cpu_start: Pro cpu start user code
I (271) cpu_start: cpu freq: 160000000 Hz
I (272) app_init: Application information:
I (276) app_init: Project name:     esp32_wifi_control
I (281) app_init: App version:      c0cfc69-dirty
I (285) app_init: Compile time:     Sep 19 2025 15:33:14
I (290) app_init: ELF file SHA256:  1c705fd7e...
I (295) app_init: ESP-IDF:          v6.0-dev-2039-g2044fba6e7
I (300) efuse_init: Min chip rev:     v0.0
I (304) efuse_init: Max chip rev:     v0.99 
I (308) efuse_init: Chip rev:         v0.2
I (312) heap_init: Initializing. RAM available for dynamic allocation:
I (318) heap_init: At 3FCA1410 len 00048300 (288 KiB): RAM
I (323) heap_init: At 3FCE9710 len 00005724 (21 KiB): RAM
I (328) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (333) heap_init: At 600FE000 len 00001FE8 (7 KiB): RTCRAM
I (340) spi_flash: detected chip: boya
I (342) spi_flash: flash io: dio
W (345) spi_flash: Detected size(16384k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
W (358) i2c: This driver is an old driver, please migrate your application code to adapt `driver/i2c_master.h`
I (367) sleep_gpio: Configure to isolate all GPIO pins in sleep state
I (374) sleep_gpio: Enable automatic switching of GPIO sleep configuration
I (381) main_task: Started on CPU0
I (391) main_task: Calling app_main()
ESP32S3 Boot Success...
I (411) pp: pp rom version: e7ae62f
I (411) net80211: net80211 rom version: e7ae62f
I (421) wifi:wifi driver task: 3fcec904, prio:23, stack:6656, core=0
I (421) wifi:wifi firmware version: df85326
I (421) wifi:wifi certification version: v7.0
I (421) wifi:config NVS flash: enabled
I (421) wifi:config nano formatting: disabled
I (431) wifi:Init data frame dynamic rx buffer num: 32
I (431) wifi:Init static rx mgmt buffer num: 5
I (441) wifi:Init management short buffer num: 32
I (441) wifi:Init dynamic tx buffer num: 32
I (451) wifi:Init static tx FG buffer num: 2
I (451) wifi:Init static rx buffer size: 1600
I (451) wifi:Init static rx buffer num: 10
I (461) wifi:Init dynamic rx buffer num: 32
I (461) wifi_init: rx ba win: 6
I (461) wifi_init: accept mbox: 6
I (471) wifi_init: tcpip mbox: 32
I (471) wifi_init: udp mbox: 6
I (471) wifi_init: tcp mbox: 6
I (481) wifi_init: tcp tx win: 5760
I (481) wifi_init: tcp rx win: 5760
I (481) wifi_init: tcp mss: 1440
I (491) wifi_init: WiFi IRAM OP enabled
I (491) wifi_init: WiFi RX IRAM OP enabled
I (501) phy_init: phy_version 701,f4f1da3a,Mar  3 2025,15:50:10
E (541) wifi:failed to post WiFi event=43 ret=259
I (541) wifi:mode : softAP (dc:b4:d9:04:7c:05)
I (541) wifi:Total power save buffer number: 16
I (541) wifi:Init max length of beacon: 752/752
I (541) wifi:Init max length of beacon: 752/752
E (551) wifi:failed to post WiFi event=12 ret=259
I (551) wifi_ap: WiFi SoftAP started. SSID: ESP32-SoftAP
I (611) OV7670: OV7670 initialized

assert failed: tcpip_send_msg_wait_sem /IDF/components/lwip/lwip/src/api/tcpip.c:454 (Invalid mbox)


Backtrace: 0x4037c7e5:0x3fca4b90 0x4037c7ad:0x3fca4bb0 0x40382a31:0x3fca4bd0 0x42053953:0x3fca4cf0 0x4205f67e:0x3fca4d20 0x4205f712:0x3fca4d40 0x420537a1:0x3fca4d90 0x42014669:0x3fca4db0 0x42014d34:0x3fca4e10 0x4200a8b8:0x3fca4e40 0x4200a7aa:0x3fca4ef0 0x420067b0:0x3fca4f10 0x42083ef6:0x3fca4f40
--- 0x4037c7e5: panic_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/panic.c:480
--- 0x4037c7ad: esp_system_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/esp_system_chip.c:87
--- 0x40382a31: __assert_func at /Users/maochun/esp32prj/esp-idf/components/newlib/src/assert.c:81
--- 0x42053953: tcpip_send_msg_wait_sem at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/tcpip.c:454
--- 0x4205f67e: netconn_apimsg at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/api_lib.c:134
--- 0x4205f712: netconn_new_with_proto_and_callback at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/api_lib.c:164
--- 0x420537a1: lwip_socket at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/sockets.c:1759
--- 0x42014669: socket at /Users/maochun/esp32prj/esp-idf/components/lwip/include/lwip/sockets.h:70
--- (inlined by) httpd_server_init at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/esp_http_server/src/httpd_main.c:358
--- 0x42014d34: httpd_start at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/esp_http_server/src/httpd_main.c:525
--- 0x4200a8b8: start_webserver at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/protocol/webserver/webserver.c:41
--- 0x4200a7aa: app_main at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/main/main.c:21
--- 0x420067b0: main_task at /Users/maochun/esp32prj/esp-idf/components/freertos/app_startup.c:208
--- 0x42083ef6: vPortTaskWrapper at /Users/maochun/esp32prj/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139




ELF file SHA256: 1c705fd7e

Rebooting...
���ESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0xc (RTC_SW_CPU_RST),boot:0x8 (SPI_FAST_FLASH_BOOT)
Saved PC:0x4037c935
--- 0x4037c935: esp_restart_noos at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/soc/esp32s3/system_internal.c:164
SPIWP:0xee
mode:DIO, clock div:1
load:0x3fce2820,len:0x1588
load:0x403c8700,len:0xd7c
--- 0x403c8700: _stext at ??:?
load:0x403cb700,len:0x2f80
entry 0x403c8908
--- 0x403c8908: call_start_cpu0 at /Users/maochun/esp32prj/esp-idf/components/bootloader/subproject/main/bootloader_start.c:25
I (29) boot: ESP-IDF v6.0-dev-2039-g2044fba6e7 2nd stage bootloader
I (29) boot: compile time Sep 19 2025 15:33:39
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
I (85) esp_image: segment 0: paddr=00010020 vaddr=3c090020 size=1b248h (111176) map
I (112) esp_image: segment 1: paddr=0002b270 vaddr=3fc98e00 size=04bech ( 19436) load
I (117) esp_image: segment 2: paddr=0002fe64 vaddr=40374000 size=001b4h (   436) load
I (117) esp_image: segment 3: paddr=00030020 vaddr=42000020 size=870a0h (553120) map
I (223) esp_image: segment 4: paddr=000b70c8 vaddr=403741b4 size=14b5ch ( 84828) load
I (242) esp_image: segment 5: paddr=000cbc2c vaddr=50000000 size=00020h (    32) load
I (251) boot: Loaded app from partition at offset 0x10000
I (251) boot: Disabling RNG early entropy source...
I (261) cpu_start: Multicore app
I (270) cpu_start: GPIO 44 and 43 are used as console UART I/O pins
I (271) cpu_start: Pro cpu start user code
I (271) cpu_start: cpu freq: 160000000 Hz
I (272) app_init: Application information:
I (276) app_init: Project name:     esp32_wifi_control
I (281) app_init: App version:      c0cfc69-dirty
I (285) app_init: Compile time:     Sep 19 2025 15:33:14
I (290) app_init: ELF file SHA256:  1c705fd7e...
I (295) app_init: ESP-IDF:          v6.0-dev-2039-g2044fba6e7
I (300) efuse_init: Min chip rev:     v0.0
I (304) efuse_init: Max chip rev:     v0.99 
I (308) efuse_init: Chip rev:         v0.2
I (312) heap_init: Initializing. RAM available for dynamic allocation:
I (318) heap_init: At 3FCA1410 len 00048300 (288 KiB): RAM
I (323) heap_init: At 3FCE9710 len 00005724 (21 KiB): RAM
I (328) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (333) heap_init: At 600FE000 len 00001FE8 (7 KiB): RTCRAM
I (340) spi_flash: detected chip: boya
I (342) spi_flash: flash io: dio
W (345) spi_flash: Detected size(16384k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
W (358) i2c: This driver is an old driver, please migrate your application code to adapt `driver/i2c_master.h`
I (367) sleep_gpio: Configure to isolate all GPIO pins in sleep state
I (374) sleep_gpio: Enable automatic switching of GPIO sleep configuration
I (381) main_task: Started on CPU0
I (391) main_task: Calling app_main()
ESP32S3 Boot Success...
I (411) pp: pp rom version: e7ae62f
I (411) net80211: net80211 rom version: e7ae62f
I (421) wifi:wifi driver task: 3fcec904, prio:23, stack:6656, core=0
I (421) wifi:wifi firmware version: df85326
I (421) wifi:wifi certification version: v7.0
I (421) wifi:config NVS flash: enabled
I (421) wifi:config nano formatting: disabled
I (431) wifi:Init data frame dynamic rx buffer num: 32
I (431) wifi:Init static rx mgmt buffer num: 5
I (441) wifi:Init management short buffer num: 32
I (441) wifi:Init dynamic tx buffer num: 32
I (451) wifi:Init static tx FG buffer num: 2
I (451) wifi:Init static rx buffer size: 1600
I (451) wifi:Init static rx buffer num: 10
I (461) wifi:Init dynamic rx buffer num: 32
I (461) wifi_init: rx ba win: 6
I (461) wifi_init: accept mbox: 6
I (471) wifi_init: tcpip mbox: 32
I (471) wifi_init: udp mbox: 6
I (471) wifi_init: tcp mbox: 6
I (481) wifi_init: tcp tx win: 5760
I (481) wifi_init: tcp rx win: 5760
I (481) wifi_init: tcp mss: 1440
I (491) wifi_init: WiFi IRAM OP enabled
I (491) wifi_init: WiFi RX IRAM OP enabled
I (501) phy_init: phy_version 701,f4f1da3a,Mar  3 2025,15:50:10
E (551) wifi:failed to post WiFi event=43 ret=259
I (551) wifi:mode : softAP (dc:b4:d9:04:7c:05)
I (551) wifi:Total power save buffer number: 16
I (551) wifi:Init max length of beacon: 752/752
I (551) wifi:Init max length of beacon: 752/752
E (561) wifi:failed to post WiFi event=12 ret=259
I (561) wifi_ap: WiFi SoftAP started. SSID: ESP32-SoftAP
I (621) OV7670: OV7670 initialized

assert failed: tcpip_send_msg_wait_sem /IDF/components/lwip/lwip/src/api/tcpip.c:454 (Invalid mbox)


Backtrace: 0x4037c7e5:0x3fca4b90 0x4037c7ad:0x3fca4bb0 0x40382a31:0x3fca4bd0 0x42053953:0x3fca4cf0 0x4205f67e:0x3fca4d20 0x4205f712:0x3fca4d40 0x420537a1:0x3fca4d90 0x42014669:0x3fca4db0 0x42014d34:0x3fca4e10 0x4200a8b8:0x3fca4e40 0x4200a7aa:0x3fca4ef0 0x420067b0:0x3fca4f10 0x42083ef6:0x3fca4f40
--- 0x4037c7e5: panic_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/panic.c:480
--- 0x4037c7ad: esp_system_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/esp_system_chip.c:87
--- 0x40382a31: __assert_func at /Users/maochun/esp32prj/esp-idf/components/newlib/src/assert.c:81
--- 0x42053953: tcpip_send_msg_wait_sem at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/tcpip.c:454
--- 0x4205f67e: netconn_apimsg at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/api_lib.c:134
--- 0x4205f712: netconn_new_with_proto_and_callback at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/api_lib.c:164
--- 0x420537a1: lwip_socket at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/sockets.c:1759
--- 0x42014669: socket at /Users/maochun/esp32prj/esp-idf/components/lwip/include/lwip/sockets.h:70
--- (inlined by) httpd_server_init at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/esp_http_server/src/httpd_main.c:358
--- 0x42014d34: httpd_start at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/esp_http_server/src/httpd_main.c:525
--- 0x4200a8b8: start_webserver at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/protocol/webserver/webserver.c:41
--- 0x4200a7aa: app_main at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/main/main.c:21
--- 0x420067b0: main_task at /Users/maochun/esp32prj/esp-idf/components/freertos/app_startup.c:208
--- 0x42083ef6: vPortTaskWrapper at /Users/maochun/esp32prj/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139




ELF file SHA256: 1c705fd7e

Rebooting...
���ESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0xc (RTC_SW_CPU_RST),boot:0x8 (SPI_FAST_FLASH_BOOT)
Saved PC:0x4037c935
--- 0x4037c935: esp_restart_noos at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/soc/esp32s3/system_internal.c:164
SPIWP:0xee
mode:DIO, clock div:1
load:0x3fce2820,len:0x1588
load:0x403c8700,len:0xd7c
--- 0x403c8700: _stext at ??:?
load:0x403cb700,len:0x2f80
entry 0x403c8908
--- 0x403c8908: call_start_cpu0 at /Users/maochun/esp32prj/esp-idf/components/bootloader/subproject/main/bootloader_start.c:25
I (29) boot: ESP-IDF v6.0-dev-2039-g2044fba6e7 2nd stage bootloader
I (29) boot: compile time Sep 19 2025 15:33:39
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
I (85) esp_image: segment 0: paddr=00010020 vaddr=3c090020 size=1b248h (111176) map
I (112) esp_image: segment 1: paddr=0002b270 vaddr=3fc98e00 size=04bech ( 19436) load
I (117) esp_image: segment 2: paddr=0002fe64 vaddr=40374000 size=001b4h (   436) load
I (117) esp_image: segment 3: paddr=00030020 vaddr=42000020 size=870a0h (553120) map
I (223) esp_image: segment 4: paddr=000b70c8 vaddr=403741b4 size=14b5ch ( 84828) load
I (242) esp_image: segment 5: paddr=000cbc2c vaddr=50000000 size=00020h (    32) load
I (251) boot: Loaded app from partition at offset 0x10000
I (251) boot: Disabling RNG early entropy source...
I (261) cpu_start: Multicore app
I (270) cpu_start: GPIO 44 and 43 are used as console UART I/O pins
I (271) cpu_start: Pro cpu start user code
I (271) cpu_start: cpu freq: 160000000 Hz
I (272) app_init: Application information:
I (276) app_init: Project name:     esp32_wifi_control
I (281) app_init: App version:      c0cfc69-dirty
I (285) app_init: Compile time:     Sep 19 2025 15:33:14
I (290) app_init: ELF file SHA256:  1c705fd7e...
I (295) app_init: ESP-IDF:          v6.0-dev-2039-g2044fba6e7
I (300) efuse_init: Min chip rev:     v0.0
I (304) efuse_init: Max chip rev:     v0.99 
I (308) efuse_init: Chip rev:         v0.2
I (312) heap_init: Initializing. RAM available for dynamic allocation:
I (318) heap_init: At 3FCA1410 len 00048300 (288 KiB): RAM
I (323) heap_init: At 3FCE9710 len 00005724 (21 KiB): RAM
I (328) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (333) heap_init: At 600FE000 len 00001FE8 (7 KiB): RTCRAM
I (340) spi_flash: detected chip: boya
I (342) spi_flash: flash io: dio
W (345) spi_flash: Detected size(16384k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
W (358) i2c: This driver is an old driver, please migrate your application code to adapt `driver/i2c_master.h`
I (367) sleep_gpio: Configure to isolate all GPIO pins in sleep state
I (374) sleep_gpio: Enable automatic switching of GPIO sleep configuration
I (381) main_task: Started on CPU0
I (391) main_task: Calling app_main()
ESP32S3 Boot Success...
I (411) pp: pp rom version: e7ae62f
I (411) net80211: net80211 rom version: e7ae62f
I (421) wifi:wifi driver task: 3fcec904, prio:23, stack:6656, core=0
I (421) wifi:wifi firmware version: df85326
I (421) wifi:wifi certification version: v7.0
I (421) wifi:config NVS flash: enabled
I (421) wifi:config nano formatting: disabled
I (431) wifi:Init data frame dynamic rx buffer num: 32
I (431) wifi:Init static rx mgmt buffer num: 5
I (441) wifi:Init management short buffer num: 32
I (441) wifi:Init dynamic tx buffer num: 32
I (451) wifi:Init static tx FG buffer num: 2
I (451) wifi:Init static rx buffer size: 1600
I (451) wifi:Init static rx buffer num: 10
I (461) wifi:Init dynamic rx buffer num: 32
I (461) wifi_init: rx ba win: 6
I (461) wifi_init: accept mbox: 6
I (471) wifi_init: tcpip mbox: 32
I (471) wifi_init: udp mbox: 6
I (471) wifi_init: tcp mbox: 6
I (481) wifi_init: tcp tx win: 5760
I (481) wifi_init: tcp rx win: 5760
I (481) wifi_init: tcp mss: 1440
I (491) wifi_init: WiFi IRAM OP enabled
I (491) wifi_init: WiFi RX IRAM OP enabled
I (501) phy_init: phy_version 701,f4f1da3a,Mar  3 2025,15:50:10
E (541) wifi:failed to post WiFi event=43 ret=259
I (541) wifi:mode : softAP (dc:b4:d9:04:7c:05)
I (551) wifi:Total power save buffer number: 16
I (551) wifi:Init max length of beacon: 752/752
I (551) wifi:Init max length of beacon: 752/752
E (551) wifi:failed to post WiFi event=12 ret=259
I (561) wifi_ap: WiFi SoftAP started. SSID: ESP32-SoftAP
I (611) OV7670: OV7670 initialized

assert failed: tcpip_send_msg_wait_sem /IDF/components/lwip/lwip/src/api/tcpip.c:454 (Invalid mbox)


Backtrace: 0x4037c7e5:0x3fca4b90 0x4037c7ad:0x3fca4bb0 0x40382a31:0x3fca4bd0 0x42053953:0x3fca4cf0 0x4205f67e:0x3fca4d20 0x4205f712:0x3fca4d40 0x420537a1:0x3fca4d90 0x42014669:0x3fca4db0 0x42014d34:0x3fca4e10 0x4200a8b8:0x3fca4e40 0x4200a7aa:0x3fca4ef0 0x420067b0:0x3fca4f10 0x42083ef6:0x3fca4f40
--- 0x4037c7e5: panic_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/panic.c:480
--- 0x4037c7ad: esp_system_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/esp_system_chip.c:87
--- 0x40382a31: __assert_func at /Users/maochun/esp32prj/esp-idf/components/newlib/src/assert.c:81
--- 0x42053953: tcpip_send_msg_wait_sem at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/tcpip.c:454
--- 0x4205f67e: netconn_apimsg at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/api_lib.c:134
--- 0x4205f712: netconn_new_with_proto_and_callback at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/api_lib.c:164
--- 0x420537a1: lwip_socket at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/sockets.c:1759
--- 0x42014669: socket at /Users/maochun/esp32prj/esp-idf/components/lwip/include/lwip/sockets.h:70
--- (inlined by) httpd_server_init at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/esp_http_server/src/httpd_main.c:358
--- 0x42014d34: httpd_start at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/esp_http_server/src/httpd_main.c:525
--- 0x4200a8b8: start_webserver at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/protocol/webserver/webserver.c:41
--- 0x4200a7aa: app_main at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/main/main.c:21
--- 0x420067b0: main_task at /Users/maochun/esp32prj/esp-idf/components/freertos/app_startup.c:208
--- 0x42083ef6: vPortTaskWrapper at /Users/maochun/esp32prj/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139




ELF file SHA256: 1c705fd7e

Rebooting...
���ESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0xc (RTC_SW_CPU_RST),boot:0x8 (SPI_FAST_FLASH_BOOT)
Saved PC:0x4037c935
--- 0x4037c935: esp_restart_noos at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/soc/esp32s3/system_internal.c:164
SPIWP:0xee
mode:DIO, clock div:1
load:0x3fce2820,len:0x1588
load:0x403c8700,len:0xd7c
--- 0x403c8700: _stext at ??:?
load:0x403cb700,len:0x2f80
entry 0x403c8908
--- 0x403c8908: call_start_cpu0 at /Users/maochun/esp32prj/esp-idf/components/bootloader/subproject/main/bootloader_start.c:25
I (29) boot: ESP-IDF v6.0-dev-2039-g2044fba6e7 2nd stage bootloader
I (29) boot: compile time Sep 19 2025 15:33:39
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
I (85) esp_image: segment 0: paddr=00010020 vaddr=3c090020 size=1b248h (111176) map
I (112) esp_image: segment 1: paddr=0002b270 vaddr=3fc98e00 size=04bech ( 19436) load
I (117) esp_image: segment 2: paddr=0002fe64 vaddr=40374000 size=001b4h (   436) load
I (117) esp_image: segment 3: paddr=00030020 vaddr=42000020 size=870a0h (553120) map
I (223) esp_image: segment 4: paddr=000b70c8 vaddr=403741b4 size=14b5ch ( 84828) load
I (242) esp_image: segment 5: paddr=000cbc2c vaddr=50000000 size=00020h (    32) load
I (251) boot: Loaded app from partition at offset 0x10000
I (251) boot: Disabling RNG early entropy source...
I (261) cpu_start: Multicore app
I (270) cpu_start: GPIO 44 and 43 are used as console UART I/O pins
I (271) cpu_start: Pro cpu start user code
I (271) cpu_start: cpu freq: 160000000 Hz
I (272) app_init: Application information:
I (276) app_init: Project name:     esp32_wifi_control
I (281) app_init: App version:      c0cfc69-dirty
I (285) app_init: Compile time:     Sep 19 2025 15:33:14
I (290) app_init: ELF file SHA256:  1c705fd7e...
I (295) app_init: ESP-IDF:          v6.0-dev-2039-g2044fba6e7
I (300) efuse_init: Min chip rev:     v0.0
I (304) efuse_init: Max chip rev:     v0.99 
I (308) efuse_init: Chip rev:         v0.2
I (312) heap_init: Initializing. RAM available for dynamic allocation:
I (318) heap_init: At 3FCA1410 len 00048300 (288 KiB): RAM
I (323) heap_init: At 3FCE9710 len 00005724 (21 KiB): RAM
I (328) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (333) heap_init: At 600FE000 len 00001FE8 (7 KiB): RTCRAM
I (340) spi_flash: detected chip: boya
I (342) spi_flash: flash io: dio
W (345) spi_flash: Detected size(16384k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
W (358) i2c: This driver is an old driver, please migrate your application code to adapt `driver/i2c_master.h`
I (367) sleep_gpio: Configure to isolate all GPIO pins in sleep state
I (374) sleep_gpio: Enable automatic switching of GPIO sleep configuration
I (381) main_task: Started on CPU0
I (391) main_task: Calling app_main()
ESP32S3 Boot Success...
I (411) pp: pp rom version: e7ae62f
I (411) net80211: net80211 rom version: e7ae62f
I (421) wifi:wifi driver task: 3fcec904, prio:23, stack:6656, core=0
I (421) wifi:wifi firmware version: df85326
I (421) wifi:wifi certification version: v7.0
I (421) wifi:config NVS flash: enabled
I (421) wifi:config nano formatting: disabled
I (431) wifi:Init data frame dynamic rx buffer num: 32
I (431) wifi:Init static rx mgmt buffer num: 5
I (441) wifi:Init management short buffer num: 32
I (441) wifi:Init dynamic tx buffer num: 32
I (451) wifi:Init static tx FG buffer num: 2
I (451) wifi:Init static rx buffer size: 1600
I (451) wifi:Init static rx buffer num: 10
I (461) wifi:Init dynamic rx buffer num: 32
I (461) wifi_init: rx ba win: 6
I (461) wifi_init: accept mbox: 6
I (471) wifi_init: tcpip mbox: 32
I (471) wifi_init: udp mbox: 6
I (471) wifi_init: tcp mbox: 6
I (481) wifi_init: tcp tx win: 5760
I (481) wifi_init: tcp rx win: 5760
I (481) wifi_init: tcp mss: 1440
I (491) wifi_init: WiFi IRAM OP enabled
I (491) wifi_init: WiFi RX IRAM OP enabled
I (501) phy_init: phy_version 701,f4f1da3a,Mar  3 2025,15:50:10
E (541) wifi:failed to post WiFi event=43 ret=259
I (551) wifi:mode : softAP (dc:b4:d9:04:7c:05)
I (551) wifi:Total power save buffer number: 16
I (551) wifi:Init max length of beacon: 752/752
I (551) wifi:Init max length of beacon: 752/752
E (561) wifi:failed to post WiFi event=12 ret=259
I (561) wifi_ap: WiFi SoftAP started. SSID: ESP32-SoftAP
I (621) OV7670: OV7670 initialized

assert failed: tcpip_send_msg_wait_sem /IDF/components/lwip/lwip/src/api/tcpip.c:454 (Invalid mbox)


Backtrace: 0x4037c7e5:0x3fca4b90 0x4037c7ad:0x3fca4bb0 0x40382a31:0x3fca4bd0 0x42053953:0x3fca4cf0 0x4205f67e:0x3fca4d20 0x4205f712:0x3fca4d40 0x420537a1:0x3fca4d90 0x42014669:0x3fca4db0 0x42014d34:0x3fca4e10 0x4200a8b8:0x3fca4e40 0x4200a7aa:0x3fca4ef0 0x420067b0:0x3fca4f10 0x42083ef6:0x3fca4f40
--- 0x4037c7e5: panic_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/panic.c:480
--- 0x4037c7ad: esp_system_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/esp_system_chip.c:87
--- 0x40382a31: __assert_func at /Users/maochun/esp32prj/esp-idf/components/newlib/src/assert.c:81
--- 0x42053953: tcpip_send_msg_wait_sem at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/tcpip.c:454
--- 0x4205f67e: netconn_apimsg at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/api_lib.c:134
--- 0x4205f712: netconn_new_with_proto_and_callback at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/api_lib.c:164
--- 0x420537a1: lwip_socket at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/sockets.c:1759
--- 0x42014669: socket at /Users/maochun/esp32prj/esp-idf/components/lwip/include/lwip/sockets.h:70
--- (inlined by) httpd_server_init at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/esp_http_server/src/httpd_main.c:358
--- 0x42014d34: httpd_start at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/esp_http_server/src/httpd_main.c:525
--- 0x4200a8b8: start_webserver at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/protocol/webserver/webserver.c:41
--- 0x4200a7aa: app_main at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/main/main.c:21
--- 0x420067b0: main_task at /Users/maochun/esp32prj/esp-idf/components/freertos/app_startup.c:208
--- 0x42083ef6: vPortTaskWrapper at /Users/maochun/esp32prj/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139




ELF file SHA256: 1c705fd7e

Rebooting...
���ESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0xc (RTC_SW_CPU_RST),boot:0x8 (SPI_FAST_FLASH_BOOT)
Saved PC:0x4037c935
--- 0x4037c935: esp_restart_noos at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/soc/esp32s3/system_internal.c:164
SPIWP:0xee
mode:DIO, clock div:1
load:0x3fce2820,len:0x1588
load:0x403c8700,len:0xd7c
--- 0x403c8700: _stext at ??:?
load:0x403cb700,len:0x2f80
entry 0x403c8908
--- 0x403c8908: call_start_cpu0 at /Users/maochun/esp32prj/esp-idf/components/bootloader/subproject/main/bootloader_start.c:25
I (29) boot: ESP-IDF v6.0-dev-2039-g2044fba6e7 2nd stage bootloader
I (29) boot: compile time Sep 19 2025 15:33:39
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
I (85) esp_image: segment 0: paddr=00010020 vaddr=3c090020 size=1b248h (111176) map
I (112) esp_image: segment 1: paddr=0002b270 vaddr=3fc98e00 size=04bech ( 19436) load
I (117) esp_image: segment 2: paddr=0002fe64 vaddr=40374000 size=001b4h (   436) load
I (117) esp_image: segment 3: paddr=00030020 vaddr=42000020 size=870a0h (553120) map
I (223) esp_image: segment 4: paddr=000b70c8 vaddr=403741b4 size=14b5ch ( 84828) load
I (242) esp_image: segment 5: paddr=000cbc2c vaddr=50000000 size=00020h (    32) load
I (251) boot: Loaded app from partition at offset 0x10000
I (251) boot: Disabling RNG early entropy source...
I (261) cpu_start: Multicore app
I (270) cpu_start: GPIO 44 and 43 are used as console UART I/O pins
I (271) cpu_start: Pro cpu start user code
I (271) cpu_start: cpu freq: 160000000 Hz
I (272) app_init: Application information:
I (276) app_init: Project name:     esp32_wifi_control
I (281) app_init: App version:      c0cfc69-dirty
I (285) app_init: Compile time:     Sep 19 2025 15:33:14
I (290) app_init: ELF file SHA256:  1c705fd7e...
I (295) app_init: ESP-IDF:          v6.0-dev-2039-g2044fba6e7
I (300) efuse_init: Min chip rev:     v0.0
I (304) efuse_init: Max chip rev:     v0.99 
I (308) efuse_init: Chip rev:         v0.2
I (312) heap_init: Initializing. RAM available for dynamic allocation:
I (318) heap_init: At 3FCA1410 len 00048300 (288 KiB): RAM
I (323) heap_init: At 3FCE9710 len 00005724 (21 KiB): RAM
I (328) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (333) heap_init: At 600FE000 len 00001FE8 (7 KiB): RTCRAM
I (340) spi_flash: detected chip: boya
I (342) spi_flash: flash io: dio
W (345) spi_flash: Detected size(16384k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
W (358) i2c: This driver is an old driver, please migrate your application code to adapt `driver/i2c_master.h`
I (367) sleep_gpio: Configure to isolate all GPIO pins in sleep state
I (374) sleep_gpio: Enable automatic switching of GPIO sleep configuration
I (381) main_task: Started on CPU0
I (391) main_task: Calling app_main()
ESP32S3 Boot Success...
I (411) pp: pp rom version: e7ae62f
I (411) net80211: net80211 rom version: e7ae62f
I (421) wifi:wifi driver task: 3fcec904, prio:23, stack:6656, core=0
I (421) wifi:wifi firmware version: df85326
I (421) wifi:wifi certification version: v7.0
I (421) wifi:config NVS flash: enabled
I (421) wifi:config nano formatting: disabled
I (431) wifi:Init data frame dynamic rx buffer num: 32
I (431) wifi:Init static rx mgmt buffer num: 5
I (441) wifi:Init management short buffer num: 32
I (441) wifi:Init dynamic tx buffer num: 32
I (451) wifi:Init static tx FG buffer num: 2
I (451) wifi:Init static rx buffer size: 1600
I (451) wifi:Init static rx buffer num: 10
I (461) wifi:Init dynamic rx buffer num: 32
I (461) wifi_init: rx ba win: 6
I (461) wifi_init: accept mbox: 6
I (471) wifi_init: tcpip mbox: 32
I (471) wifi_init: udp mbox: 6
I (471) wifi_init: tcp mbox: 6
I (481) wifi_init: tcp tx win: 5760
I (481) wifi_init: tcp rx win: 5760
I (481) wifi_init: tcp mss: 1440
I (491) wifi_init: WiFi IRAM OP enabled
I (491) wifi_init: WiFi RX IRAM OP enabled
I (501) phy_init: phy_version 701,f4f1da3a,Mar  3 2025,15:50:10
E (541) wifi:failed to post WiFi event=43 ret=259
I (541) wifi:mode : softAP (dc:b4:d9:04:7c:05)
I (551) wifi:Total power save buffer number: 16
I (551) wifi:Init max length of beacon: 752/752
I (551) wifi:Init max length of beacon: 752/752
E (551) wifi:failed to post WiFi event=12 ret=259
I (561) wifi_ap: WiFi SoftAP started. SSID: ESP32-SoftAP
I (611) OV7670: OV7670 initialized

assert failed: tcpip_send_msg_wait_sem /IDF/components/lwip/lwip/src/api/tcpip.c:454 (Invalid mbox)


Backtrace: 0x4037c7e5:0x3fca4b90 0x4037c7ad:0x3fca4bb0 0x40382a31:0x3fca4bd0 0x42053953:0x3fca4cf0 0x4205f67e:0x3fca4d20 0x4205f712:0x3fca4d40 0x420537a1:0x3fca4d90 0x42014669:0x3fca4db0 0x42014d34:0x3fca4e10 0x4200a8b8:0x3fca4e40 0x4200a7aa:0x3fca4ef0 0x420067b0:0x3fca4f10 0x42083ef6:0x3fca4f40
--- 0x4037c7e5: panic_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/panic.c:480
--- 0x4037c7ad: esp_system_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/esp_system_chip.c:87
--- 0x40382a31: __assert_func at /Users/maochun/esp32prj/esp-idf/components/newlib/src/assert.c:81
--- 0x42053953: tcpip_send_msg_wait_sem at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/tcpip.c:454
--- 0x4205f67e: netconn_apimsg at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/api_lib.c:134
--- 0x4205f712: netconn_new_with_proto_and_callback at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/api_lib.c:164
--- 0x420537a1: lwip_socket at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/sockets.c:1759
--- 0x42014669: socket at /Users/maochun/esp32prj/esp-idf/components/lwip/include/lwip/sockets.h:70
--- (inlined by) httpd_server_init at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/esp_http_server/src/httpd_main.c:358
--- 0x42014d34: httpd_start at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/esp_http_server/src/httpd_main.c:525
--- 0x4200a8b8: start_webserver at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/protocol/webserver/webserver.c:41
--- 0x4200a7aa: app_main at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/main/main.c:21
--- 0x420067b0: main_task at /Users/maochun/esp32prj/esp-idf/components/freertos/app_startup.c:208
--- 0x42083ef6: vPortTaskWrapper at /Users/maochun/esp32prj/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139




ELF file SHA256: 1c705fd7e

Rebooting...
���ESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0xc (RTC_SW_CPU_RST),boot:0x8 (SPI_FAST_FLASH_BOOT)
Saved PC:0x4037c935
--- 0x4037c935: esp_restart_noos at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/soc/esp32s3/system_internal.c:164
SPIWP:0xee
mode:DIO, clock div:1
load:0x3fce2820,len:0x1588
load:0x403c8700,len:0xd7c
--- 0x403c8700: _stext at ??:?
load:0x403cb700,len:0x2f80
entry 0x403c8908
--- 0x403c8908: call_start_cpu0 at /Users/maochun/esp32prj/esp-idf/components/bootloader/subproject/main/bootloader_start.c:25
I (29) boot: ESP-IDF v6.0-dev-2039-g2044fba6e7 2nd stage bootloader
I (29) boot: compile time Sep 19 2025 15:33:39
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
I (85) esp_image: segment 0: paddr=00010020 vaddr=3c090020 size=1b248h (111176) map
I (112) esp_image: segment 1: paddr=0002b270 vaddr=3fc98e00 size=04bech ( 19436) load
I (117) esp_image: segment 2: paddr=0002fe64 vaddr=40374000 size=001b4h (   436) load
I (117) esp_image: segment 3: paddr=00030020 vaddr=42000020 size=870a0h (553120) map
I (223) esp_image: segment 4: paddr=000b70c8 vaddr=403741b4 size=14b5ch ( 84828) load
I (242) esp_image: segment 5: paddr=000cbc2c vaddr=50000000 size=00020h (    32) load
I (251) boot: Loaded app from partition at offset 0x10000
I (251) boot: Disabling RNG early entropy source...
I (261) cpu_start: Multicore app
I (270) cpu_start: GPIO 44 and 43 are used as console UART I/O pins
I (271) cpu_start: Pro cpu start user code
I (271) cpu_start: cpu freq: 160000000 Hz
I (272) app_init: Application information:
I (276) app_init: Project name:     esp32_wifi_control
I (281) app_init: App version:      c0cfc69-dirty
I (285) app_init: Compile time:     Sep 19 2025 15:33:14
I (290) app_init: ELF file SHA256:  1c705fd7e...
I (295) app_init: ESP-IDF:          v6.0-dev-2039-g2044fba6e7
I (300) efuse_init: Min chip rev:     v0.0
I (304) efuse_init: Max chip rev:     v0.99 
I (308) efuse_init: Chip rev:         v0.2
I (312) heap_init: Initializing. RAM available for dynamic allocation:
I (318) heap_init: At 3FCA1410 len 00048300 (288 KiB): RAM
I (323) heap_init: At 3FCE9710 len 00005724 (21 KiB): RAM
I (328) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (333) heap_init: At 600FE000 len 00001FE8 (7 KiB): RTCRAM
I (340) spi_flash: detected chip: boya
I (342) spi_flash: flash io: dio
W (345) spi_flash: Detected size(16384k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
W (358) i2c: This driver is an old driver, please migrate your application code to adapt `driver/i2c_master.h`
I (367) sleep_gpio: Configure to isolate all GPIO pins in sleep state
I (374) sleep_gpio: Enable automatic switching of GPIO sleep configuration
I (381) main_task: Started on CPU0
I (391) main_task: Calling app_main()
ESP32S3 Boot Success...
I (411) pp: pp rom version: e7ae62f
I (411) net80211: net80211 rom version: e7ae62f
I (421) wifi:wifi driver task: 3fcec904, prio:23, stack:6656, core=0
I (421) wifi:wifi firmware version: df85326
I (421) wifi:wifi certification version: v7.0
I (421) wifi:config NVS flash: enabled
I (421) wifi:config nano formatting: disabled
I (431) wifi:Init data frame dynamic rx buffer num: 32
I (431) wifi:Init static rx mgmt buffer num: 5
I (441) wifi:Init management short buffer num: 32
I (441) wifi:Init dynamic tx buffer num: 32
I (451) wifi:Init static tx FG buffer num: 2
I (451) wifi:Init static rx buffer size: 1600
I (451) wifi:Init static rx buffer num: 10
I (461) wifi:Init dynamic rx buffer num: 32
I (461) wifi_init: rx ba win: 6
I (461) wifi_init: accept mbox: 6
I (471) wifi_init: tcpip mbox: 32
I (471) wifi_init: udp mbox: 6
I (471) wifi_init: tcp mbox: 6
I (481) wifi_init: tcp tx win: 5760
I (481) wifi_init: tcp rx win: 5760
I (481) wifi_init: tcp mss: 1440
I (491) wifi_init: WiFi IRAM OP enabled
I (491) wifi_init: WiFi RX IRAM OP enabled
I (501) phy_init: phy_version 701,f4f1da3a,Mar  3 2025,15:50:10
E (541) wifi:failed to post WiFi event=43 ret=259
I (541) wifi:mode : softAP (dc:b4:d9:04:7c:05)
I (541) wifi:Total power save buffer number: 16
I (551) wifi:Init max length of beacon: 752/752
I (551) wifi:Init max length of beacon: 752/752
E (551) wifi:failed to post WiFi event=12 ret=259
I (551) wifi_ap: WiFi SoftAP started. SSID: ESP32-SoftAP
I (611) OV7670: OV7670 initialized

assert failed: tcpip_send_msg_wait_sem /IDF/components/lwip/lwip/src/api/tcpip.c:454 (Invalid mbox)


Backtrace: 0x4037c7e5:0x3fca4b90 0x4037c7ad:0x3fca4bb0 0x40382a31:0x3fca4bd0 0x42053953:0x3fca4cf0 0x4205f67e:0x3fca4d20 0x4205f712:0x3fca4d40 0x420537a1:0x3fca4d90 0x42014669:0x3fca4db0 0x42014d34:0x3fca4e10 0x4200a8b8:0x3fca4e40 0x4200a7aa:0x3fca4ef0 0x420067b0:0x3fca4f10 0x42083ef6:0x3fca4f40
--- Error: read failed: [Errno 6] Device not configured
--- Waiting for the device to reconnect--- 0x4037c7e5: panic_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/panic.c:480
--- 0x4037c7ad: esp_system_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/esp_system_chip.c:87
--- 0x40382a31: __assert_func at /Users/maochun/esp32prj/esp-idf/components/newlib/src/assert.c:81
--- 0x42053953: tcpip_send_msg_wait_sem at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/tcpip.c:454
--- 0x4205f67e: netconn_apimsg at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/api_lib.c:134
--- 0x4205f712: netconn_new_with_proto_and_callback at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/api_lib.c:164
--- 0x420537a1: lwip_socket at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/sockets.c:1759
--- 0x42014669: socket at /Users/maochun/esp32prj/esp-idf/components/lwip/include/lwip/sockets.h:70
--- (inlined by) httpd_server_init at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/esp_http_server/src/httpd_main.c:358
--- 0x42014d34: httpd_start at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/esp_http_server/src/httpd_main.c:525
--- 0x4200a8b8: start_webserver at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/protocol/webserver/webserver.c:41
--- 0x4200a7aa: app_main at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/main/main.c:21
--- 0x420067b0: main_task at /Users/maochun/esp32prj/esp-idf/components/freertos/app_startup.c:208
--- 0x42083ef6: vPortTaskWrapper at /Users/maochun/esp32prj/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139




ELF file SHA256: 1c705fd7e