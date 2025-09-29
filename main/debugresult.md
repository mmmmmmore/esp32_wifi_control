2025-09-29:
change VSYNC to GPIO21, no warning print:
ESP32S3 Boot Success...
I (917) pp: pp rom version: e7ae62f
I (917) net80211: net80211 rom version: e7ae62f
I (927) wifi:wifi driver task: 3fca7fa0, prio:23, stack:6656, core=0
I (927) wifi:wifi firmware version: df85326
I (927) wifi:wifi certification version: v7.0
I (927) wifi:config NVS flash: enabled
I (927) wifi:config nano formatting: disabled
I (937) wifi:Init data frame dynamic rx buffer num: 32
I (937) wifi:Init static rx mgmt buffer num: 5
I (947) wifi:Init management short buffer num: 32
I (947) wifi:Init dynamic tx buffer num: 32
I (957) wifi:Init static tx FG buffer num: 2
I (957) wifi:Init static rx buffer size: 1600
I (957) wifi:Init static rx buffer num: 10
I (967) wifi:Init dynamic rx buffer num: 32
I (967) wifi_init: rx ba win: 6
I (967) wifi_init: accept mbox: 6
I (977) wifi_init: tcpip mbox: 32
I (977) wifi_init: udp mbox: 6
I (977) wifi_init: tcp mbox: 6
I (987) wifi_init: tcp tx win: 5760
I (987) wifi_init: tcp rx win: 5760
I (987) wifi_init: tcp mss: 1440
I (997) wifi_init: WiFi IRAM OP enabled
I (997) wifi_init: WiFi RX IRAM OP enabled
I (1007) phy_init: phy_version 701,f4f1da3a,Mar  3 2025,15:50:10
I (1047) wifi:mode : softAP (dc:b4:d9:04:7c:05)
I (1057) wifi:Total power save buffer number: 16
I (1057) wifi:Init max length of beacon: 752/752
I (1057) wifi:Init max length of beacon: 752/752
I (1057) wifi_ap: WiFi SoftAP started. SSID: ESP32-TEST, Password: niwenwoa
I (1057) esp_netif_lwip: DHCP server started on interface WIFI_AP_DEF with IP: 192.168.4.1
I (1067) wifi_ap: DHCP server is running.
I (1077) PSRAM: PSRAM size: 8388608 bytes
I (1077) PSRAM: Free heap: 8660224 bytes
I (1087) PSRAM: PSRAM is initialized and ready.
I (1087) PSRAM: Successfully allocated 1KB from PSRAM.
I (1087) camera: : Initializing camera sensor...
I (1097) camera: : Camera sensor initialization complete.
I (1187) SPIFFS:: SPIFFS mounted successfully
I (1187) webserver: Starting webserver...
I (1197) webserver: Webserver started
系统初始化完成，等待客户端连接...
I (1197) main_task: Returned from app_main()
I (6617) wifi:new:<1,1>, old:<1,1>, ap:<1,1>, sta:<255,255>, prof:1, snd_ch_cfg:0x0
I (6617) wifi:station: 5c:5f:67:ed:16:1a join, AID=1, bgn, 40U
I (6667) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.2
I (9637) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.2
I (9727) webserver: HTTP GET /
I (9787) webserver: HTTP GET /favicon.ico
I (12767) webserver: HTTP POST /toggle
I (12767) webserver: Received toggle command: ON
I (15987) webserver: HTTP GET /image
I (15987) webserver: Allocating frame buffer (153600 bytes)
I (15987) webserver: Free heap before alloc: 8650924
I (15987) OV7670_HANDLER: Reading raw frame of size: 153600
I (15987) OV7670_HANDLER: Resetting FIFO read pointer...
I (15997) OV7670_HANDLER: Enabling FIFO output...
I (15997) OV7670_HANDLER: Byte[0] = 0x62
I (16007) OV7670_HANDLER: Byte[1] = 0x02
I (16007) OV7670_HANDLER: Byte[2] = 0x02
I (16007) OV7670_HANDLER: Byte[3] = 0xEE
I (16597) OV7670_HANDLER: Disabling FIFO output...
I (16597) OV7670_HANDLER: Raw frame read complete
I (16597) jpeg: Allocating initial JPEG buffer: 76800 bytes
I (16597) jpeg: Allocating RGB888 buffer: 230400 bytes
I (16607) jpeg: Converting RGB565 to RGB888...
I (16607) jpeg: First pixel RGB565: 0x0262 → RGB888: R=0 G=76 B=16
I (16637) jpeg: Starting JPEG encoding...
W (16637) jpeg: JPEG buffer expanded to 307200 bytes
I (16647) jpeg: JPEG encoding successful: 230422 bytes
I (16647) webserver: JPEG encoded size: 230422 bytes
I (16817) wifi:<ba-add>idx:2 (ifx:1, 5c:5f:67:ed:16:1a), tid:0, ssn:145, winSize:64
I (63027) webserver: HTTP GET /image
I (63027) webserver: Allocating frame buffer (153600 bytes)
I (63027) webserver: Free heap before alloc: 8650844
I (63037) OV7670_HANDLER: Reading raw frame of size: 153600
I (63037) OV7670_HANDLER: Resetting FIFO read pointer...
I (63047) OV7670_HANDLER: Enabling FIFO output...
I (63047) OV7670_HANDLER: Byte[0] = 0x02
I (63047) OV7670_HANDLER: Byte[1] = 0xED
I (63057) OV7670_HANDLER: Byte[2] = 0xED
I (63057) OV7670_HANDLER: Byte[3] = 0x01
I (63647) OV7670_HANDLER: Disabling FIFO output...
I (63647) OV7670_HANDLER: Raw frame read complete
I (63647) jpeg: Allocating initial JPEG buffer: 76800 bytes
I (63647) jpeg: Allocating RGB888 buffer: 230400 bytes
I (63657) jpeg: Converting RGB565 to RGB888...
I (63657) jpeg: First pixel RGB565: 0xED02 → RGB888: R=232 G=160 B=16
I (63677) jpeg: Starting JPEG encoding...
W (63687) jpeg: JPEG buffer expanded to 307200 bytes
I (63697) jpeg: JPEG encoding successful: 230422 bytes
I (63697) webserver: JPEG encoded size: 230422 bytes


