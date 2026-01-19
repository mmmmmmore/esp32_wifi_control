#include "motor_handler.h"
#include "common_gpio.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "esp_log.h"
#include <math.h>
#include <string.h>

static const char *TAG = "motor_handler";

// DRV8833 motor configuration
typedef struct {
    gpio_num_t in1_gpio;      // DRV8833 IN1 pin
    gpio_num_t in2_gpio;      // DRV8833 IN2 pin
    ledc_channel_t pwm_ch1;   // PWM channel for IN1
    ledc_channel_t pwm_ch2;   // PWM channel for IN2
} drv8833_motor_t;

// Motor configuration array based on pin definitions
static const drv8833_motor_t motors[MOTOR_COUNT] = {
        // Motor 1: GPIO19 (AIN1), GPIO20 (AIN2) - DRV8833-Board_1
        { .in1_gpio = GPIO_MOTOR1_IN1, .in2_gpio = GPIO_MOTOR1_IN2, 
            .pwm_ch1 = LEDC_CHANNEL_0, .pwm_ch2 = LEDC_CHANNEL_1 },
    
        // Motor 2: GPIO14 (BIN1), GPIO21 (BIN2) - DRV8833-Board_1
        { .in1_gpio = GPIO_MOTOR2_IN1, .in2_gpio = GPIO_MOTOR2_IN2, 
            .pwm_ch1 = LEDC_CHANNEL_2, .pwm_ch2 = LEDC_CHANNEL_3 },
    
        // Motor 3: GPIO1 (AIN1), GPIO2 (AIN2) - DRV8833-Board_2
        { .in1_gpio = GPIO_MOTOR3_IN1, .in2_gpio = GPIO_MOTOR3_IN2, 
            .pwm_ch1 = LEDC_CHANNEL_4, .pwm_ch2 = LEDC_CHANNEL_5 },
    
        // Motor 4: GPIO38 (BIN1), GPIO39 (BIN2) - DRV8833-Board_2
        { .in1_gpio = GPIO_MOTOR4_IN1, .in2_gpio = GPIO_MOTOR4_IN2, 
            .pwm_ch1 = LEDC_CHANNEL_6, .pwm_ch2 = LEDC_CHANNEL_7 }
};

// Initialize PWM timer
static esp_err_t init_pwm_timer(void) {
    ledc_timer_config_t timer_conf = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_8_BIT,  // 8-bit resolution (0-255)
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 1000,  // 1 kHz PWM frequency
        .clk_cfg = LEDC_AUTO_CLK
    };
    
    esp_err_t ret = ledc_timer_config(&timer_conf);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to configure PWM timer: %s", esp_err_to_name(ret));
        return ret;
    }
    
    ESP_LOGI(TAG, "PWM timer configured: 1kHz, 8-bit resolution");
    return ESP_OK;
}

// Initialize single motor PWM channels
static esp_err_t init_motor_pwm(const drv8833_motor_t *motor) {
    // Configure IN1 PWM channel
    ledc_channel_config_t ch1_conf = {
        .gpio_num = motor->in1_gpio,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = motor->pwm_ch1,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
        .hpoint = 0
    };
    
    esp_err_t ret = ledc_channel_config(&ch1_conf);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to configure IN1 PWM channel (GPIO%d): %s", 
                 motor->in1_gpio, esp_err_to_name(ret));
        return ret;
    }
    
    // Configure IN2 PWM channel
    ledc_channel_config_t ch2_conf = {
        .gpio_num = motor->in2_gpio,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = motor->pwm_ch2,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
        .hpoint = 0
    };
    
    ret = ledc_channel_config(&ch2_conf);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to configure IN2 PWM channel (GPIO%d): %s", 
                 motor->in2_gpio, esp_err_to_name(ret));
        return ret;
    }
    
    return ESP_OK;
}

