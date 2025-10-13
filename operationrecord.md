
I (1057) PSRAM: PSRAM size: 8388608 bytes
I (1057) PSRAM: Free heap: 8657900 bytes
I (1067) PSRAM: PSRAM is initialized and ready.
I (1067) PSRAM: Successfully allocated 1KB from PSRAM.
ESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0x8 (TG1WDT_SYS_RST),boot:0x8 (SPI_FAST_FLASH_BOOT)
Saved PC:0x40375780
--- 0x40375780: panic_enable_cache at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/panic_handler.c:277
SPIWP:0xee
mode:DIO, clock div:1
load:0x3fce2820,len:0x16fc
load:0x403c8700,len:0xf14
load:0x403cb700,len:0x3214
entry 0x403c8930
I (29) boot: ESP-IDF v6.0-dev-2039-g2044fba6e7 2nd stage bootloader
I (29) boot: compile time Oct 13 2025 19:47:23
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
I (112) esp_image: segment 0: paddr=00010020 vaddr=3c0a0020 size=20644h (132676) map
I (139) esp_image: segment 1: paddr=0003066c vaddr=3fc9a600 size=05618h ( 22040) load
I (144) esp_image: segment 2: paddr=00035c8c vaddr=40374000 size=0a38ch ( 41868) load
I (152) esp_image: segment 3: paddr=00040020 vaddr=42000020 size=9ea70h (649840) map
I (251) esp_image: segment 4: paddr=000dea98 vaddr=4037e38c size=0c18ch ( 49548) load
I (261) esp_image: segment 5: paddr=000eac2c vaddr=50000000 size=00020h (    32) load
I (270) boot: Loaded app from partition at offset 0x10000
I (271) boot: Disabling RNG early entropy source...
I (281) octal_psram: vendor id    : 0x0d (AP)
I (281) octal_psram: dev id       : 0x02 (generation 3)
I (281) octal_psram: density      : 0x03 (64 Mbit)
I (283) octal_psram: good-die     : 0x01 (Pass)
I (287) octal_psram: Latency      : 0x01 (Fixed)
I (292) octal_psram: VCC          : 0x01 (3V)
I (296) octal_psram: SRF          : 0x01 (Fast Refresh)
I (301) octal_psram: BurstType    : 0x01 (Hybrid Wrap)
I (305) octal_psram: BurstLen     : 0x01 (32 Byte)
I (310) octal_psram: Readlatency  : 0x02 (10 cycles@Fixed)
I (315) octal_psram: DriveStrength: 0x00 (1/1)
I (320) MSPI Timing: PSRAM timing tuning index: 4
I (324) esp_psram: Found 8MB PSRAM device
I (327) esp_psram: Speed: 80MHz
I (330) cpu_start: Multicore app
I (759) esp_psram: SPI SRAM memory test OK
I (768) cpu_start: GPIO 44 and 43 are used as console UART I/O pins
I (768) cpu_start: Pro cpu start user code
I (768) cpu_start: cpu freq: 160000000 Hz
I (770) app_init: Application information:
I (774) app_init: Project name:     esp32_wifi_control
I (779) app_init: App version:      01081db
I (783) app_init: Compile time:     Oct 13 2025 19:46:56
I (788) app_init: ELF file SHA256:  9aeb37d83...
I (792) app_init: ESP-IDF:          v6.0-dev-2039-g2044fba6e7
I (798) efuse_init: Min chip rev:     v0.0
I (801) efuse_init: Max chip rev:     v0.99 
I (805) efuse_init: Chip rev:         v0.2
I (809) heap_init: Initializing. RAM available for dynamic allocation:
I (815) heap_init: At 3FCA3CE0 len 00045A30 (278 KiB): RAM
I (821) heap_init: At 3FCE9710 len 00005724 (21 KiB): RAM
I (826) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (831) heap_init: At 600FE000 len 00001FE8 (7 KiB): RTCRAM
I (836) esp_psram: Adding pool of 8192K of PSRAM memory to heap allocator
I (843) spi_flash: detected chip: boya
I (846) spi_flash: flash io: qio
W (849) i2c: This driver is an old driver, please migrate your application code to adapt `driver/i2c_master.h`
I (859) sleep_gpio: Configure to isolate all GPIO pins in sleep state
I (865) sleep_gpio: Enable automatic switching of GPIO sleep configuration
I (872) esp_core_dump_uart: Init core dump to UART
I (877) main_task: Started on CPU0
I (887) main_task: Calling app_main()
ESP32S3 Boot Success...