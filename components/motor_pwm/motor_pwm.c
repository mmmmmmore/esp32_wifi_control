#include "pwm.h"
#include "esp_log.h"

static const char *TAG = "pwm";

// 电机 GPIO 配置（根据实际连接修改）
static motor_gpio_config_t motor_config[MOTOR_COUNT] = {
    { .in1_gpio = GPIO_NUM_2,  .in2_gpio = GPIO_NUM_4,  .pwm_gpio = GPIO_NUM_5,  .pwm_channel = LEDC_CHANNEL_0 },
    { .in1_gpio = GPIO_NUM_18, .in2_gpio = GPIO_NUM_19, .pwm_gpio = GPIO_NUM_21, .pwm_channel = LEDC_CHANNEL_1 },
    { .in1_gpio = GPIO_NUM_22, .in2_gpio = GPIO_NUM_23, .pwm_gpio = GPIO_NUM_25, .pwm_channel = LEDC_CHANNEL_2 },
    { .in1_gpio = GPIO_NUM_26, .in2_gpio = GPIO_NUM_27, .pwm_gpio = GPIO_NUM_32, .pwm_channel = LEDC_CHANNEL_3 },
};

esp_err_t pwm_init_all_motors(void) {
    ledc_timer_config_t timer = {
        .duty_resolution = LEDC_TIMER_8_BIT,
        .freq_hz = 1000,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .clk_cfg = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&timer));

    for (int i = 0; i < MOTOR_COUNT; i++) {
        gpio_set_direction(motor_config[i].in1_gpio, GPIO_MODE_OUTPUT);
        gpio_set_direction(motor_config[i].in2_gpio, GPIO_MODE_OUTPUT);

        ledc_channel_config_t channel = {
            .channel    = motor_config[i].pwm_channel,
            .duty       = 0,
            .gpio_num   = motor_config[i].pwm_gpio,
            .speed_mode = LEDC_LOW_SPEED_MODE,
            .hpoint     = 0,
            .timer_sel  = LEDC_TIMER_0
        };
        ESP_ERROR_CHECK(ledc_channel_config(&channel));
    }

    ESP_LOGI(TAG, "PWM motors initialized");
    return ESP_OK;
}

void pwm_set_motor_direction(int motor_id, bool forward) {
    if (motor_id < 1 || motor_id > MOTOR_COUNT) return;
    motor_gpio_config_t *motor = &motor_config[motor_id - 1];

    gpio_set_level(motor->in1_gpio, forward ? 1 : 0);
    gpio_set_level(motor->in2_gpio, forward ? 0 : 1);
}

void pwm_set_motor_speed(int motor_id, int speed_percent) {
    if (motor_id < 1 || motor_id > MOTOR_COUNT) return;
    if (speed_percent < 0) speed_percent = 0;
    if (speed_percent > 100) speed_percent = 100;

    uint32_t duty = (speed_percent * 255) / 100;
    ledc_set_duty(LEDC_LOW_SPEED_MODE, motor_config[motor_id - 1].pwm_channel, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, motor_config[motor_id - 1].pwm_channel);
}

void pwm_stop_all_motors(void) {
    for (int i = 1; i <= MOTOR_COUNT; i++) {
        pwm_set_motor_speed(i, 0);
        gpio_set_level(motor_config[i - 1].in1_gpio, 0);
        gpio_set_level(motor_config[i - 1].in2_gpio, 0);
    }
}
