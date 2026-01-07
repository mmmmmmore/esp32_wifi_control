#ifndef MOTOR_HANDLER_H
#define MOTOR_HANDLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "esp_err.h"
#include <stdbool.h>

// Motor IDs (1-4)
#define MOTOR_1  1
#define MOTOR_2  2
#define MOTOR_3  3
#define MOTOR_4  4
#define MOTOR_COUNT 4

// Motor control modes for DRV8833
typedef enum {
    MOTOR_STOP_COAST = 0,   // IN1=0, IN2=0 - Free running/coast
    MOTOR_FORWARD,           // IN1=PWM, IN2=0 - Forward with PWM speed
    MOTOR_REVERSE,           // IN1=0, IN2=PWM - Reverse with PWM speed
    MOTOR_BRAKE              // IN1=1, IN2=1 - Active brake
} motor_mode_t;

/**
 * @brief Initialize all motors with GPIO and PWM configuration
 * @return ESP_OK on success
 */
esp_err_t motor_handler_init(void);

/**
 * @brief Set individual motor speed and direction
 * @param motor_id Motor ID (1-4)
 * @param speed Speed value (-100 to +100), negative for reverse
 * @return ESP_OK on success
 */
esp_err_t motor_handler_set_motor(int motor_id, int speed);

/**
 * @brief Control motor with specific mode
 * @param motor_id Motor ID (1-4)
 * @param mode Motor control mode
 * @param speed_percent Speed percentage (0-100)
 * @return ESP_OK on success
 */
esp_err_t motor_handler_set_mode(int motor_id, motor_mode_t mode, int speed_percent);

/**
 * @brief Stop all motors (coast mode)
 * @return ESP_OK on success
 */
esp_err_t motor_handler_stop_all(void);

/**
 * @brief Brake all motors (active brake)
 * @return ESP_OK on success
 */
esp_err_t motor_handler_brake_all(void);

/**
 * @brief Enable/disable motor driver boards (STBY pin)
 * @param enable true to enable, false to disable (sleep mode)
 * @return ESP_OK on success
 */
esp_err_t motor_handler_enable(bool enable);

/**
 * @brief Update motors based on joystick angle and distance (for mecanum/omni wheels)
 * @param angle_deg Joystick angle in degrees (0-360)
 * @param distance_percent Joystick distance from center (0-100)
 * @return ESP_OK on success
 */
esp_err_t motor_handler_update(int angle_deg, int distance_percent);

/**
 * @brief Rotate the robot in place based on direction and degrees
 * @param clockwise true for clockwise, false for counterclockwise
 * @param degrees Rotation magnitude (0-180). 180 maps to 100% PWM.
 * @return ESP_OK on success
 */
esp_err_t motor_handler_rotate(bool clockwise, int degrees);

#ifdef __cplusplus
}
#endif

#endif // MOTOR_HANDLER_H
