2025-9-28:
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