esp_err_t motor_handler_init(void) {
    ESP_LOGI(TAG, "Initializing motor handler for DRV8833 drivers");
    
    // Initialize STBY pin
    gpio_config_t stby_conf = {
        .pin_bit_mask = (1ULL << GPIO_MOTOR_STBY),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    
    esp_err_t ret = gpio_config(&stby_conf);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to configure STBY pin (GPIO%d): %s", 
                 GPIO_MOTOR_STBY, esp_err_to_name(ret));
        return ret;
    }
    
    // Enable drivers (STBY HIGH)
    gpio_set_level(GPIO_MOTOR_STBY, 1);
    ESP_LOGI(TAG, "DRV8833 drivers enabled (STBY=HIGH on GPIO%d)", GPIO_MOTOR_STBY);
    
    // Initialize PWM timer
    ret = init_pwm_timer();
    if (ret != ESP_OK) {
        return ret;
    }
    
    // Initialize all motors
    for (int i = 0; i < MOTOR_COUNT; i++) {
        ret = init_motor_pwm(&motors[i]);
        if (ret != ESP_OK) {
            ESP_LOGE(TAG, "Failed to initialize motor %d", i + 1);
            return ret;
        }
        ESP_LOGI(TAG, "Motor %d initialized: IN1=GPIO%d, IN2=GPIO%d", 
                 i + 1, motors[i].in1_gpio, motors[i].in2_gpio);
    }
    
    // Stop all motors initially
    motor_handler_stop_all();
    
    ESP_LOGI(TAG, "Motor handler initialization complete");
    return ESP_OK;
}

esp_err_t motor_handler_set_mode(int motor_id, motor_mode_t mode, int speed_percent) {
    if (motor_id < 1 || motor_id > MOTOR_COUNT) {
        ESP_LOGE(TAG, "Invalid motor_id: %d", motor_id);
        return ESP_FAIL;
    }
    
    // Clamp speed to 0-100
    if (speed_percent < 0) speed_percent = 0;
    if (speed_percent > 100) speed_percent = 100;
    
    const drv8833_motor_t *motor = &motors[motor_id - 1];
    uint32_t duty = (speed_percent * 255) / 100;  // Convert to 8-bit PWM duty
    
    switch (mode) {
        case MOTOR_STOP_COAST:
            // IN1=0, IN2=0
            ledc_set_duty(LEDC_LOW_SPEED_MODE, motor->pwm_ch1, 0);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, motor->pwm_ch1);
            ledc_set_duty(LEDC_LOW_SPEED_MODE, motor->pwm_ch2, 0);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, motor->pwm_ch2);
            ESP_LOGD(TAG, "Motor %d: COAST", motor_id);
            break;
            
        case MOTOR_FORWARD:
            // IN1=PWM, IN2=0
            ledc_set_duty(LEDC_LOW_SPEED_MODE, motor->pwm_ch1, duty);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, motor->pwm_ch1);
            ledc_set_duty(LEDC_LOW_SPEED_MODE, motor->pwm_ch2, 0);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, motor->pwm_ch2);
            ESP_LOGD(TAG, "Motor %d: FORWARD speed=%d%% (duty=%ld)", motor_id, speed_percent, duty);
            break;
            
        case MOTOR_REVERSE:
            // IN1=0, IN2=PWM
            ledc_set_duty(LEDC_LOW_SPEED_MODE, motor->pwm_ch1, 0);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, motor->pwm_ch1);
            ledc_set_duty(LEDC_LOW_SPEED_MODE, motor->pwm_ch2, duty);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, motor->pwm_ch2);
            ESP_LOGD(TAG, "Motor %d: REVERSE speed=%d%% (duty=%ld)", motor_id, speed_percent, duty);
            break;
            
        case MOTOR_BRAKE:
            // IN1=1, IN2=1
            ledc_set_duty(LEDC_LOW_SPEED_MODE, motor->pwm_ch1, 255);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, motor->pwm_ch1);
            ledc_set_duty(LEDC_LOW_SPEED_MODE, motor->pwm_ch2, 255);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, motor->pwm_ch2);
            ESP_LOGD(TAG, "Motor %d: BRAKE", motor_id);
            break;
            
        default:
            ESP_LOGE(TAG, "Invalid motor mode: %d", mode);
            return ESP_FAIL;
    }
    
    return ESP_OK;
}

esp_err_t motor_handler_set_motor(int motor_id, int speed) {
    if (motor_id < 1 || motor_id > MOTOR_COUNT) {
        ESP_LOGE(TAG, "Invalid motor_id: %d", motor_id);
        return ESP_FAIL;
    }
    
    // Clamp speed to -100 to +100
    if (speed < -100) speed = -100;
    if (speed > 100) speed = 100;
    
    if (speed == 0) {
        return motor_handler_set_mode(motor_id, MOTOR_STOP_COAST, 0);
    } else if (speed > 0) {
        return motor_handler_set_mode(motor_id, MOTOR_FORWARD, speed);
    } else {
        return motor_handler_set_mode(motor_id, MOTOR_REVERSE, -speed);
    }
}