update init sequence
I (848) spi_flash: flash io: dio
W (851) spi_flash: Detected size(16384k) larger than the size in the binary image header(8192k). Using the size in the binary image header.
W (864) i2c: This driver is an old driver, please migrate your application code to adapt `driver/i2c_master.h`
I (873) sleep_gpio: Configure to isolate all GPIO pins in sleep state
I (880) sleep_gpio: Enable automatic switching of GPIO sleep configuration
I (887) main_task: Started on CPU0
I (897) main_task: Calling app_main()
ESP32S3 Boot Success...
I (917) pp: pp rom version: e7ae62f
I (917) net80211: net80211 rom version: e7ae62f
I (927) wifi:wifi driver task: 3fca7fa0, prio:23, stack:6656, core=0
I (927) wifi:wifi firmware version: df85326
I (927) wifi:wifi certification version: v7.0
I (927) wifi:config NVS flash: enabled
I (927) wifi:config nano formatting: disabled
I (937) wifi:Init data frame dynamic rx buffer num: 32
I (937) wifi:Init static rx mgmt buffer num: 5
I (947) wifi:Init management short buffer num: 32
I (947) wifi:Init dynamic tx buffer num: 32
I (957) wifi:Init static tx FG buffer num: 2
I (957) wifi:Init static rx buffer size: 1600
I (957) wifi:Init static rx buffer num: 10
I (967) wifi:Init dynamic rx buffer num: 32
I (967) wifi_init: rx ba win: 6
I (967) wifi_init: accept mbox: 6
I (977) wifi_init: tcpip mbox: 32
I (977) wifi_init: udp mbox: 6
I (977) wifi_init: tcp mbox: 6
I (987) wifi_init: tcp tx win: 5760
I (987) wifi_init: tcp rx win: 5760
I (987) wifi_init: tcp mss: 1440
I (997) wifi_init: WiFi IRAM OP enabled
I (997) wifi_init: WiFi RX IRAM OP enabled
I (1007) phy_init: phy_version 701,f4f1da3a,Mar  3 2025,15:50:10
I (1047) phy_init: Saving new calibration data due to checksum failure or outdated calibration data, mode(0)
I (1107) wifi:mode : softAP (dc:b4:d9:04:7c:05)
I (1117) wifi:Total power save buffer number: 16
I (1117) wifi:Init max length of beacon: 752/752
I (1117) wifi:Init max length of beacon: 752/752
I (1117) wifi_ap: WiFi SoftAP started. SSID: ESP32-TEST, Password: niwenwoa
I (1117) esp_netif_lwip: DHCP server started on interface WIFI_AP_DEF with IP: 192.168.4.1
I (1137) wifi_ap: DHCP server is running.
I (1137) PSRAM: PSRAM size: 8388608 bytes
I (1137) PSRAM: Free heap: 8660424 bytes
I (1147) PSRAM: PSRAM is initialized and ready.
I (1147) PSRAM: Successfully allocated 1KB from PSRAM.
I (1157) camera: : Initializing camera sensor...
W (1197) camera: : VSYNC signal not detected
I (1197) camera: : Camera sensor initialization complete.
I (1287) SPIFFS:: SPIFFS mounted successfully
I (1287) webserver: Starting webserver...
I (1287) webserver: Webserver started
系统初始化完成，等待客户端连接...
I (1287) main_task: Returned from app_main()
I (6157) wifi:new:<1,1>, old:<1,1>, ap:<1,1>, sta:<255,255>, prof:1, snd_ch_cfg:0x0
I (6157) wifi:station: 5c:5f:67:ed:16:1a join, AID=1, bgn, 40U
I (6187) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.2
I (9497) webserver: HTTP POST /toggle
I (9507) webserver: Received toggle command: ON
I (9567) wifi:<ba-add>idx:2 (ifx:1, 5c:5f:67:ed:16:1a), tid:0, ssn:53, winSize:64
I (11597) webserver: HTTP GET /image
I (11597) webserver: Allocating frame buffer (153600 bytes)
I (11597) webserver: Free heap before alloc: 8650364
I (11607) OV7670_HANDLER: Reading raw frame of size: 153600
I (11607) OV7670_HANDLER: Resetting FIFO read pointer...
I (11617) OV7670_HANDLER: Enabling FIFO output...
I (11617) OV7670_HANDLER: Byte[0] = 0x00
I (11617) OV7670_HANDLER: Byte[1] = 0x00
I (11627) OV7670_HANDLER: Byte[2] = 0x0C
I (11627) OV7670_HANDLER: Byte[3] = 0xEC
I (12217) OV7670_HANDLER: Disabling FIFO output...
I (12217) OV7670_HANDLER: Raw frame read complete
I (12217) jpeg: Allocating initial JPEG buffer: 76800 bytes
I (12217) jpeg: Allocating RGB888 buffer: 230400 bytes
I (12227) jpeg: Converting RGB565 to RGB888...
I (12227) jpeg: First pixel RGB565: 0x0000 → RGB888: R=0 G=0 B=0
I (12247) jpeg: Starting JPEG encoding...
W (12257) jpeg: JPEG buffer expanded to 307200 bytes
I (12267) jpeg: JPEG encoding successful: 230422 bytes
I (12267) webserver: JPEG encoded size: 230422 bytes


