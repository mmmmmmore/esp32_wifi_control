/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/protocol/sccb/sccb.c:12:5: error: implicit declaration of function 'ets_delay_us'; did you mean 'esp_rom_delay_us'? [-Wimplicit-function-declaration]
   12 |     ets_delay_us(SCCB_DELAY_US);
      |     ^~~~~~~~~~~~
      |     esp_rom_delay_us
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/protocol/sccb/sccb.c: At top level:
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/protocol/sccb/sccb.c:54:1: error: expected '=', ',', ';', 'asm' or '__attribute__' at end of input
   54 | static void sccb_stop
      | ^~~~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/protocol/sccb/sccb.c:44:13: warning: 'sccb_start' defined but not used [-Wunused-function]
   44 | static void sccb_start() {
      |             ^~~~~~~~~~
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/protocol/sccb/sccb.c:23:12: warning: 'sccb_get_sda' defined but not used [-Wunused-function]
   23 | static int sccb_get_sda() {
      |            ^~~~~~~~~~~~
[3/31] Building C object esp-idf/ov7670/CMakeFiles/__idf_ov7670.dir/ov7670.c.obj