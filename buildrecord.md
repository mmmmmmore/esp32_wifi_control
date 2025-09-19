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




/Users/maochun/.espressif/tools/xtensa-esp-elf/esp-15.1.0_20250607/xtensa-esp-elf/bin/../lib/gcc/xtensa-esp-elf/15.1.0/../../../../xtensa-esp-elf/bin/ld: esp-idf/ov7670gpio/libov7670gpio.a(ov7670_gpio.c.obj): in function `ov7670_init':
/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/ov7670gpio/ov7670_gpio.c:167: multiple definition of `ov7670_init'; esp-idf/ov7670/libov7670.a(ov7670.c.obj):/Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/components/ov7670/ov7670.c:60: first defined here
collect2: error: ld returned 1 exit status
ninja: build stopped: subcommand failed.
ninja failed with exit code 1, output of the command is in the /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/build/log/idf_py_stderr_output_14066 and /Users/maochun/esp32prj/Motor/motor_wifi/esp32_wifi_control/build/log/idf_py_stdout_output_14066