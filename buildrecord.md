
/Users/maochun/esp32prj/Project_CAM/branch/esp32_wifi_control/components/camera/camera.c: In function 'camera_init':
/Users/maochun/esp32prj/Project_CAM/branch/esp32_wifi_control/components/camera/camera.c:17:31: error: implicit declaration of function 'heap_caps_malloc' [-Wimplicit-function-declaration]
   17 |     frame_buffer = (uint8_t *)heap_caps_malloc(CAMERA_FRAME_SIZE, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
      |                               ^~~~~~~~~~~~~~~~
/Users/maochun/esp32prj/Project_CAM/branch/esp32_wifi_control/components/camera/camera.c:17:67: error: 'MALLOC_CAP_SPIRAM' undeclared (first use in this function)
   17 |     frame_buffer = (uint8_t *)heap_caps_malloc(CAMERA_FRAME_SIZE, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
      |                                                                   ^~~~~~~~~~~~~~~~~
/Users/maochun/esp32prj/Project_CAM/branch/esp32_wifi_control/components/camera/camera.c:17:67: note: each undeclared identifier is reported only once for each function it appears in
/Users/maochun/esp32prj/Project_CAM/branch/esp32_wifi_control/components/camera/camera.c:17:87: error: 'MALLOC_CAP_8BIT' undeclared (first use in this function)
   17 |     frame_buffer = (uint8_t *)heap_caps_malloc(CAMERA_FRAME_SIZE, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
      |                                                                                       ^~~~~~~~~~~~~~~
[1/1] cd /Users/maochun/esp32prj/Project_CAM/branch/esp3...ranch/esp32_wifi_control/build/bootloader/bootloader.bin
Bootloader binary size 0x5880 bytes. 0x2780 bytes (31%) free.
[4/13] Building C object esp-idf/common_gpio/CMakeFiles/__idf_common_gpio.dir/common_gpio.c.obj