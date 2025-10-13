
ESP32S3 Boot Success...
I (913) pp: pp rom version: e7ae62f
I (913) net80211: net80211 rom version: e7ae62f
I (923) wifi:wifi driver task: 3fca8220, prio:23, stack:6656, core=0
I (923) wifi:wifi firmware version: df85326
I (923) wifi:wifi certification version: v7.0
I (923) wifi:config NVS flash: enabled
I (923) wifi:config nano formatting: disabled
I (933) wifi:Init data frame dynamic rx buffer num: 32
I (933) wifi:Init static rx mgmt buffer num: 5
I (943) wifi:Init management short buffer num: 32
I (943) wifi:Init dynamic tx buffer num: 32
I (953) wifi:Init static tx FG buffer num: 2
I (953) wifi:Init static rx buffer size: 1600
I (953) wifi:Init static rx buffer num: 10
I (963) wifi:Init dynamic rx buffer num: 32
I (963) wifi_init: rx ba win: 6
I (963) wifi_init: accept mbox: 6
I (973) wifi_init: tcpip mbox: 32
I (973) wifi_init: udp mbox: 6
I (973) wifi_init: tcp mbox: 6
I (983) wifi_init: tcp tx win: 5760
I (983) wifi_init: tcp rx win: 5760
I (983) wifi_init: tcp mss: 1440
I (983) wifi_init: WiFi IRAM OP enabled
I (993) wifi_init: WiFi RX IRAM OP enabled
I (1003) phy_init: phy_version 701,f4f1da3a,Mar  3 2025,15:50:10
I (1043) wifi:mode : softAP (dc:b4:d9:04:7c:05)
I (1053) wifi:Total power save buffer number: 16
I (1053) wifi:Init max length of beacon: 752/752
I (1053) wifi:Init max length of beacon: 752/752
I (1053) wifi_ap: WiFi SoftAP started. SSID: ESP32-TEST, Password: niwenwoa
I (1053) esp_netif_lwip: DHCP server started on interface WIFI_AP_DEF with IP: 192.168.4.1
I (1063) wifi_ap: DHCP server is running.
I (1073) PSRAM: PSRAM size: 8388608 bytes
I (1073) PSRAM: Free heap: 8659788 bytes
I (1083) PSRAM: PSRAM is initialized and ready.
I (1083) PSRAM: Successfully allocated 1KB from PSRAM.
ESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0x8 (TG1WDT_SYS_RST),boot:0x8 (SPI_FAST_FLASH_BOOT)
Saved PC:0x4037577c
--- 0x4037577c: panic_enable_cache at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/panic_handler.c:277
SPIWP:0xee
mode:DIO, clock div:1
load:0x3fce2820,len:0x16fc
load:0x403c8700,len:0xf14
load:0x403cb700,len:0x3214
entry 0x403c8930
I (29) boot: ESP-IDF v6.0-dev-2039-g2044fba6e7 2nd stage bootloader
I (29) boot: compile time Oct 13 2025 19:21:32
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
I (67) boot: Partition Table:
I (69) boot: ## Label            Usage          Type ST Offset   Length
I (76) boot:  0 nvs              WiFi data        01 02 00009000 00005000
I (82) boot:  1 otadata          OTA data         01 00 0000e000 00002000
I (89) boot:  2 app0             OTA app          00 10 00010000 00140000
I (95) boot:  3 app1             OTA app          00 11 00150000 00140000
I (102) boot:  4 spiffs           Unknown data     01 82 00290000 00170000
I (108) boot: End of partition table
I (112) esp_image: segment 0: paddr=00010020 vaddr=3c0a0020 size=1f60ch (128524) map
I (139) esp_image: segment 1: paddr=0002f634 vaddr=3fc9a600 size=009e4h (  2532) load
I (140) esp_image: segment 2: paddr=00030020 vaddr=42000020 size=9cda8h (642472) map
I (240) esp_image: segment 3: paddr=000ccdd0 vaddr=3fc9afe4 size=04764h ( 18276) load
I (243) esp_image: segment 4: paddr=000d153c vaddr=40374000 size=16514h ( 91412) load
I (261) esp_image: segment 5: paddr=000e7a58 vaddr=50000000 size=00020h (    32) load
I (271) boot: Loaded app from partition at offset 0x10000
I (271) boot: Disabling RNG early entropy source...
I (281) octal_psram: vendor id    : 0x0d (AP)
I (282) octal_psram: dev id       : 0x02 (generation 3)
I (282) octal_psram: density      : 0x03 (64 Mbit)
I (284) octal_psram: good-die     : 0x01 (Pass)
I (288) octal_psram: Latency      : 0x01 (Fixed)
I (292) octal_psram: VCC          : 0x01 (3V)
I (296) octal_psram: SRF          : 0x01 (Fast Refresh)
I (301) octal_psram: BurstType    : 0x01 (Hybrid Wrap)
I (306) octal_psram: BurstLen     : 0x01 (32 Byte)
I (311) octal_psram: Readlatency  : 0x02 (10 cycles@Fixed)
I (316) octal_psram: DriveStrength: 0x00 (1/1)
I (321) MSPI Timing: PSRAM timing tuning index: 4
I (325) esp_psram: Found 8MB PSRAM device
I (328) esp_psram: Speed: 80MHz
I (331) cpu_start: Multicore app
I (760) esp_psram: SPI SRAM memory test OK
I (768) cpu_start: GPIO 44 and 43 are used as console UART I/O pins
I (769) cpu_start: Pro cpu start user code
I (769) cpu_start: cpu freq: 160000000 Hz
I (771) app_init: Application information:
I (775) app_init: Project name:     esp32_wifi_control
I (779) app_init: App version:      42c256e
I (783) app_init: Compile time:     Oct 13 2025 19:21:06
I (788) app_init: ELF file SHA256:  6646d8c6b...
I (793) app_init: ESP-IDF:          v6.0-dev-2039-g2044fba6e7
I (798) efuse_init: Min chip rev:     v0.0
I (802) efuse_init: Max chip rev:     v0.99 
I (806) efuse_init: Chip rev:         v0.2
I (810) heap_init: Initializing. RAM available for dynamic allocation:
I (816) heap_init: At 3FCA34F8 len 00046218 (280 KiB): RAM
I (821) heap_init: At 3FCE9710 len 00005724 (21 KiB): RAM
I (826) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (832) heap_init: At 600FE000 len 00001FE8 (7 KiB): RTCRAM
I (837) esp_psram: Adding pool of 8192K of PSRAM memory to heap allocator
I (844) spi_flash: detected chip: boya
I (847) spi_flash: flash io: qio
W (850) i2c: This driver is an old driver, please migrate your application code to adapt `driver/i2c_master.h`
I (860) sleep_gpio: Configure to isolate all GPIO pins in sleep state
I (866) sleep_gpio: Enable automatic switching of GPIO sleep configuration
I (873) main_task: Started on CPU0
I (893) main_task: Calling app_main()
ESP32S3 Boot Success...
I (913) pp: pp rom version: e7ae62f
I (913) net80211: net80211 rom version: e7ae62f
I (923) wifi:wifi driver task: 3fca8220, prio:23, stack:6656, core=0
I (923) wifi:wifi firmware version: df85326
I (923) wifi:wifi certification version: v7.0
I (923) wifi:config NVS flash: enabled
I (923) wifi:config nano formatting: disabled