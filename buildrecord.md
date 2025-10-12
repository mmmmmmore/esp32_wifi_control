
2025-10-12

build log:

/Users/maochun/esp32prj/Project_CAM/branch/esp32_wifi_control/protocol/webserver/webserver.c: In function 'start_webserver':
/Users/maochun/esp32prj/Project_CAM/branch/esp32_wifi_control/protocol/webserver/webserver.c:24:9: error: implicit declaration of function 'webserver_init' [-Wimplicit-function-declaration]
   24 |         webserver_init();
      |         ^~~~~~~~~~~~~~
In file included from /Users/maochun/esp32prj/esp-idf/components/esp_hw_support/include/esp_intr_alloc.h:12,
                 from /Users/maochun/esp32prj/esp-idf/components/esp_hw_support/include/esp_cpu.h:21,
                 from /Users/maochun/esp32prj/esp-idf/components/esp_hw_support/include/spinlock.h:11,
                 from /Users/maochun/esp32prj/esp-idf/components/freertos/FreeRTOS-Kernel/portable/xtensa/include/freertos/portmacro.h:49,
                 from /Users/maochun/esp32prj/esp-idf/components/freertos/FreeRTOS-Kernel/include/freertos/portable.h:57,
                 from /Users/maochun/esp32prj/esp-idf/components/freertos/FreeRTOS-Kernel/include/freertos/FreeRTOS.h:69,
                 from /Users/maochun/esp32prj/esp-idf/components/esp_http_server/include/esp_http_server.h:12,
                 from /Users/maochun/esp32prj/Project_CAM/branch/esp32_wifi_control/protocol/webserver/webserver.h:5,
                 from /Users/maochun/esp32prj/Project_CAM/branch/esp32_wifi_control/protocol/webserver/webserver.c:1:
/Users/maochun/esp32prj/Project_CAM/branch/esp32_wifi_control/protocol/webserver/webserver.c: In function 'webserver_init':
/Users/maochun/esp32prj/Project_CAM/branch/esp32_wifi_control/protocol/webserver/webserver.c:36:21: error: implicit declaration of function 'webserver_base_register' [-Wimplicit-function-declaration]
   36 |     ESP_ERROR_CHECK(webserver_base_register(server));
      |                     ^~~~~~~~~~~~~~~~~~~~~~~
/Users/maochun/esp32prj/esp-idf/components/esp_common/include/esp_err.h:116:30: note: in definition of macro 'ESP_ERROR_CHECK'
  116 |         esp_err_t err_rc_ = (x);                                        \
      |                              ^
/Users/maochun/esp32prj/Project_CAM/branch/esp32_wifi_control/protocol/webserver/webserver.c:39:21: error: implicit declaration of function 'webserver_camera_register' [-Wimplicit-function-declaration]
   39 |     ESP_ERROR_CHECK(webserver_camera_register(server));
      |                     ^~~~~~~~~~~~~~~~~~~~~~~~~
/Users/maochun/esp32prj/esp-idf/components/esp_common/include/esp_err.h:116:30: note: in definition of macro 'ESP_ERROR_CHECK'
  116 |         esp_err_t err_rc_ = (x);                                        \
      |                              ^
/Users/maochun/esp32prj/Project_CAM/branch/esp32_wifi_control/protocol/webserver/webserver.c:42:21: error: implicit declaration of function 'webserver_motor_register' [-Wimplicit-function-declaration]
   42 |     ESP_ERROR_CHECK(webserver_motor_register(server));
      |                     ^~~~~~~~~~~~~~~~~~~~~~~~
/Users/maochun/esp32prj/esp-idf/components/esp_common/include/esp_err.h:116:30: note: in definition of macro 'ESP_ERROR_CHECK'
  116 |         esp_err_t err_rc_ = (x);                                        \
      |                              ^