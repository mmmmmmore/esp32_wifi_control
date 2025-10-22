#include "motor_handler.h"
#include "common_gpio.h"
#include "driver/ledc.h"
#include "esp_log.h"
#include <math.h>

static const char *TAG = "motor_handler";

// 假设 PWM 范围为 0~255
#define MAX_PWM 255

// 将速度值映射到 PWM
static int map_speed_to_pwm(float speed) {
    int pwm = (int)(fabs(speed) * MAX_PWM);
    if (pwm > MAX_PWM) pwm = MAX_PWM;
    return pwm;
}

// 设置单个电机的方向和 PWM  for DRV8833
static void set_motor(const motor_gpio_t *motor, float speed) {
    int pwm = map_speed_to_pwm(speed);

    if (speed >= 0) {
        // 正转：PWM 输出到 IN1，IN2 拉低
        gpio_set_level(motor->in2_gpio, 0);
        ledc_set_duty(LEDC_LOW_SPEED_MODE, motor->pwm_channel, pwm); // PWM 输出到 IN1
        ledc_update_duty(LEDC_LOW_SPEED_MODE, motor->pwm_channel);
        ESP_LOGI(TAG, "DRV8833 正转: IN1(PWM)=GPIO%d, IN2=GPIO%d, pwm=%d",
                 motor->in1_gpio, motor->in2_gpio, pwm);
    } else {
        // 反转：PWM 输出到 IN2，IN1 拉低
        gpio_set_level(motor->in1_gpio, 0);
        ledc_set_duty(LEDC_LOW_SPEED_MODE, motor->pwm_channel, pwm); // PWM 输出到 IN2
        ledc_update_duty(LEDC_LOW_SPEED_MODE, motor->pwm_channel);
        ESP_LOGI(TAG, "DRV8833 反转: IN1=GPIO%d, IN2(PWM)=GPIO%d, pwm=%d",
                 motor->in1_gpio, motor->in2_gpio, pwm);
    }
}


esp_err_t motor_handler_update(int angle_deg, int distance_percent) {
    ESP_LOGI(TAG, "Motor update: angle=%d°, distance=%d%%", angle_deg, distance_percent);

    // 将角度转换为弧度
    float angle_rad = angle_deg * M_PI / 180.0f;

    // 计算 X/Y 分量
    float Vx = cosf(angle_rad) * (distance_percent / 100.0f);
    float Vy = sinf(angle_rad) * (distance_percent / 100.0f);
    float omega = 0; // 暂不使用旋转

    // 计算四个轮子的速度
    float FL = Vy + Vx + omega;
    float FR = Vy - Vx - omega;
    float RL = Vy - Vx + omega;
    float RR = Vy + Vx - omega;


    ESP_LOGI(TAG, "wheel speeds: FL=%.2f, FR=%.2f, RL=%.2f, RR=%.2f",FL,FR,RL,RR);


    // 设置电机（假设 GPIO 定义在 common_gpio.h 中）
    set_motor(&motor_fl, FL);
    set_motor(&motor_fr, FR);
    set_motor(&motor_rl, RL);
    set_motor(&motor_rr, RR);

    return ESP_OK;
}


