W (341) spi_flash: Detected size(16384k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
W (354) i2c: This driver is an old driver, please migrate your application code to adapt `driver/i2c_master.h`
I (363) sleep_gpio: Configure to isolate all GPIO pins in sleep state
I (370) sleep_gpio: Enable automatic switching of GPIO sleep configuration
I (377) main_task: Started on CPU0
I (387) main_task: Calling app_main()
ESP32S3 Boot Success...
I (407) pp: pp rom version: e7ae62f
I (407) net80211: net80211 rom version: e7ae62f
I (417) wifi:wifi driver task: 3fcec988, prio:23, stack:6656, core=0
I (417) wifi:wifi firmware version: df85326
I (417) wifi:wifi certification version: v7.0
I (417) wifi:config NVS flash: enabled
I (427) wifi:config nano formatting: disabled
I (427) wifi:Init data frame dynamic rx buffer num: 32
I (427) wifi:Init static rx mgmt buffer num: 5
I (437) wifi:Init management short buffer num: 32
I (437) wifi:Init dynamic tx buffer num: 32
I (447) wifi:Init static tx FG buffer num: 2
I (447) wifi:Init static rx buffer size: 1600
I (447) wifi:Init static rx buffer num: 10
I (457) wifi:Init dynamic rx buffer num: 32
I (457) wifi_init: rx ba win: 6
I (467) wifi_init: accept mbox: 6
I (467) wifi_init: tcpip mbox: 32
I (467) wifi_init: udp mbox: 6
I (467) wifi_init: tcp mbox: 6
I (477) wifi_init: tcp tx win: 5760
I (477) wifi_init: tcp rx win: 5760
I (477) wifi_init: tcp mss: 1440
I (487) wifi_init: WiFi IRAM OP enabled
I (487) wifi_init: WiFi RX IRAM OP enabled
I (497) phy_init: phy_version 701,f4f1da3a,Mar  3 2025,15:50:10
E (537) wifi:failed to post WiFi event=43 ret=259
I (537) wifi:mode : softAP (dc:b4:d9:04:7c:05)
I (537) wifi:Total power save buffer number: 16
I (537) wifi:Init max length of beacon: 752/752
I (537) wifi:Init max length of beacon: 752/752
E (547) wifi:failed to post WiFi event=12 ret=259
I (547) wifi_ap: WiFi SoftAP started. SSID: ESP32-SoftAP
I (607) OV7670: OV7670 initialized
系统初始化完成，等待客户端连接...
I (607) main_task: Returned from app_main()
I (24767) wifi:new:<1,1>, old:<1,1>, ap:<1,1>, sta:<255,255>, prof:1, snd_ch_cfg:0x0
I (24767) wifi:station: 5c:5f:67:ed:16:1a join, AID=1, bgn, 40U


 (330) spi_flash: Detected size(16384k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (343) sleep_gpio: Configure to isolate all GPIO pins in sleep state
I (349) sleep_gpio: Enable automatic switching of GPIO sleep configuration
I (356) main_task: Started on CPU0
I (376) main_task: Calling app_main()
I (396) pp: pp rom version: e7ae62f
I (396) net80211: net80211 rom version: e7ae62f
I (406) wifi:wifi driver task: 3fced478, prio:23, stack:6656, core=0
I (406) wifi:wifi firmware version: f3dbad7
I (406) wifi:wifi certification version: v7.0
I (406) wifi:config NVS flash: enabled
I (406) wifi:config nano formatting: disabled
I (416) wifi:Init data frame dynamic rx buffer num: 32
I (416) wifi:Init static rx mgmt buffer num: 5
I (426) wifi:Init management short buffer num: 32
I (426) wifi:Init dynamic tx buffer num: 32
I (436) wifi:Init static tx FG buffer num: 2
I (436) wifi:Init static rx buffer size: 1600
I (436) wifi:Init static rx buffer num: 10
I (446) wifi:Init dynamic rx buffer num: 32
I (446) wifi_init: rx ba win: 6
I (446) wifi_init: accept mbox: 6
I (456) wifi_init: tcpip mbox: 32
I (456) wifi_init: udp mbox: 6
I (456) wifi_init: tcp mbox: 6
I (466) wifi_init: tcp tx win: 5760
I (466) wifi_init: tcp rx win: 5760
I (466) wifi_init: tcp mss: 1440
I (476) wifi_init: WiFi IRAM OP enabled
I (476) wifi_init: WiFi RX IRAM OP enabled
I (486) phy_init: phy_version 701,f4f1da3a,Mar  3 2025,15:50:10
I (526) wifi:mode : softAP (dc:b4:d9:04:7c:05)
I (526) wifi:Total power save buffer number: 16
I (526) wifi:Init max length of beacon: 752/752
I (526) wifi:Init max length of beacon: 752/752
I (526) esp_netif_lwip: DHCP server started on interface WIFI_AP_DEF with IP: 192.168.4.1
I (536) main_task: Returned from app_main()
I (5596) wifi:new:<1,1>, old:<1,1>, ap:<1,1>, sta:<255,255>, prof:1, snd_ch_cfg:0x0
I (5596) wifi:station: 5c:5f:67:ed:16:1a join, AID=1, bgn, 40U
I (5636) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.2
I (5716) wifi:station: 5c:5f:67:ed:16:1a leave, AID = 1, reason = 1, bss_flags is 756835, bss:0x3fca5c98
I (5716) wifi:new:<1,0>, old:<1,1>, ap:<1,1>, sta:<255,255>, prof:1, snd_ch_cfg:0x0
I (11006) wifi:new:<1,1>, old:<1,0>, ap:<1,1>, sta:<255,255>, prof:1, snd_ch_cfg:0x0
I (11006) wifi:station: 5c:5f:67:ed:16:1a join, AID=1, bgn, 40U
I (11206) esp_netif_lwip: DHCP server assigned IP to a client, IP is: 192.168.4.2
I (14856) wifi:<ba-add>idx:2 (ifx:1, 5c:5f:67:ed:16:1a), tid:0, ssn:75, winSize:64