系统初始化完成，等待客户端连接...
I (1186) main_task: Returned from app_main()
I (6066) wifi:new:<1,1>, old:<1,1>, ap:<1,1>, sta:<255,255>, prof:1, snd_ch_cfg:0x0
I (6066) wifi:station: 5c:5f:67:ed:16:1a join, AID=1, bgn, 40U
I (6096) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.2
I (9696) wifi:<ba-add>idx:2 (ifx:1, 5c:5f:67:ed:16:1a), tid:0, ssn:55, winSize:64
I (12896) webserver: HTTP POST /toggle
I (12896) webserver: Received toggle command: ON
I (15876) webserver: HTTP GET /image
I (15876) webserver: Allocating frame buffer (153600 bytes)
I (15876) webserver: Free heap before alloc: 8650740
I (15876) OV7670_HANDLER: Reading raw frame of size: 153600
I (15886) OV7670_HANDLER: Resetting FIFO read pointer...
I (15886) OV7670_HANDLER: Enabling FIFO output...
I (15896) OV7670_HANDLER: Byte[0] = 0xE8
I (15896) OV7670_HANDLER: Byte[1] = 0x40
I (15906) OV7670_HANDLER: Byte[2] = 0x00
I (15906) OV7670_HANDLER: Byte[3] = 0x00
I (16486) OV7670_HANDLER: Disabling FIFO output...
I (16486) OV7670_HANDLER: Raw frame read complete
I (16496) jpeg: Allocating initial JPEG buffer: 76800 bytes
I (16496) jpeg: Allocating RGB888 buffer: 230400 bytes
I (16496) jpeg: Converting RGB565 to RGB888...
I (16506) jpeg: First pixel RGB565: 0x40E8 → RGB888: R=64 G=28 B=64
I (16526) jpeg: Starting JPEG encoding...
W (16526) jpeg: JPEG buffer expanded to 307200 bytes
I (16546) jpeg: JPEG encoding successful: 230422 bytes
I (16546) webserver: JPEG encoded size: 230422 bytes
I (26636) webserver: HTTP GET /image
I (26636) webserver: Allocating frame buffer (153600 bytes)
I (26636) webserver: Free heap before alloc: 8650740
I (26636) OV7670_HANDLER: Reading raw frame of size: 153600
I (26636) OV7670_HANDLER: Resetting FIFO read pointer...
I (26646) OV7670_HANDLER: Enabling FIFO output...
I (26646) OV7670_HANDLER: Byte[0] = 0xE8
I (26656) OV7670_HANDLER: Byte[1] = 0xE8
I (26656) OV7670_HANDLER: Byte[2] = 0x00
I (26656) OV7670_HANDLER: Byte[3] = 0x00
I (27246) OV7670_HANDLER: Disabling FIFO output...
I (27246) OV7670_HANDLER: Raw frame read complete
I (27246) jpeg: Allocating initial JPEG buffer: 76800 bytes
I (27246) jpeg: Allocating RGB888 buffer: 230400 bytes
I (27256) jpeg: Converting RGB565 to RGB888...
I (27256) jpeg: First pixel RGB565: 0xE8E8 → RGB888: R=232 G=28 B=64
I (27276) jpeg: Starting JPEG encoding...
W (27286) jpeg: JPEG buffer expanded to 307200 bytes
I (27296) jpeg: JPEG encoding successful: 230422 bytes
I (27296) webserver: JPEG encoded size: 230422 bytes
I (33706) webserver: HTTP GET /image
I (33706) webserver: Allocating frame buffer (153600 bytes)
I (33706) webserver: Free heap before alloc: 8650740
I (33716) OV7670_HANDLER: Reading raw frame of size: 153600
I (33716) OV7670_HANDLER: Resetting FIFO read pointer...
I (33726) OV7670_HANDLER: Enabling FIFO output...
I (33726) OV7670_HANDLER: Byte[0] = 0xE8
I (33726) OV7670_HANDLER: Byte[1] = 0xE8
I (33736) OV7670_HANDLER: Byte[2] = 0xE8
I (33736) OV7670_HANDLER: Byte[3] = 0x00
I (34326) OV7670_HANDLER: Disabling FIFO output...
I (34326) OV7670_HANDLER: Raw frame read complete
I (34326) jpeg: Allocating initial JPEG buffer: 76800 bytes
I (34326) jpeg: Allocating RGB888 buffer: 230400 bytes
I (34336) jpeg: Converting RGB565 to RGB888...
I (34336) jpeg: First pixel RGB565: 0xE8E8 → RGB888: R=232 G=28 B=64
I (34356) jpeg: Starting JPEG encoding...
W (34366) jpeg: JPEG buffer expanded to 307200 bytes
I (34376) jpeg: JPEG encoding successful: 230422 bytes
I (34376) webserver: JPEG encoded size: 230422 bytes
I (37976) webserver: HTTP GET /image
I (37976) webserver: Allocating frame buffer (153600 bytes)
I (37976) webserver: Free heap before alloc: 8650740
I (37976) OV7670_HANDLER: Reading raw frame of size: 153600
I (37986) OV7670_HANDLER: Resetting FIFO read pointer...
I (37986) OV7670_HANDLER: Enabling FIFO output...
I (37996) OV7670_HANDLER: Byte[0] = 0xE8
I (37996) OV7670_HANDLER: Byte[1] = 0x00
I (37996) OV7670_HANDLER: Byte[2] = 0x00
I (38006) OV7670_HANDLER: Byte[3] = 0x00
I (38596) OV7670_HANDLER: Disabling FIFO output...
I (38596) OV7670_HANDLER: Raw frame read complete
I (38596) jpeg: Allocating initial JPEG buffer: 76800 bytes
I (38596) jpeg: Allocating RGB888 buffer: 230400 bytes
I (38596) jpeg: Converting RGB565 to RGB888...
I (38606) jpeg: First pixel RGB565: 0x00E8 → RGB888: R=0 G=28 B=64
I (38626) jpeg: Starting JPEG encoding...
W (38626) jpeg: JPEG buffer expanded to 307200 bytes
I (38646) jpeg: JPEG encoding successful: 230422 bytes
I (38646) webserver: JPEG encoded size: 230422 bytes




