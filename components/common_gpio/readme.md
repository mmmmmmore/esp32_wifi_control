# components/common_gpio — Pin mapping (DRV8833 configuration)

This file documents the pin assignments used by the project for the DRV8833 dual-H-bridge motor drivers.

Key notes:
- We use two DRV8833 driver ICs to control four motors. Each motor has two inputs (IN1/IN2); PWM is output on the dedicated PWM pin assigned to that motor.
- Avoid using SPI flash pins (typically GPIO 6..11) for motor control — using those may brick or interfere with flash access.
- Verify these pins against your board schematics and remap if your hardware differs.

Motor pin assignments (DRV8833):

/* Motor 1 */
#define GPIO_MOTOR1_IN1     2    // Direction / IN1
#define GPIO_MOTOR1_IN2     3    // Direction / IN2
#define GPIO_MOTOR1_PWM     21   // PWM output (LED PWM channel 0)

/* Motor 2 */
#define GPIO_MOTOR2_IN1     4
#define GPIO_MOTOR2_IN2     5
#define GPIO_MOTOR2_PWM     22

/* Motor 3 */
#define GPIO_MOTOR3_IN1     12
#define GPIO_MOTOR3_IN2     13
#define GPIO_MOTOR3_PWM     14

/* Motor 4 */
#define GPIO_MOTOR4_IN1     15
#define GPIO_MOTOR4_IN2     16
#define GPIO_MOTOR4_PWM     17

/* Shared nSLEEP (STBY) pin used to enable/disable both DRV8833 chips */
#define GPIO_MOTOR_STBY      27

Other notes:
- LED status and I2C pins are defined in `common_gpio.h`.
- LEDC channels used:
  - `LEDC_CHANNEL_MOTOR1_A` -> Motor 1 PWM
  - `LEDC_CHANNEL_MOTOR1_B` -> Motor 2 PWM
  - `LEDC_CHANNEL_MOTOR2_A` -> Motor 3 PWM
  - `LEDC_CHANNEL_MOTOR2_B` -> Motor 4 PWM

If you want different pin assignments (for example to match a specific board revision), tell me which physical pins you'd prefer and I will update the header and C initialization accordingly.
