
maochun@MMMBP esp32_wifi_control % espcoredump.py -p /dev/tty.usbmodem5AF70906551 dbg_corefile build/esp32_wifi_control.elf
INFO: Invoke esptool to read image.
INFO: Retrieving core dump partition offset and size...
Traceback (most recent call last):
  File "/Users/maochun/esp32prj/esp-idf/components/espcoredump/espcoredump.py", line 76, in <module>
    main()
    ~~~~^^
  File "/Users/maochun/esp32prj/esp-idf/components/espcoredump/espcoredump.py", line 63, in main
    temp_core_files = espcoredump.dbg_corefile()
  File "/Users/maochun/esp32prj/esp-idf/tools/python_env/idf6.0_py3.13_env/lib/python3.13/site-packages/esp_coredump/coredump.py", line 529, in dbg_corefile
    core_header_info_dict = self.get_core_header_info_dict(e_machine=exe_elf.e_machine)
  File "/Users/maochun/esp32prj/esp-idf/tools/python_env/idf6.0_py3.13_env/lib/python3.13/site-packages/esp_coredump/coredump.py", line 143, in get_core_header_info_dict
    loader = ESPCoreDumpFlashLoader(self.coredump_off, port=self.port, baud=self.baud, part_table_offset=self.parttable_off)
  File "/Users/maochun/esp32prj/esp-idf/tools/python_env/idf6.0_py3.13_env/lib/python3.13/site-packages/esp_coredump/corefile/loader.py", line 556, in __init__
    self._get_core_src(offset, target)
    ~~~~~~~~~~~~~~~~~~^^^^^^^^^^^^^^^^
  File "/Users/maochun/esp32prj/esp-idf/tools/python_env/idf6.0_py3.13_env/lib/python3.13/site-packages/esp_coredump/corefile/loader.py", line 564, in _get_core_src
    self._invoke_esptool(off=off, target=target)
    ~~~~~~~~~~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^
  File "/Users/maochun/esp32prj/esp-idf/tools/python_env/idf6.0_py3.13_env/lib/python3.13/site-packages/esp_coredump/corefile/loader.py", line 580, in _invoke_esptool
    (part_offset, part_size) = self._get_core_dump_partition_info()
                               ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^^
  File "/Users/maochun/esp32prj/esp-idf/tools/python_env/idf6.0_py3.13_env/lib/python3.13/site-packages/esp_coredump/corefile/loader.py", line 628, in _get_core_dump_partition_info
    (offset_str, size_str) = res.rsplit(b'\n')[-1].split(b' ')
    ^^^^^^^^^^^^^^^^^^^^^^