esp_err_t motor_handler_stop_all(void) {
    ESP_LOGI(TAG, "Stopping all motors (coast)");
    for (int i = 1; i <= MOTOR_COUNT; i++) {
        motor_handler_set_mode(i, MOTOR_STOP_COAST, 0);
    }
    return ESP_OK;
}

esp_err_t motor_handler_brake_all(void) {
    ESP_LOGI(TAG, "Braking all motors");
    for (int i = 1; i <= MOTOR_COUNT; i++) {
        motor_handler_set_mode(i, MOTOR_BRAKE, 0);
    }
    return ESP_OK;
}

esp_err_t motor_handler_enable(bool enable) {
    gpio_set_level(GPIO_MOTOR_STBY, enable ? 1 : 0);
    ESP_LOGI(TAG, "Motor drivers %s", enable ? "enabled" : "disabled (sleep)");
    return ESP_OK;
}

esp_err_t motor_handler_update(int angle_deg, int distance_percent) {
    ESP_LOGI(TAG, "Joystick update: angle=%d°, distance=%d%%", angle_deg, distance_percent);
    
    // Clamp inputs
    if (distance_percent < 0) distance_percent = 0;
    if (distance_percent > 100) distance_percent = 100;
    
    // Handle stop condition
    if (distance_percent == 0) {
        return motor_handler_stop_all();
    }
    
    // Normalize angle to 0-359
    while (angle_deg < 0) angle_deg += 360;
    while (angle_deg >= 360) angle_deg -= 360;
    
    // Convert to radians
    float angle_rad = angle_deg * M_PI / 180.0f;
    
    // Calculate velocity components (normalized -1.0 to +1.0)
    float speed_factor = distance_percent / 100.0f;
    float Vx = cosf(angle_rad) * speed_factor;  // X component (left/right)
    float Vy = sinf(angle_rad) * speed_factor;  // Y component (forward/back)
    
    // Mecanum wheel drive kinematics
    // Assuming motor layout:
    //   Motor1 (FL)    Motor2 (FR)
    //   Motor3 (RL)    Motor4 (RR)
    float omega = 0.0f;  // Rotation component (can add later for spinning)
    
    float motor1_speed = Vy + Vx + omega;  // Front Left
    float motor2_speed = Vy - Vx - omega;  // Front Right
    float motor3_speed = Vy - Vx + omega;  // Rear Left
    float motor4_speed = Vy + Vx - omega;  // Rear Right
    
    ESP_LOGI(TAG, "Motor speeds: M1=%.2f, M2=%.2f, M3=%.2f, M4=%.2f", 
             motor1_speed, motor2_speed, motor3_speed, motor4_speed);
    
    // Convert normalized speeds to percentage (-100 to +100)
    int m1_speed = (int)(motor1_speed * 100);
    int m2_speed = (int)(motor2_speed * 100);
    int m3_speed = (int)(motor3_speed * 100);
    int m4_speed = (int)(motor4_speed * 100);
    
    // Apply to motors
    motor_handler_set_motor(MOTOR_1, m1_speed);
    motor_handler_set_motor(MOTOR_2, m2_speed);
    motor_handler_set_motor(MOTOR_3, m3_speed);
    motor_handler_set_motor(MOTOR_4, m4_speed);
    
    return ESP_OK;
}

esp_err_t motor_handler_rotate(bool clockwise, int degrees) {
    // Clamp degrees to 0-180
    if (degrees < 0) degrees = 0;
    if (degrees > 180) degrees = 180;

    // If no rotation requested, stop all motors
    if (degrees == 0) {
        return motor_handler_stop_all();
    }

    int speed_percent = (degrees * 100) / 180; // Map 180° -> 100% PWM

    // For rotation in place:
    //  Clockwise: left wheels forward, right wheels reverse
    //  Counterclockwise: left wheels reverse, right wheels forward
    int left_speed = clockwise ? speed_percent : -speed_percent;
    int right_speed = clockwise ? -speed_percent : speed_percent;

    motor_handler_set_motor(MOTOR_1, left_speed);  // Front Left
    motor_handler_set_motor(MOTOR_3, left_speed);  // Rear Left
    motor_handler_set_motor(MOTOR_2, right_speed); // Front Right
    motor_handler_set_motor(MOTOR_4, right_speed); // Rear Right

    ESP_LOGI(TAG, "Rotate %s %d° -> speed=%d%%", clockwise ? "CW" : "CCW", degrees, speed_percent);
    return ESP_OK;
}



