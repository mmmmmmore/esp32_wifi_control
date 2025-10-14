#include "common_gpio.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "driver/i2c.h"
#include "esp_err.h"
#include "esp_log.h"

static const char *TAG = "common_gpio";

// 初始化 OV7670 摄像头相关 GPIO
void ov7670_gpio_init(void) {
    gpio_config_t io_conf = {
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
        .pin_bit_mask = 0
    };

    gpio_num_t ov7670_gpios[] = {
        GPIO_SCL, GPIO_SDA,
        GPIO_D0, GPIO_D1, GPIO_D2, GPIO_D3, GPIO_D4, GPIO_D5, GPIO_D6, GPIO_D7,
        GPIO_VSYNC, GPIO_RCLK, GPIO_OE, GPIO_WRST, GPIO_RRST, GPIO_WEN
    };

    for (int i = 0; i < sizeof(ov7670_gpios)/sizeof(ov7670_gpios[0]); i++) {
        if (ov7670_gpios[i] >= GPIO_NUM_0 && ov7670_gpios[i] < GPIO_NUM_MAX) {
            io_conf.pin_bit_mask |= (1ULL << ov7670_gpios[i]);
        } else {
            ESP_LOGW(TAG, "Invalid OV7670 GPIO: %d", ov7670_gpios[i]);
        }
    }

    ESP_ERROR_CHECK(gpio_config(&io_conf));
    ESP_LOGI(TAG, "OV7670 GPIOs initialized");
}

// 初始化电机相关 GPIO（包括 PWM 和方向控制）
void motor_gpio_init(void) {
    gpio_config_t io_conf = {
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
        .pin_bit_mask = 0
    };

    gpio_num_t motor_gpios[] = {
        GPIO_MOTOR1_AIN1, GPIO_MOTOR1_AIN2, GPIO_MOTOR1_BIN1, GPIO_MOTOR1_BIN2,
        GPIO_MOTOR1_PWMA, GPIO_MOTOR1_PWMB,
        GPIO_MOTOR2_AIN1, GPIO_MOTOR2_AIN2, GPIO_MOTOR2_BIN1, GPIO_MOTOR2_BIN2,
        GPIO_MOTOR2_PWMA, GPIO_MOTOR2_PWMB,
        GPIO_MOTOR_STBY
    };

    for (int i = 0; i < sizeof(motor_gpios)/sizeof(motor_gpios[0]); i++) {
        if (motor_gpios[i] >= GPIO_NUM_0 && motor_gpios[i] < GPIO_NUM_MAX) {
            io_conf.pin_bit_mask |= (1ULL << motor_gpios[i]);
        } else {
            ESP_LOGW(TAG, "Invalid Motor GPIO: %d", motor_gpios[i]);
        }
    }

    ESP_ERROR_CHECK(gpio_config(&io_conf));
    ESP_LOGI(TAG, "Motor GPIOs initialized");
}

// 初始化其他功能 GPIO
void misc_gpio_init(void) {
    gpio_config_t io_conf = {
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
        .pin_bit_mask = 0
    };

    gpio_num_t misc_gpios[] = {
        GPIO_LED_STATUS,
        GPIO_WEBSERVER_CTRL
    };

    for (int i = 0; i < sizeof(misc_gpios)/sizeof(misc_gpios[0]); i++) {
        if (misc_gpios[i] >= GPIO_NUM_0 && misc_gpios[i] < GPIO_NUM_MAX) {
            io_conf.pin_bit_mask |= (1ULL << misc_gpios[i]);
        } else {
            ESP_LOGW(TAG, "Invalid Misc GPIO: %d", misc_gpios[i]);
        }
    }

    ESP_ERROR_CHECK(gpio_config(&io_conf));
    ESP_LOGI(TAG, "Misc GPIOs initialized");
}

// 总入口函数
void common_gpio_init(void) {
    ESP_LOGI(TAG, "Starting GPIO initialization...");
    ov7670_gpio_init();
    motor_gpio_init();
    misc_gpio_init();
    ESP_LOGI(TAG, "All GPIOs initialized");
}

//
//void common_gpio_init(void) {
//    gpio_config_t io_conf = {
//        .mode = GPIO_MODE_OUTPUT,
//        .pull_up_en = GPIO_PULLUP_DISABLE,
//        .pull_down_en = GPIO_PULLDOWN_DISABLE,
//        .intr_type = GPIO_INTR_DISABLE
//    };
//
//    // 所有输出 GPIO 列表
//    gpio_num_t gpio_outputs[] = {
//        GPIO_SCL, GPIO_SDA,
//        GPIO_D0, GPIO_D1, GPIO_D2, GPIO_D3, GPIO_D4, GPIO_D5, GPIO_D6, GPIO_D7,
//        GPIO_VSYNC, GPIO_RCLK, GPIO_OE, GPIO_WRST, GPIO_RRST, GPIO_WEN,
//        GPIO_MOTOR1_AIN1, GPIO_MOTOR1_AIN2, GPIO_MOTOR1_BIN1, GPIO_MOTOR1_BIN2,
//        GPIO_MOTOR1_PWMA, GPIO_MOTOR1_PWMB,
//        GPIO_MOTOR2_AIN1, GPIO_MOTOR2_AIN2, GPIO_MOTOR2_BIN1, GPIO_MOTOR2_BIN2,
//        GPIO_MOTOR2_PWMA, GPIO_MOTOR2_PWMB,
//        GPIO_MOTOR_STBY,
//        GPIO_LED_STATUS, GPIO_WEBSERVER_CTRL
//    };
//
//    io_conf.pin_bit_mask = 0;
//    for (int i = 0; i < sizeof(gpio_outputs)/sizeof(gpio_outputs[0]); i++) {
//        io_conf.pin_bit_mask |= (1ULL << gpio_outputs[i]);
//    }
//
//    gpio_config(&io_conf);
//}

//new ledc print err:
void ledc_init(void) {
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .timer_num        = LEDC_TIMER,
        .duty_resolution  = LEDC_DUTY_RES,
        .freq_hz          = LEDC_FREQUENCY,
        .clk_cfg          = LEDC_AUTO_CLK
    };

    esp_err_t err = ledc_timer_config(&ledc_timer);
    if (err != ESP_OK) {
        ESP_LOGE("LEDC", "Timer config failed: %s", esp_err_to_name(err));
        return;
    }

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
        err = ledc_channel_config(&ledc_channels[i]);
        if (err != ESP_OK) {
            ESP_LOGE("LEDC", "Channel %d config failed: %s", i, esp_err_to_name(err));
        }
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



const motor_gpio_t motor_fl = {
    .dir_gpio = GPIO_MOTOR1_AIN1,
    .pwm_gpio = GPIO_MOTOR1_PWMA,
    .pwm_channel = LEDC_CHANNEL_MOTOR1_A
};

const motor_gpio_t motor_fr = {
    .dir_gpio = GPIO_MOTOR1_AIN2,
    .pwm_gpio = GPIO_MOTOR1_PWMB,
    .pwm_channel = LEDC_CHANNEL_MOTOR1_B
};

const motor_gpio_t motor_rl = {
    .dir_gpio = GPIO_MOTOR2_AIN1,
    .pwm_gpio = GPIO_MOTOR2_PWMA,
    .pwm_channel = LEDC_CHANNEL_MOTOR2_A
};

const motor_gpio_t motor_rr = {
    .dir_gpio = GPIO_MOTOR2_AIN2,
    .pwm_gpio = GPIO_MOTOR2_PWMB,
    .pwm_channel = LEDC_CHANNEL_MOTOR2_B
};