ValueError: too many values to unpack (expected 2)
maochun@MMMBP esp32_wifi_control % 


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
I (112) esp_image: segment 0: paddr=00010020 vaddr=3c0a0020 size=20894h (133268) map
I (139) esp_image: segment 1: paddr=000308bc vaddr=3fc9a600 size=05618h ( 22040) load
I (144) esp_image: segment 2: paddr=00035edc vaddr=40374000 size=0a13ch ( 41276) load
I (152) esp_image: segment 3: paddr=00040020 vaddr=42000020 size=9f930h (653616) map
I (251) esp_image: segment 4: paddr=000df958 vaddr=4037e13c size=0c3dch ( 50140) load
I (261) esp_image: segment 5: paddr=000ebd3c vaddr=50000000 size=00020h (    32) load
I (271) boot: Loaded app from partition at offset 0x10000
I (271) boot: Disabling RNG early entropy source...
I (281) octal_psram: vendor id    : 0x0d (AP)
I (281) octal_psram: dev id       : 0x02 (generation 3)
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
I (324) esp_psram: Found 8MB PSRAM device
I (328) esp_psram: Speed: 80MHz
I (331) cpu_start: Multicore app
I (760) esp_psram: SPI SRAM memory test OK
I (768) cpu_start: GPIO 44 and 43 are used as console UART I/O pins
I (769) cpu_start: Pro cpu start user code
I (769) cpu_start: cpu freq: 160000000 Hz
I (771) app_init: Application information:
I (775) app_init: Project name:     esp32_wifi_control
I (779) app_init: App version:      47ed799-dirty
I (784) app_init: Compile time:     Oct 13 2025 20:18:57
I (789) app_init: ELF file SHA256:  21ffcbcef...
I (793) app_init: ESP-IDF:          v6.0-dev-2039-g2044fba6e7
I (799) efuse_init: Min chip rev:     v0.0
I (803) efuse_init: Max chip rev:     v0.99 
I (807) efuse_init: Chip rev:         v0.2
I (810) heap_init: Initializing. RAM available for dynamic allocation:
I (817) heap_init: At 3FCA4B00 len 00044C10 (275 KiB): RAM
I (822) heap_init: At 3FCE9710 len 00005724 (21 KiB): RAM
I (827) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (832) heap_init: At 600FE000 len 00001FE8 (7 KiB): RTCRAM
I (838) esp_psram: Adding pool of 8192K of PSRAM memory to heap allocator
I (845) spi_flash: detected chip: boya
I (847) spi_flash: flash io: qio
W (851) i2c: This driver is an old driver, please migrate your application code to adapt `driver/i2c_master.h`
I (860) sleep_gpio: Configure to isolate all GPIO pins in sleep state
I (867) sleep_gpio: Enable automatic switching of GPIO sleep configuration
I (873) esp_core_dump_uart: Init core dump to UART
I (878) main_task: Started on CPU0
I (888) main_task: Calling app_main()
ESP32S3 Boot Success...
I (908) pp: pp rom version: e7ae62f
I (908) net80211: net80211 rom version: e7ae62f
I (918) wifi:wifi driver task: 3fca9828, prio:23, stack:6656, core=0
I (918) wifi:wifi firmware version: df85326
I (918) wifi:wifi certification version: v7.0
I (918) wifi:config NVS flash: enabled
I (918) wifi:config nano formatting: disabled
I (928) wifi:Init data frame dynamic rx buffer num: 32
I (928) wifi:Init static rx mgmt buffer num: 5
I (938) wifi:Init management short buffer num: 32
I (938) wifi:Init dynamic tx buffer num: 32
I (948) wifi:Init static tx FG buffer num: 2
I (948) wifi:Init static rx buffer size: 1600
I (948) wifi:Init static rx buffer num: 10
I (958) wifi:Init dynamic rx buffer num: 32
I (958) wifi_init: rx ba win: 6
I (958) wifi_init: accept mbox: 6
I (968) wifi_init: tcpip mbox: 32
I (968) wifi_init: udp mbox: 6
I (968) wifi_init: tcp mbox: 6
I (978) wifi_init: tcp tx win: 5760
I (978) wifi_init: tcp rx win: 5760
I (978) wifi_init: tcp mss: 1440
I (978) wifi_init: WiFi IRAM OP enabled
I (988) wifi_init: WiFi RX IRAM OP enabled
I (998) phy_init: phy_version 701,f4f1da3a,Mar  3 2025,15:50:10
I (1028) wifi:mode : softAP (dc:b4:d9:04:7c:05)
I (1038) wifi:Total power save buffer number: 16
I (1038) wifi:Init max length of beacon: 752/752
I (1038) wifi:Init max length of beacon: 752/752
I (1038) wifi_ap: WiFi SoftAP started. SSID: ESP32-TEST, Password: niwenwoa
I (1038) esp_netif_lwip: DHCP server started on interface WIFI_AP_DEF with IP: 192.168.4.1
I (1058) wifi_ap: DHCP server is running.
I (1058) PSRAM: PSRAM size: 8388608 bytes
I (1058) PSRAM: Free heap: 8654284 bytes
I (1068) PSRAM: PSRAM is initialized and ready.
I (1068) PSRAM: Successfully allocated 1KB from PSRAM.
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