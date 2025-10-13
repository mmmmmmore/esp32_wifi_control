2025-10-13


I (843) heap_init: At 3FCE9710 len 00005724 (21 KiB): RAM
I (848) heap_init: At 3FCF0000 len 00008000 (32 KiB): DRAM
I (854) heap_init: At 600FE000 len 00001FE8 (7 KiB): RTCRAM
I (859) esp_psram: Adding pool of 8192K of PSRAM memory to heap allocator
W (866) spi_flash: Quad flash chip is using but opi_str flash mode is selected, will automatically switch to DIO mode
I (876) spi_flash: detected chip: generic
I (880) spi_flash: flash io: dio
E (882) spi_flash: Detected size(32k) smaller than the size in the binary image header(16384k). Probe failed.

assert failed: __esp_system_init_fn_init_flash startup_funcs.c:118 (flash_ret == ESP_OK)


Backtrace: 0x4037ddc5:0x3fceb120 0x4037dd8d:0x3fceb140 0x4038421d:0x3fceb160 0x420026ee:0x3fceb280 0x420031ff:0x3fceb2a0 0x4200324d:0x3fceb2c0 0x420032b7:0x3fceb2e0 0x403755d1:0x3fceb300 0x403ccbe3:0x3fceb330 0x403ccf89:0x3fceb370 0x403c8974:0x3fceb4a0 0x40045c01:0x3fceb570 0x40043ab6:0x3fceb6f0 0x40034c45:0x3fceb710
--- 0x4037ddc5: panic_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/panic.c:480
--- 0x4037dd8d: esp_system_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/esp_system_chip.c:87
--- 0x4038421d: __assert_func at /Users/maochun/esp32prj/esp-idf/components/newlib/src/assert.c:81
--- 0x420026ee: __esp_system_init_fn_init_flash at /Users/maochun/esp32prj/esp-idf/components/esp_system/startup_funcs.c:118
--- 0x420031ff: do_system_init_fn at /Users/maochun/esp32prj/esp-idf/components/esp_system/startup.c:104
--- 0x4200324d: do_core_init at /Users/maochun/esp32prj/esp-idf/components/esp_system/startup.c:142
--- 0x420032b7: start_cpu0_default at /Users/maochun/esp32prj/esp-idf/components/esp_system/startup.c:177
--- 0x403755d1: call_start_cpu0 at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/cpu_start.c:944
--- 0x403ccbe3: set_cache_and_start_app at /Users/maochun/esp32prj/esp-idf/components/bootloader_support/src/bootloader_utility.c:1156
--- (inlined by) unpack_load_app at /Users/maochun/esp32prj/esp-idf/components/bootloader_support/src/bootloader_utility.c:891
--- (inlined by) load_image at /Users/maochun/esp32prj/esp-idf/components/bootloader_support/src/bootloader_utility.c:801
--- 0x403ccf89: bootloader_utility_load_boot_image at /Users/maochun/esp32prj/esp-idf/components/bootloader_support/src/bootloader_utility.c:603
--- 0x403c8974: call_start_cpu0 at /Users/maochun/esp32prj/esp-idf/components/bootloader/subproject/main/bootloader_start.c:62
--- 0x40045c01: ets_run_flash_bootloader in ROM
--- 0x40043ab6: main in ROM
--- 0x40034c45: .stack_ok in ROM




ELF file SHA256: e9a4966b3