I (24696) webserver: HTTP GET /image
I (24696) webserver: Allocating frame buffer (153600 bytes)
I (24696) webserver: Free heap before alloc: 8650752
I (24696) OV7670_HANDLER: Reading raw frame of size: 153600
I (24706) OV7670_HANDLER: Resetting FIFO read pointer...
I (24706) OV7670_HANDLER: Enabling FIFO output...
I (24716) OV7670_HANDLER: Byte[0] = 0x00
I (24716) OV7670_HANDLER: Byte[1] = 0xE8
I (24716) OV7670_HANDLER: Byte[2] = 0xE8
I (24726) OV7670_HANDLER: Byte[3] = 0x60
I (25306) OV7670_HANDLER: Disabling FIFO output...
I (25306) OV7670_HANDLER: Raw frame read complete
I (25316) jpeg: Allocating initial JPEG buffer: 76800 bytes
I (25316) jpeg: Allocating RGB888 buffer: 230400 bytes
I (25316) jpeg: Converting RGB565 to RGB888...
I (25326) jpeg: First pixel RGB565: 0xE800 → RGB888: R=232 G=0 B=0
I (25346) jpeg: Starting JPEG encoding...
W (25346) jpeg: JPEG buffer expanded to 307200 bytes
I (25356) jpeg: JPEG encoding successful: 230422 bytes
I (25356) webserver: JPEG encoded size: 230422 bytes


