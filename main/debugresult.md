I (551) wifi:Init max length of beacon: 752/752
I (551) wifi:Init max length of beacon: 752/752
E (551) wifi:failed to post WiFi event=12 ret=259
I (551) wifi_ap: WiFi SoftAP started. SSID: ESP32-TEST, Password: niwenwoa
W (561) wifi_ap: DHCP server is NOT running.
I (621) OV7670: OV7670 initialized

assert failed: tcpip_send_msg_wait_sem /IDF/components/lwip/lwip/src/api/tcpip.c:454 (Invalid mbox)


Backtrace: 0x4037c7e5:0x3fca4ba0 0x4037c7ad:0x3fca4bc0 0x40382a31:0x3fca4be0 0x42053b27:0x3fca4d00 0x4205f8be:0x3fca4d30 0x4205f952:0x3fca4d50 0x42053975:0x3fca4da0 0x42014831:0x3fca4dc0 0x42014efc:0x3fca4e20 0x4200a8d8:0x3fca4e50 0x4200a7ca:0x3fca4f00 0x420067d0:0x3fca4f20 0x42084162:0x3fca4f50
--- 0x4037c7e5: panic_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/panic.c:480
--- 0x4037c7ad: esp_system_abort at /Users/maochun/esp32prj/esp-idf/components/esp_system/port/esp_system_chip.c:87
--- 0x40382a31: __assert_func at /Users/maochun/esp32prj/esp-idf/components/newlib/src/assert.c:81
--- 0x42053b27: tcpip_send_msg_wait_sem at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/tcpip.c:454
--- 0x4205f8be: netconn_apimsg at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/api_lib.c:134
--- 0x4205f952: netconn_new_with_proto_and_callback at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/api_lib.c:164
--- 0x42053975: lwip_socket at /Users/maochun/esp32prj/esp-idf/components/lwip/lwip/src/api/sockets.c:1759
--- 0x42014831: socket at /Users/maochun/esp32prj/esp-idf/components/lwip/include/lwip/sockets.h:70
--- (inlined by) httpd_server_init at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/esp_http_server/src/httpd_main.c:358
--- 0x42014efc: httpd_start at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/esp_http_server/src/httpd_main.c:525
--- 0x4200a8d8: start_webserver at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/protocol/webserver/webserver.c:41
--- 0x4200a7ca: app_main at /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/main/main.c:29
--- 0x420067d0: main_task at /Users/maochun/esp32prj/esp-idf/components/freertos/app_startup.c:208
--- 0x42084162: vPortTaskWrapper at /Users/maochun/esp32prj/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/port.c:139




ELF file SHA256: 0092097ba

Rebooting...

after wifi and DHCP finish

系统初始化完成，等待客户端连接...
I (624) main_task: Returned from app_main()
I (1124) wifi:new:<1,1>, old:<1,1>, ap:<1,1>, sta:<255,255>, prof:1, snd_ch_cfg:0x0
I (1124) wifi:station: 5c:5f:67:ed:16:1a join, AID=1, bgn, 40U
I (1154) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.2
ESP-ROM:esp32s3-20210327
Build:Mar 27 2021
rst:0x8 (TG1WDT_SYS_RST),boot:0x8 (SPI_FAST_FLASH_BOOT)
Saved PC:0x403743c8
--- 0x403743c8: _DoubleExceptionVector at /Users/maochun/esp32prj/esp-idf/components/xtensa/xtensa_vectors.S:568
SPIWP:0xee
mode:DIO, clock div:1
load:0x3fce2820,len:0x1588
load:0x403c8700,len:0xd7c
--- 0x403c8700: _stext at ??:?
load:0x403cb700,len:0x2f80
entry 0x403c8908
--- 0x403c8908: call_start_cpu0 at /Users/maochun/esp32prj/esp-idf/components/bootloader/subproject/main/bootloader_start.c:25
I (29) boot: ESP-IDF v6.0-dev-2039-g2044fba6e7 2nd stage bootloader
I (29) boot: compile time Sep 23 2025 07:58:20
I (29) boot: Multicore bootloader
I (31) boot: chip revision: v0.2


cd /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/build/esp-idf/partition_table && /Users/maochun/.espressif/python_env/idf6.0_py3.13_env/bin/python /Users/maochun/esp32prj/esp-idf/components/partition_table/gen_esp32part.py -q --offset 0x8000 --primary-bootloader-offset 0x0 --flash-size 2MB -- /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/partitions.csv /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/build/partition_table/partition-table.bin && /usr/local/bin/cmake -E echo "Partition table binary generated. Contents:" && /usr/local/bin/cmake -E echo "*******************************************************************************" && /Users/maochun/.espressif/python_env/idf6.0_py3.13_env/bin/python /Users/maochun/esp32prj/esp-idf/components/partition_table/gen_esp32part.py -q --offset 0x8000 --primary-bootloader-offset 0x0 --flash-size 2MB -- /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/build/partition_table/partition-table.bin && /usr/local/bin/cmake -E echo "*******************************************************************************"
Partitions tables occupies 4.0MB of flash (4194304 bytes) which does not fit in configured flash size 2MB. Change the flash size in menuconfig under the 'Serial Flasher Config' menu.


系统初始化完成，等待客户端连接...
I (718) main_task: Returned from app_main()
I (23268) wifi:new:<1,1>, old:<1,1>, ap:<1,1>, sta:<255,255>, prof:1, snd_ch_cfg:0x0
I (23268) wifi:station: 5c:5f:67:ed:16:1a join, AID=1, bgn, 40U
I (30178) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.2
I (31388) wifi:<ba-add>idx:2 (ifx:1, 5c:5f:67:ed:16:1a), tid:0, ssn:73, winSize:64
W (32518) httpd_uri: httpd_uri: Method '1' not allowed for URI '/toggle'
W (32518) httpd_txrx: httpd_resp_send_err: 405 Method Not Allowed - Specified method is invalid for this resource
I (38948) stream_control: Capture set to: OFF
I (71758) stream_control: Capture set to: OFF
I (74228) stream_control: Capture set to: OFF
I (74908) stream_control: Capture set to: OFF
I (76638) stream_control: Capture set to: OFF
I (200758) toggle_handler: Received toggle command: ON
I (200758) stream_control: Capture set to: ON
I (223278) stream_control: Capture set to: ON
E (223278) image_handler: Failed to allocate memory for frame buffer
W (223278) httpd_txrx: httpd_resp_send_err: 500 Internal Server Error - Server has encountered an unexpected error
W (223288) httpd_uri: httpd_uri: uri handler execution failed