Rebooting...
ESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0xc (RTC_SW_CPU_RST),boot:0x8 (SPI_FAST_FLASH_BOOT)
Saved PC:0x4037df65
--- 0x4037df65: esp_restart_noos at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/soc/esp32s3/system_internal.c:164
SPIWP:0xee
mode:DOUT, clock div:1
load:0x3fce2820,len:0x1588
load:0x403c8700,len:0xd7c
--- 0x403c8700: _stext at ??:?
load:0x403cb700,len:0x2f80
entry 0x403c8908
--- 0x403c8908: call_start_cpu0 at /Users/maochun/esp32prj/esp-idf/components/bootloader/subproject/main/bootloader_start.c:25
I (29) boot: ESP-IDF v6.0-dev-2039-g2044fba6e7 2nd stage bootloader
I (29) boot: compile time Oct 13 2025 19:07:35
I (29) boot: Multicore bootloader
I (31) boot: chip revision: v0.2
I (34) boot: efuse block revision: v1.3
I (37) boot.esp32s3: Boot SPI Speed : 80MHz
I (41) boot.esp32s3: SPI Mode       : DOUT
I (45) boot.esp32s3: SPI Flash Size : 16MB
I (49) boot: Enabling RNG early entropy source...
I (53) boot: Partition Table:
I (56) boot: ## Label            Usage          Type ST Offset   Length
I (62) boot:  0 nvs              WiFi data        01 02 00009000 00005000
I (69) boot:  1 otadata          OTA data         01 00 0000e000 00002000
I (75) boot:  2 app0             OTA app          00 10 00010000 00140000
I (82) boot:  3 app1             OTA app          00 11 00150000 00140000
I (88) boot:  4 spiffs           Unknown data     01 82 00290000 00170000
I (95) boot: End of partition table
I (98) esp_image: segment 0: paddr=00010020 vaddr=3c0a0020 size=1f61ch (128540) map
I (130) esp_image: segment 1: paddr=0002f644 vaddr=3fc9a600 size=009d4h (  2516) load
I (131) esp_image: segment 2: paddr=00030020 vaddr=42000020 size=9cdach (642476) map
I (257) esp_image: segment 3: paddr=000ccdd4 vaddr=3fc9afd4 size=04774h ( 18292) load
I (262) esp_image: segment 4: paddr=000d1550 vaddr=40374000 size=1650ch ( 91404) load
I (283) esp_image: segment 5: paddr=000e7a64 vaddr=50000000 size=00020h (    32) load
I (293) boot: Loaded app from partition at offset 0x10000
I (293) boot: Disabling RNG early entropy source...
I (303) octal_psram: vendor id    : 0x0d (AP)
I (303) octal_psram: dev id       : 0x02 (generation 3)
I (304) octal_psram: density      : 0x03 (64 Mbit)
I (306) octal_psram: good-die     : 0x01 (Pass)
I (310) octal_psram: Latency      : 0x01 (Fixed)
I (314) octal_psram: VCC          : 0x01 (3V)
I (318) octal_psram: SRF          : 0x01 (Fast Refresh)
I (323) octal_psram: BurstType    : 0x01 (Hybrid Wrap)
I (328) octal_psram: BurstLen     : 0x01 (32 Byte)
I (333) octal_psram: Readlatency  : 0x02 (10 cycles@Fixed)
I (338) octal_psram: DriveStrength: 0x00 (1/1)
I (343) MSPI Timing: PSRAM timing tuning index: 4
I (346) esp_psram: Found 8MB PSRAM device
I (350) esp_psram: Speed: 80MHz
I (353) cpu_start: Multicore app


NOTICE: Processing 3 dependencies:
NOTICE: [1/3] espressif/esp_jpeg (1.3.1)
NOTICE: [2/3] espressif/esp_new_jpeg (0.6.1)
NOTICE: [3/3] idf (6.0.0)
CMake Error at /Users/maochun/esp32prj/esp-idf/tools/cmake/build.cmake:653 (include):
  include could not find requested file:

    /Users/maochun/esp32prj/Project_CAM/branch/esp32_wifi_control/build/managed_components_list.temp.cmake
Call Stack (most recent call first):
  /Users/maochun/esp32prj/esp-idf/tools/cmake/project.cmake:740 (idf_build_process)
  CMakeLists.txt:19 (project)


-- ESP-TEE is currently supported only on the esp32c6;esp32h2;esp32c5 SoCs
CMake Error at /Users/maochun/esp32prj/esp-idf/tools/cmake/component.cmake:256 (message):
  ERROR: Cannot find component list file.  Please make sure this script is
  executed from CMake

Call Stack (most recent call first):
  /Users/maochun/esp32prj/esp-idf/tools/cmake/build.cmake:684 (__component_get_requirements)
  /Users/maochun/esp32prj/esp-idf/tools/cmake/project.cmake:740 (idf_build_process)
  CMakeLists.txt:19 (project)



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