2025-9-28:
I (24556) webserver: HTTP GET /image
I (24556) webserver: Allocating frame buffer (153600 bytes)
I (24556) webserver: Free heap before alloc: 8650740
I (25146) jpeg: Allocating initial JPEG buffer: 76800 bytes
I (25146) jpeg: Allocating RGB888 buffer: 230400 bytes
I (25146) jpeg: Converting RGB565 to RGB888...
I (25146) jpeg: First pixel RGB565: 0x0000 → RGB888: R=0 G=0 B=0
I (25166) jpeg: Starting JPEG encoding...
W (25176) jpeg: JPEG buffer expanded to 307200 bytes
I (25186) jpeg: JPEG encoding successful: 230422 bytes
I (25186) webserver: JPEG encoded size: 230422 bytes


I (12166) webserver: HTTP GET /
I (12176) webserver: HTTP POST /toggle
I (12176) webserver: Received toggle command: ON
I (13086) webserver: HTTP GET /favicon.ico
I (13776) webserver: HTTP GET /image
I (13776) webserver: Allocating frame buffer (153600 bytes)
I (13776) webserver: Free heap before alloc: 8650728
I (14356) jpeg: Allocating initial JPEG buffer: 76800 bytes
I (14356) jpeg: Allocating RGB888 buffer: 230400 bytes
E (14356) jpeg: Failed to allocate RGB888 buffer
E (14366) webserver: JPEG encoding failed
W (14366) httpd_txrx: httpd_resp_send_err: 500 Internal Server Error - Server has encountered an unexpected error
W (14376) httpd_uri: httpd_uri: uri handler execution failed

I (11696) webserver: HTTP GET /
I (11806) webserver: HTTP GET /favicon.ico
I (14696) webserver: HTTP POST /toggle
I (14696) webserver: Received toggle command: ON
I (16096) webserver: HTTP GET /image
I (16096) webserver: Allocating frame buffer (153600 bytes)
I (16096) webserver: Free heap before alloc: 8650412
I (16676) jpeg: Allocating initial JPEG buffer: 76800 bytes
I (16676) jpeg: Allocating RGB888 buffer: 230400 bytes
I (16676) jpeg: Converting RGB565 to RGB888...
I (16686) jpeg: First pixel RGB565: 0x0000 → RGB888: R=0 G=0 B=0
I (16706) jpeg: Starting JPEG encoding...
E (16706) jpeg: Failed to realloc JPEG buffer
I (16706) jpeg: JPEG encoding successful: 22 bytes
I (16706) webserver: JPEG encoded size: 22 bytes



