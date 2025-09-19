#include "sccb.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static gpio_num_t sccb_sda;
static gpio_num_t sccb_scl;

#define SCCB_DELAY_US 5  // SCCB 时序延迟，单位微秒

static void sccb_delay() {
    ets_delay_us(SCCB_DELAY_US);
}

static void sccb_set_sda(int level) {
    gpio_set_level(sccb_sda, level);
}

static void sccb_set_scl(int level) {
    gpio_set_level(sccb_scl, level);
}

static int sccb_get_sda() {
    return gpio_get_level(sccb_sda);
}

void sccb_init(gpio_num_t sda, gpio_num_t scl) {
    sccb_sda = sda;
    sccb_scl = scl;

    gpio_config_t conf = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = (1ULL << sda) | (1ULL << scl),
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&conf);

    sccb_set_sda(1);
    sccb_set_scl(1);
}

static void sccb_start() {
    sccb_set_sda(1);
    sccb_set_scl(1);
    sccb_delay();
    sccb_set_sda(0);
    sccb_delay();
    sccb_set_scl(0);
    sccb_delay();
}

static void sccb_stop