#include "common_gpio.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "driver/i2c.h"
#include "esp_err.h"



const motor_gpio_t motor_fl = {
    .dir_gpio = GPIO_MOTOR1_AIN2,
    .pwm_gpio = GPIO_MOTOR1_PWMA,
    .pwm_channel = LEDC_CHANNEL_MOTOR1_A
};

const motor_gpio_t motor_fr = {
    .dir_gpio = GPIO_MOTOR1_BIN2,
    .pwm_gpio = GPIO_MOTOR1_PWMB,
    .pwm_channel = LEDC_CHANNEL_MOTOR1_B
};

const motor_gpio_t motor_rl = {
    .dir_gpio = GPIO_MOTOR2_AIN2,
    .pwm_gpio = GPIO_MOTOR2_PWMA,
    .pwm_channel = LEDC_CHANNEL_MOTOR2_A
};

const motor_gpio_t motor_rr = {
    .dir_gpio = GPIO_MOTOR2_BIN2,
    .pwm_gpio = GPIO_MOTOR2_PWMB,
    .pwm_channel = LEDC_CHANNEL_MOTOR2_B
};


void common_gpio_init(void) {
    gpio_config_t io_conf = {
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };

    // 所有输出 GPIO 列表
    gpio_num_t gpio_outputs[] = {
        GPIO_SCL, GPIO_SDA,
        GPIO_D0, GPIO_D1, GPIO_D2, GPIO_D3, GPIO_D4, GPIO_D5, GPIO_D6, GPIO_D7,
        GPIO_VSYNC, GPIO_RCLK, GPIO_OE, GPIO_WRST, GPIO_RRST, GPIO_WEN,
        GPIO_MOTOR1_AIN1, GPIO_MOTOR1_AIN2, GPIO_MOTOR1_BIN1, GPIO_MOTOR1_BIN2,
        GPIO_MOTOR1_PWMA, GPIO_MOTOR1_PWMB,
        GPIO_MOTOR2_AIN1, GPIO_MOTOR2_AIN2, GPIO_MOTOR2_BIN1, GPIO_MOTOR2_BIN2,
        GPIO_MOTOR2_PWMA, GPIO_MOTOR2_PWMB,
        GPIO_MOTOR_STBY,
        GPIO_LED_STATUS, GPIO_WEBSERVER_CTRL
    };

    io_conf.pin_bit_mask = 0;
    for (int i = 0; i < sizeof(gpio_outputs)/sizeof(gpio_outputs[0]); i++) {
        io_conf.pin_bit_mask |= (1ULL << gpio_outputs[i]);
    }

    gpio_config(&io_conf);
}

void ledc_init(void) {
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .timer_num        = LEDC_TIMER,
        .duty_resolution  = LEDC_DUTY_RES,
        .freq_hz          = LEDC_FREQUENCY,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channels[] = {
        {
            .channel    = LEDC_CHANNEL_MOTOR1_A,
            .duty       = 0,
            .gpio_num   = GPIO_MOTOR1_PWMA,
            .speed_mode = LEDC_MODE,
            .hpoint     = 0,
            .timer_sel  = LEDC_TIMER
        },
        {
            .channel    = LEDC_CHANNEL_MOTOR1_B,
            .duty       = 0,
            .gpio_num   = GPIO_MOTOR1_PWMB,
            .speed_mode = LEDC_MODE,
            .hpoint     = 0,
            .timer_sel  = LEDC_TIMER
        },
        {
            .channel    = LEDC_CHANNEL_MOTOR2_A,
            .duty       = 0,
            .gpio_num   = GPIO_MOTOR2_PWMA,
            .speed_mode = LEDC_MODE,
            .hpoint     = 0,
            .timer_sel  = LEDC_TIMER
        },
        {
            .channel    = LEDC_CHANNEL_MOTOR2_B,
            .duty       = 0,
            .gpio_num   = GPIO_MOTOR2_PWMB,
            .speed_mode = LEDC_MODE,
            .hpoint     = 0,
            .timer_sel  = LEDC_TIMER
        }
    };

    for (int i = 0; i < sizeof(ledc_channels)/sizeof(ledc_channels[0]); i++) {
        ledc_channel_config(&ledc_channels[i]);
    }
}

void i2c_master_init(void) {
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = GPIO_SDA,
        .scl_io_num = GPIO_SCL,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ
    };
    i2c_param_config(I2C_MASTER_NUM, &conf);
    i2c_driver_install(I2C_MASTER_NUM, conf.mode,
                       I2C_MASTER_RX_BUF_DISABLE,
                       I2C_MASTER_TX_BUF_DISABLE, 0);
}
