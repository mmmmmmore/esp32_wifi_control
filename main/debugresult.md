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