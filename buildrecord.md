
Rebooting...
ESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0xc (RTC_SW_CPU_RST),boot:0x8 (SPI_FAST_FLASH_BOOT)
Saved PC:0x4037c909
--- 0x4037c909: esp_restart_noos at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/soc/esp32s3/system_internal.c:164
SPIWP:0xee
mode:DIO, clock div:1
load:0x3fce2820,len:0x1588
load:0x403c8700,len:0xd7c
load:0x403cb700,len:0x2f80
entry 0x403c8908
I (29) boot: ESP-IDF v6.0-dev-2039-g2044fba6e7 2nd stage bootloader
I (29) boot: compile time Sep 19 2025 12:41:51
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
I (69) boot:  1 phy_init         RF data          01 01 0000f000 00001000.
I (75) boot:  2 factory          factory app      00 00 00010000 00100000
I (82) boot: End of partition table
I (85) esp_image: segment 0: paddr=00010020 vaddr=3c090020 size=1aed8h (110296) map
I (112) esp_image: segment 1: paddr=0002af00 vaddr=3fc98600 size=04b14h ( 19220) load
I (116) esp_image: segment 2: paddr=0002fa1c vaddr=40374000 size=005fch (  1532) load
I (117) esp_image: segment 3: paddr=00030020 vaddr=42000020 size=854fch (546044) map
I (222) esp_image: segment 4: paddr=000b5524 vaddr=403745fc size=13fc8h ( 81864) load
I (240) esp_image: segment 5: paddr=000c94f4 vaddr=50000000 size=00020h (    32) load
I (249) boot: Loaded app from partition at offset 0x10000
I (249) boot: Disabling RNG early entropy source...
I (259) cpu_start: Multicore app
I (267) cpu_start: GPIO 44 and 43 are used as console UART I/O pins
I (268) cpu_start: Pro cpu start user code
I (268) cpu_start: cpu freq: 160000000 Hz
I (270) app_init: Application information:
I (274) app_init: Project name:     esp32_wifi_control
I (278) app_init: App version:      eebf498-dirty
I (283) app_init: Compile time:     Sep 19 2025 12:53:27
I (288) app_init: ELF file SHA256:  817d571cd...
I (292) app_init: ESP-IDF:          v6.0-dev-2039-g2044fba6e7
I (298) efuse_init: Min chip rev:     v0.0
I (302) efuse_init: Max chip rev:     v0.99 
I (306) efuse_init: Chip rev:         v0.2
I (309) heap_init: Initializing. RAM available for dynamic allocation:
I (316) heap_init: At 3FCA0B30 len 00048BE0 (290 KiB): RAM
I (321) heap_init: At 3FCE9710 len 00005724 (21 KiB): RAM
I (326) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (331) heap_init: At 600FE000 len 00001FE8 (7 KiB): RTCRAM
I (338) spi_flash: detected chip: boya
I (340) spi_flash: flash io: dio
W (343) spi_flash: Detected size(16384k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
W (355) i2c: This driver is an old driver, please migrate your application code to adapt `driver/i2c_master.h`
I (365) sleep_gpio: Configure to isolate all GPIO pins in sleep state
I (371) sleep_gpio: Enable automatic switching of GPIO sleep configuration
I (378) main_task: Started on CPU0
I (388) main_task: Calling app_main()
I (388) pp: pp rom version: e7ae62f
I (388) net80211: net80211 rom version: e7ae62f
W (388) wifi:wifi osi_nvs_open fail ret=4353

W (398) wifi_init: Failed to unregister Rx callbacks
E (398) wifi_init: Failed to deinit Wi-Fi driver (0x3001)
E (408) wifi_init: Failed to deinit Wi-Fi (0x3001)
ESP_ERROR_CHECK failed: esp_err_t 0x1101 (ESP_ERR_NVS_NOT_INITIALIZED) at 0x4200a9b2
--- 0x4200a9b2: wifi_init_softap at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/protocol/wifi_ap/wifi_ap.c:8
file: "./protocol/wifi_ap/wifi_ap.c" line 8
func: wifi_init_softap
expression: esp_wifi_init(&cfg)

abort() was called at PC 0x4037c777 on core 0
--- 0x4037c777: _esp_error_check_failed at /Users/maochun/esp32prj/esp-idf/components/esp_system/esp_err.c:49


Backtrace: 0x4037c7b9:0x3fca43c0 0x4037c781:0x3fca43e0 0x403828ed:0x3fca4400 0x4037c777:0x3fca4470 0x4200a9b2:0x3fca44a0 0x4200a707:0x3fca4610 0x42006768:0x3fca4630 0x42082352:0x3fca4660
.--- 0x4037c7b9: panic_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/panic.c:480
--- 0x4037c781: esp_system_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/esp_system_chip.c:87
--- 0x403828ed: abort at /Users/maochun/esp32prj/esp-idf/components/newlib/src/abort.c:38
--- 0x4037c777: _esp_error_check_failed at /Users/maochun/esp32prj/esp-idf/components/esp_system/esp_err.c:49
--- 0x4200a9b2: wifi_init_softap at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/protocol/wifi_ap/wifi_ap.c:8
--- 0x4200a707: app_main at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/main/main.c:8
--- 0x42006768: main_task at /Users/maochun/esp32prj/esp-idf/components/freertos/app_startup.c:208
--- 0x42082352: vPortTaskWrapper at /Users/maochun/esp32prj/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139




ELF file SHA256: 817d571cd

Rebooting...
ESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0xc (RTC_SW_CPU_RST),boot:0x8 (SPI_FAST_FLASH_BOOT)
Saved PC:0x4037c909
--- 0x4037c909: esp_restart_noos at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/soc/esp32s3/system_internal.c:164
SPIWP:0xee
mode:DIO, clock div:1
load:0x3fce2820,len:0x1588
load:0x403c8700,len:0xd7c
load:0x403cb700,len:0x2f80
entry 0x403c8908
I (29) boot: ESP-IDF v6.0-dev-2039-g2044fba6e7 2nd stage bootloader
I (29) boot: compile time Sep 19 2025 12:41:51
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
I (85) esp_image: segment 0: paddr=00010020 vaddr=3c090020 size=1aed8h (110296) map
I (112) esp_image: segment 1: paddr=0002af00 vaddr=3fc98600 size=04b14h ( 19220) load
I (116) esp_image: segment 2: paddr=0002fa1c vaddr=40374000 size=005fch (  1532) load
.I (117) esp_image: segment 3: paddr=00030020 vaddr=42000020 size=854fch (546044) map
I (222) esp_image: segment 4: paddr=000b5524 vaddr=403745fc size=13fc8h ( 81864) load
I (240) esp_image: segment 5: paddr=000c94f4 vaddr=50000000 size=00020h (    32) load
I (249) boot: Loaded app from partition at offset 0x10000
I (249) boot: Disabling RNG early entropy source...
I (259) cpu_start: Multicore app
I (267) cpu_start: GPIO 44 and 43 are used as console UART I/O pins
I (268) cpu_start: Pro cpu start user code
I (268) cpu_start: cpu freq: 160000000 Hz
I (270) app_init: Application information:
I (274) app_init: Project name:     esp32_wifi_control
I (278) app_init: App version:      eebf498-dirty
I (283) app_init: Compile time:     Sep 19 2025 12:53:27
I (288) app_init: ELF file SHA256:  817d571cd...
I (292) app_init: ESP-IDF:          v6.0-dev-2039-g2044fba6e7
I (298) efuse_init: Min chip rev:     v0.0
I (302) efuse_init: Max chip rev:     v0.99 
I (306) efuse_init: Chip rev:         v0.2
I (309) heap_init: Initializing. RAM available for dynamic allocation:
I (316) heap_init: At 3FCA0B30 len 00048BE0 (290 KiB): RAM
I (321) heap_init: At 3FCE9710 len 00005724 (21 KiB): RAM
I (326) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (331) heap_init: At 600FE000 len 00001FE8 (7 KiB): RTCRAM
I (338) spi_flash: detected chip: boya
I (340) spi_flash: flash io: dio
W (343) spi_flash: Detected size(16384k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
W (355) i2c: This driver is an old driver, please migrate your application code to adapt `driver/i2c_master.h`
I (365) sleep_gpio: Configure to isolate all GPIO pins in sleep state
I (371) sleep_gpio: Enable automatic switching of GPIO sleep configuration
I (378) main_task: Started on CPU0
I (388) main_task: Calling app_main()
I (388) pp: pp rom version: e7ae62f
I (388) net80211: net80211 rom version: e7ae62f
W (388) wifi:wifi osi_nvs_open fail ret=4353

W (398) wifi_init: Failed to unregister Rx callbacks
E (398) wifi_init: Failed to deinit Wi-Fi driver (0x3001)
E (408) wifi_init: Failed to deinit Wi-Fi (0x3001)
ESP_ERROR_CHECK failed: esp_err_t 0x1101 (ESP_ERR_NVS_NOT_INITIALIZED) at 0x4200a9b2
--- 0x4200a9b2: wifi_init_softap at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/protocol/wifi_ap/wifi_ap.c:8
file: "./protocol/wifi_ap/wifi_ap.c" line 8
func: wifi_init_softap
expression: esp_wifi_init(&cfg)

abort() was called at PC 0x4037c777 on core 0
.--- 0x4037c777: _esp_error_check_failed at /Users/maochun/esp32prj/esp-idf/components/esp_system/esp_err.c:49


Backtrace: 0x4037c7b9:0x3fca43c0 0x4037c781:0x3fca43e0 0x403828ed:0x3fca4400 0x4037c777:0x3fca4470 0x4200a9b2:0x3fca44a0 0x4200a707:0x3fca4610 0x42006768:0x3fca4630 0x42082352:0x3fca4660
--- 0x4037c7b9: panic_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/panic.c:480
--- 0x4037c781: esp_system_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/esp_system_chip.c:87
--- 0x403828ed: abort at /Users/maochun/esp32prj/esp-idf/components/newlib/src/abort.c:38
--- 0x4037c777: _esp_error_check_failed at /Users/maochun/esp32prj/esp-idf/components/esp_system/esp_err.c:49
--- 0x4200a9b2: wifi_init_softap at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/protocol/wifi_ap/wifi_ap.c:8
--- 0x4200a707: app_main at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/main/main.c:8
--- 0x42006768: main_task at /Users/maochun/esp32prj/esp-idf/components/freertos/app_startup.c:208
--- 0x42082352: vPortTaskWrapper at /Users/maochun/esp32prj/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139




ELF file SHA256: 817d571cd
.
Rebooting...
ESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0xc (RTC_SW_CPU_RST),boot:0x8 (SPI_FAST_FLASH_BOOT)
Saved PC:0x4037c909
--- 0x4037c909: esp_restart_noos at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/soc/esp32s3/system_internal.c:164
SPIWP:0xee
mode:DIO, clock div:1
load:0x3fce2820,len:0x1588
load:0x403c8700,len:0xd7c
load:0x403cb700,len:0x2f80
entry 0x403c8908
I (29) boot: ESP-IDF v6.0-dev-2039-g2044fba6e7 2nd stage bootloader
I (29) boot: compile time Sep 19 2025 12:41:51
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
I (85) esp_image: segment 0: paddr=00010020 vaddr=3c090020 size=1aed8h (110296) map
I (112) esp_image: segment 1: paddr=0002af00 vaddr=3fc98600 size=04b14h ( 19220) load
I (116) esp_image: segment 2: paddr=0002fa1c vaddr=40374000 size=005fch (  1532) load
I (117) esp_image: segment 3: paddr=00030020 vaddr=42000020 size=854fch (546044) map
I (222) esp_image: segment 4: paddr=000b5524 vaddr=403745fc size=13fc8h ( 81864) load
I (240) esp_image: segment 5: paddr=000c94f4 vaddr=50000000 size=00020h (    32) load
I (249) boot: Loaded app from partition at offset 0x10000
I (249) boot: Disabling RNG early entropy source...
I (259) cpu_start: Multicore app
I (267) cpu_start: GPIO 44 and 43 are used as console UART I/O pins
I (268) cpu_start: Pro cpu start user code
I (268) cpu_start: cpu freq: 160000000 Hz
I (270) app_init: Application information:
I (274) app_init: Project name:     esp32_wifi_control
I (278) app_init: App version:      eebf498-dirty
I (283) app_init: Compile time:     Sep 19 2025 12:53:27
I (288) app_init: ELF file SHA256:  817d571cd...
I (292) app_init: ESP-IDF:          v6.0-dev-2039-g2044fba6e7
I (298) efuse_init: Min chip rev:     v0.0
I (302) efuse_init: Max chip rev:     v0.99 
I (306) efuse_init: Chip rev:         v0.2
I (309) heap_init: Initializing. RAM available for dynamic allocation:
I (316) heap_init: At 3FCA0B30 len 00048BE0 (290 KiB): RAM
I (321) heap_init: At 3FCE9710 len 00005724 (21 KiB): RAM
I (326) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (331) heap_init: At 600FE000 len 00001FE8 (7 KiB): RTCRAM
I (338) spi_flash: detected chip: boya
I (340) spi_flash: flash io: dio
W (343) spi_flash: Detected size(16384k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
W (355) i2c: This driver is an old driver, please migrate your application code to adapt `driver/i2c_master.h`
I (365) sleep_gpio: Configure to isolate all GPIO pins in sleep state
I (371) sleep_gpio: Enable automatic switching of GPIO sleep configuration
I (378) main_task: Started on CPU0
I (388) main_task: Calling app_main()
I (388) pp: pp rom version: e7ae62f
I (388) net80211: net80211 rom version: e7ae62f
W (388) wifi:wifi osi_nvs_open fail ret=4353

W (398) wifi_init: Failed to unregister Rx callbacks
E (398) wifi_init: Failed to deinit Wi-Fi driver (0x3001)
E (408) wifi_init: Failed to deinit Wi-Fi (0x3001)
ESP_ERROR_CHECK failed: esp_err_t 0x1101 (ESP_ERR_NVS_NOT_INITIALIZED) at 0x4200a9b2
.--- 0x4200a9b2: wifi_init_softap at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/protocol/wifi_ap/wifi_ap.c:8
file: "./protocol/wifi_ap/wifi_ap.c" line 8
func: wifi_init_softap
expression: esp_wifi_init(&cfg)

abort() was called at PC 0x4037c777 on core 0
--- 0x4037c777: _esp_error_check_failed at /Users/maochun/esp32prj/esp-idf/components/esp_system/esp_err.c:49


Backtrace: 0x4037c7b9:0x3fca43c0 0x4037c781:0x3fca43e0 0x403828ed:0x3fca4400 0x4037c777:0x3fca4470 0x4200a9b2:0x3fca44a0 0x4200a707:0x3fca4610 0x42006768:0x3fca4630 0x42082352:0x3fca4660
--- 0x4037c7b9: panic_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/panic.c:480
--- 0x4037c781: esp_system_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/esp_system_chip.c:87
--- 0x403828ed: abort at /Users/maochun/esp32prj/esp-idf/components/newlib/src/abort.c:38
--- 0x4037c777: _esp_error_check_failed at /Users/maochun/esp32prj/esp-idf/components/esp_system/esp_err.c:49
--- 0x4200a9b2: wifi_init_softap at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/protocol/wifi_ap/wifi_ap.c:8
--- 0x4200a707: app_main at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/main/main.c:8
--- 0x42006768: main_task at /Users/maochun/esp32prj/esp-idf/components/freertos/app_startup.c:208
--- 0x42082352: vPortTaskWrapper at /Users/maochun/esp32prj/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139




ELF file SHA256: 817d571cd
.
Rebooting...
ESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0xc (RTC_SW_CPU_RST),boot:0x8 (SPI_FAST_FLASH_BOOT)
Saved PC:0x4037c909
--- 0x4037c909: esp_restart_noos at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/soc/esp32s3/system_internal.c:164
SPIWP:0xee
mode:DIO, clock div:1
load:0x3fce2820,len:0x1588
load:0x403c8700,len:0xd7c
load:0x403cb700,len:0x2f80
entry 0x403c8908
I (29) boot: ESP-IDF v6.0-dev-2039-g2044fba6e7 2nd stage bootloader
I (29) boot: compile time Sep 19 2025 12:41:51
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
I (85) esp_image: segment 0: paddr=00010020 vaddr=3c090020 size=1aed8h (110296) map
I (112) esp_image: segment 1: paddr=0002af00 vaddr=3fc98600 size=04b14h ( 19220) load
I (116) esp_image: segment 2: paddr=0002fa1c vaddr=40374000 size=005fch (  1532) load
I (117) esp_image: segment 3: paddr=00030020 vaddr=42000020 size=854fch (546044) map
I (222) esp_image: segment 4: paddr=000b5524 vaddr=403745fc size=13fc8h ( 81864) load
I (240) esp_image: segment 5: paddr=000c94f4 vaddr=50000000 size=00020h (    32) load
I (249) boot: Loaded app from partition at offset 0x10000
I (249) boot: Disabling RNG early entropy source...
I (259) cpu_start: Multicore app
I (267) cpu_start: GPIO 44 and 43 are used as console UART I/O pins
I (268) cpu_start: Pro cpu start user code
I (268) cpu_start: cpu freq: 160000000 Hz
I (270) app_init: Application information:
I (274) app_init: Project name:     esp32_wifi_control
I (278) app_init: App version:      eebf498-dirty
I (283) app_init: Compile time:     Sep 19 2025 12:53:27
I (288) app_init: ELF file SHA256:  817d571cd...
.I (292) app_init: ESP-IDF:          v6.0-dev-2039-g2044fba6e7
I (298) efuse_init: Min chip rev:     v0.0
I (302) efuse_init: Max chip rev:     v0.99 
I (306) efuse_init: Chip rev:         v0.2
I (309) heap_init: Initializing. RAM available for dynamic allocation:
I (316) heap_init: At 3FCA0B30 len 00048BE0 (290 KiB): RAM
I (321) heap_init: At 3FCE9710 len 00005724 (21 KiB): RAM
I (326) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (331) heap_init: At 600FE000 len 00001FE8 (7 KiB): RTCRAM
I (338) spi_flash: detected chip: boya
I (340) spi_flash: flash io: dio
W (343) spi_flash: Detected size(16384k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
W (355) i2c: This driver is an old driver, please migrate your application code to adapt `driver/i2c_master.h`
I (365) sleep_gpio: Configure to isolate all GPIO pins in sleep state
I (371) sleep_gpio: Enable automatic switching of GPIO sleep configuration
I (378) main_task: Started on CPU0
I (388) main_task: Calling app_main()
I (388) pp: pp rom version: e7ae62f
I (388) net80211: net80211 rom version: e7ae62f
W (388) wifi:wifi osi_nvs_open fail ret=4353

W (398) wifi_init: Failed to unregister Rx callbacks
E (398) wifi_init: Failed to deinit Wi-Fi driver (0x3001)
E (408) wifi_init: Failed to deinit Wi-Fi (0x3001)
ESP_ERROR_CHECK failed: esp_err_t 0x1101 (ESP_ERR_NVS_NOT_INITIALIZED) at 0x4200a9b2
--- 0x4200a9b2: wifi_init_softap at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/protocol/wifi_ap/wifi_ap.c:8
file: "./protocol/wifi_ap/wifi_ap.c" line 8
func: wifi_init_softap
expression: esp_wifi_init(&cfg)

abort() was called at PC 0x4037c777 on core 0
--- 0x4037c777: _esp_error_check_failed at /Users/maochun/esp32prj/esp-idf/components/esp_system/esp_err.c:49


Backtrace: 0x4037c7b9:0x3fca43c0 0x4037c781:0x3fca43e0 0x403828ed:0x3fca4400 0x4037c777:0x3fca4470 0x4200a9b2:0x3fca44a0 0x4200a707:0x3fca4610 0x42006768:0x3fca4630 0x42082352:0x3fca4660
.--- 0x4037c7b9: panic_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/panic.c:480
--- 0x4037c781: esp_system_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/esp_system_chip.c:87
--- 0x403828ed: abort at /Users/maochun/esp32prj/esp-idf/components/newlib/src/abort.c:38
--- 0x4037c777: _esp_error_check_failed at /Users/maochun/esp32prj/esp-idf/components/esp_system/esp_err.c:49
--- 0x4200a9b2: wifi_init_softap at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/protocol/wifi_ap/wifi_ap.c:8
--- 0x4200a707: app_main at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/main/main.c:8
--- 0x42006768: main_task at /Users/maochun/esp32prj/esp-idf/components/freertos/app_startup.c:208
--- 0x42082352: vPortTaskWrapper at /Users/maochun/esp32prj/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139




ELF file SHA256: 817d571cd
