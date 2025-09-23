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