2025-10-13


W (870) spi_flash: Detected size(16384k) larger than the size in the binary image header(8192k). Using the size in the binary image header.
W (883) i2c: This driver is an old driver, please migrate your application code to adapt `driver/i2c_master.h`
I (892) sleep_gpio: Configure to isolate all GPIO pins in sleep state
I (898) sleep_gpio: Enable automatic switching of GPIO sleep configuration
I (905) main_task: Started on CPU0
I (915) main_task: Calling app_main()
ESP32S3 Boot Success...
I (935) pp: pp rom version: e7ae62f
I (935) net80211: net80211 rom version: e7ae62f
I (945) wifi:wifi driver task: 3fca8220, prio:23, stack:6656, core=0
I (945) wifi:wifi firmware version: df85326
I (945) wifi:wifi certification version: v7.0
I (945) wifi:config NVS flash: enabled
I (945) wifi:config nano formatting: disabled
I (955) wifi:Init data frame dynamic rx buffer num: 32
I (955) wifi:Init static rx mgmt buffer num: 5
I (965) wifi:Init management short buffer num: 32
I (965) wifi:Init dynamic tx buffer num: 32
I (975) wifi:Init static tx FG buffer num: 2
I (975) wifi:Init static rx buffer size: 1600
I (975) wifi:Init static rx buffer num: 10
I (985) wifi:Init dynamic rx buffer num: 32
I (985) wifi_init: rx ba win: 6
I (985) wifi_init: accept mbox: 6
I (995) wifi_init: tcpip mbox: 32
I (995) wifi_init: udp mbox: 6
I (995) wifi_init: tcp mbox: 6
I (1005) wifi_init: tcp tx win: 5760
I (1005) wifi_init: tcp rx win: 5760
I (1005) wifi_init: tcp mss: 1440
I (1015) wifi_init: WiFi IRAM OP enabled
I (1015) wifi_init: WiFi RX IRAM OP enabled
I (1025) phy_init: phy_version 701,f4f1da3a,Mar  3 2025,15:50:10
I (1065) wifi:mode : softAP (dc:b4:d9:04:7c:05)
I (1065) wifi:Total power save buffer number: 16
I (1065) wifi:Init max length of beacon: 752/752
I (1065) wifi:Init max length of beacon: 752/752
I (1075) wifi_ap: WiFi SoftAP started. SSID: ESP32-TEST, Password: niwenwoa
I (1075) esp_netif_lwip: DHCP server started on interface WIFI_AP_DEF with IP: 192.168.4.1
I (1085) wifi_ap: DHCP server is running.
I (1085) PSRAM: PSRAM size: 8388608 bytes
I (1095) PSRAM: Free heap: 8659788 bytes
I (1095) PSRAM: PSRAM is initialized and ready.
I (1105) PSRAM: Successfully allocated 1KB from PSRAM.
ESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0x8 (TG1WDT_SYS_RST),boot:0x8 (SPI_FAST_FLASH_BOOT)
Saved PC:0x4037577c
--- 0x4037577c: panic_enable_cache at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/panic_handler.c:277
SPIWP:0xee
mode:DIO, clock div:1
load:0x3fce2820,len:0x1588
load:0x403c8700,len:0xd7c
load:0x403cb700,len:0x2f80
entry 0x403c8908
I (29) boot: ESP-IDF v6.0-dev-2039-g2044fba6e7 2nd stage bootloader
I (29) boot: compile time Oct 12 2025 14:46:28
I (29) boot: Multicore bootloader
I (31) boot: chip revision: v0.2
I (34) boot: efuse block revision: v1.3
I (37) boot.esp32s3: Boot SPI Speed : 80MHz
I (41) boot.esp32s3: SPI Mode       : DIO
I (45) boot.esp32s3: SPI Flash Size : 8MB
W (49) boot.esp32s3: PRO CPU has been reset by WDT.
W (53) boot.esp32s3: APP CPU has been reset by WDT.
I (58) boot: Enabling RNG early entropy source...
I (62) boot: Partition Table:
I (65) boot: ## Label            Usage          Type ST Offset   Length
I (71) boot:  0 nvs              WiFi data        01 02 00009000 00005000
I (78) boot:  1 otadata          OTA data         01 00 0000e000 00002000
I (84) boot:  2 app0             OTA app          00 10 00010000 00140000
I (91) boot:  3 app1             OTA app          00 11 00150000 00140000
I (97) boot:  4 spiffs           Unknown data     01 82 00290000 00170000
I (104) boot: End of partition table
I (107) esp_image: segment 0: paddr=00010020 vaddr=3c0a0020 size=1f60ch (128524) map
I (138) esp_image: segment 1: paddr=0002f634 vaddr=3fc9a600 size=009e4h (  2532) load
I (139) esp_image: segment 2: paddr=00030020 vaddr=42000020 size=9cda8h (642472) map
I (257) esp_image: segment 3: paddr=000ccdd0 vaddr=3fc9afe4 size=04764h ( 18276) load
I (261) esp_image: segment 4: paddr=000d153c vaddr=40374000 size=16514h ( 91412) load
I (281) esp_image: segment 5: paddr=000e7a58 vaddr=50000000 size=00020h (    32) load
I (291) boot: Loaded app from partition at offset 0x10000
I (291) boot: Disabling RNG early entropy source...
I (301) octal_psram: vendor id    : 0x0d (AP)
I (302) octal_psram: dev id       : 0x02 (generation 3)
I (302) octal_psram: density      : 0x03 (64 Mbit)
I (304) octal_psram: good-die     : 0x01 (Pass)
I (308) octal_psram: Latency      : 0x01 (Fixed)
I (312) octal_psram: VCC          : 0x01 (3V)
I (316) octal_psram: SRF          : 0x01 (Fast Refresh)
I (321) octal_psram: BurstType    : 0x01 (Hybrid Wrap)
I (326) octal_psram: BurstLen     : 0x01 (32 Byte)
I (331) octal_psram: Readlatency  : 0x02 (10 cycles@Fixed)
I (336) octal_psram: DriveStrength: 0x00 (1/1)
I (341) MSPI Timing: PSRAM timing tuning index: 4
I (345) esp_psram: Found 8MB PSRAM device
I (348) esp_psram: Speed: 80MHz
I (351) cpu_start: Multicore app