I (17956) jpeg: Allocating JPEG buffer: 76800 bytes
I (17956) jpeg: Allocating RGB888 buffer: 230400 bytes
I (17956) jpeg: Converting RGB565 to RGB888...
I (17956) jpeg: First pixel RGB565: 0xE8E8 → RGB888: R=232 G=28 B=64
I (17976) jpeg: Starting JPEG encoding...
E (17976) jpeg: JPEG buffer overflow: size=230420, capacity=76800
I (17976) jpeg: JPEG encoding successful: 22 bytes
I (17986) webserver: JPEG encoded size: 22 bytes


2025-09-27
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:41:7: note: in expansion of macro 'REG_COM7'
   41 |     { REG_COM7, 0x80 },     //reverse
      |       ^~~~~~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera_reg.h:31:25: note: (near initialization for 'ov7670_qvga_rgb565')
   31 | #define REG_COM7        0x12
      |                         ^~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:41:7: note: in expansion of macro 'REG_COM7'
   41 |     { REG_COM7, 0x80 },     //reverse
      |       ^~~~~~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:41:17: warning: excess elements in scalar initializer
   41 |     { REG_COM7, 0x80 },     //reverse
      |                 ^~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:41:17: note: (near initialization for 'ov7670_qvga_rgb565')
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:42:5: warning: braces around scalar initializer
   42 |     { REG_CLKRC, 0x80 },    //use external clk signal
      |     ^
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:42:5: note: (near initialization for 'ov7670_qvga_rgb565')
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera_reg.h:30:25: error: initialization of 'const struct regval_list *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
   30 | #define REG_CLKRC       0x11
      |                         ^~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:42:7: note: in expansion of macro 'REG_CLKRC'
   42 |     { REG_CLKRC, 0x80 },    //use external clk signal
      |       ^~~~~~~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera_reg.h:30:25: note: (near initialization for 'ov7670_qvga_rgb565')
   30 | #define REG_CLKRC       0x11
      |                         ^~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:42:7: note: in expansion of macro 'REG_CLKRC'
   42 |     { REG_CLKRC, 0x80 },    //use external clk signal
      |       ^~~~~~~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:42:18: warning: excess elements in scalar initializer
   42 |     { REG_CLKRC, 0x80 },    //use external clk signal
      |                  ^~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:42:18: note: (near initialization for 'ov7670_qvga_rgb565')
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:42:5: warning: excess elements in scalar initializer
   42 |     { REG_CLKRC, 0x80 },    //use external clk signal
      |     ^
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:42:5: note: (near initialization for 'ov7670_qvga_rgb565')
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:43:5: warning: braces around scalar initializer
   43 |     { REG_COM11, 0x0A },    //use BD50ST and expourse time smaller
      |     ^
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:43:5: note: (near initialization for 'ov7670_qvga_rgb565')
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera_reg.h:63:25: error: initialization of 'const struct regval_list *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
   63 | #define REG_COM11       0x3B
      |                         ^~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:43:7: note: in expansion of macro 'REG_COM11'
   43 |     { REG_COM11, 0x0A },    //use BD50ST and expourse time smaller
      |       ^~~~~~~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera_reg.h:63:25: note: (near initialization for 'ov7670_qvga_rgb565')
   63 | #define REG_COM11       0x3B
      |                         ^~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:43:7: note: in expansion of macro 'REG_COM11'
   43 |     { REG_COM11, 0x0A },    //use BD50ST and expourse time smaller
      |       ^~~~~~~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:43:18: warning: excess elements in scalar initializer
   43 |     { REG_COM11, 0x0A },    //use BD50ST and expourse time smaller
      |                  ^~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:43:18: note: (near initialization for 'ov7670_qvga_rgb565')
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:43:5: warning: excess elements in scalar initializer
   43 |     { REG_COM11, 0x0A },    //use BD50ST and expourse time smaller
      |     ^
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:43:5: note: (near initialization for 'ov7670_qvga_rgb565')
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:44:5: warning: braces around scalar initializer
   44 |     { REG_COM7, 0x04 },     //output RGB mode
      |     ^
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:44:5: note: (near initialization for 'ov7670_qvga_rgb565')
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera_reg.h:31:25: error: initialization of 'const struct regval_list *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
   31 | #define REG_COM7        0x12
      |                         ^~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:44:7: note: in expansion of macro 'REG_COM7'
   44 |     { REG_COM7, 0x04 },     //output RGB mode
      |       ^~~~~~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera_reg.h:31:25: note: (near initialization for 'ov7670_qvga_rgb565')
   31 | #define REG_COM7        0x12
      |                         ^~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:44:7: note: in expansion of macro 'REG_COM7'
   44 |     { REG_COM7, 0x04 },     //output RGB mode
      |       ^~~~~~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:44:17: warning: excess elements in scalar initializer
   44 |     { REG_COM7, 0x04 },     //output RGB mode
      |                 ^~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:44:17: note: (near initialization for 'ov7670_qvga_rgb565')
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:44:5: warning: excess elements in scalar initializer
   44 |     { REG_COM7, 0x04 },     //output RGB mode
      |     ^
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:44:5: note: (near initialization for 'ov7670_qvga_rgb565')
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:45:5: warning: braces around scalar initializer
   45 |     { REG_RGB444, 0x00 },    //RGB44 disable
      |     ^
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:45:5: note: (near initialization for 'ov7670_qvga_rgb565')
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera_reg.h:127:25: error: initialization of 'const struct regval_list *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
  127 | #define REG_RGB444      0x8C
      |                         ^~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:45:7: note: in expansion of macro 'REG_RGB444'
   45 |     { REG_RGB444, 0x00 },    //RGB44 disable
      |       ^~~~~~~~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera_reg.h:127:25: note: (near initialization for 'ov7670_qvga_rgb565')
  127 | #define REG_RGB444      0x8C
      |                         ^~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:45:7: note: in expansion of macro 'REG_RGB444'
   45 |     { REG_RGB444, 0x00 },    //RGB44 disable
      |       ^~~~~~~~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:45:19: warning: excess elements in scalar initializer
   45 |     { REG_RGB444, 0x00 },    //RGB44 disable
      |                   ^~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:45:19: note: (near initialization for 'ov7670_qvga_rgb565')
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:45:5: warning: excess elements in scalar initializer
   45 |     { REG_RGB444, 0x00 },    //RGB44 disable
      |     ^
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:45:5: note: (near initialization for 'ov7670_qvga_rgb565')
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:46:5: warning: braces around scalar initializer
   46 |     { REG_COM15, 0xD0 },    //output 00-FF, RGB565 match with RGB444 low
      |     ^
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:46:5: note: (near initialization for 'ov7670_qvga_rgb565')
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera_reg.h:68:25: error: initialization of 'const struct regval_list *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
   68 | #define REG_COM15       0x40
      |                         ^~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:46:7: note: in expansion of macro 'REG_COM15'
   46 |     { REG_COM15, 0xD0 },    //output 00-FF, RGB565 match with RGB444 low
      |       ^~~~~~~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera_reg.h:68:25: note: (near initialization for 'ov7670_qvga_rgb565')
   68 | #define REG_COM15       0x40
      |                         ^~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:46:7: note: in expansion of macro 'REG_COM15'
   46 |     { REG_COM15, 0xD0 },    //output 00-FF, RGB565 match with RGB444 low
      |       ^~~~~~~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:46:18: warning: excess elements in scalar initializer
   46 |     { REG_COM15, 0xD0 },    //output 00-FF, RGB565 match with RGB444 low
      |                  ^~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:46:18: note: (near initialization for 'ov7670_qvga_rgb565')
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:46:5: warning: excess elements in scalar initializer
   46 |     { REG_COM15, 0xD0 },    //output 00-FF, RGB565 match with RGB444 low
      |     ^
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:46:5: note: (near initialization for 'ov7670_qvga_rgb565')
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:47:5: warning: braces around scalar initializer
   47 |     { REG_COM1, 0x00 },    ///disable general control
      |     ^
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:47:5: note: (near initialization for 'ov7670_qvga_rgb565')
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera_reg.h:17:25: error: initialization of 'const struct regval_list *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
   17 | #define REG_COM1        0x04
      |                         ^~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/camera/camera.c:47:7: note: in expansion of macro 'REG_COM1'
   47 |     { REG_COM1, 0x00 },    ///disable general control
      |       ^~~~~~~~