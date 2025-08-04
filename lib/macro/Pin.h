#ifndef __PIN_DEFINE__
#define __PIN_DEFINE__

// ultrasound pins
#define Ultrasound_TRIG 21
#define Ultrasound_ECHO 47

// led pins
#define LED1 48

//I2C bus pins
#define I2C_SDA 12
#define I2C_SCL 13

// ticks counter encoder pins
#define FRONT_LEFT_MOTOR_ENCODER_A 6
#define FRONT_LEFT_MOTOR_ENCODER_B 7
#define FRONT_RIGHT_MOTOR_ENCODER_A 18
#define FRONT_RIGHT_MOTOR_ENCODER_B 17
#define BACK_LEFT_MOTOR_ENCODER_A 20
#define BACK_LEFT_MOTOR_ENCODER_B 19
#define BACK_RIGHT_MOTOR_ENCODER_A 11
#define BACK_RIGHT_MOTOR_ENCODER_B 10

// Motor pins
#define FRONT_LFET_MOTOR_PIN_1 5
#define FRONT_LFET_MOTOR_PIN_2 4
#define FRONT_RIGHT_MOTOR_PIN_1 15
#define FRONT_RIGHT_MOTOR_PIN_2 16
#define BACK_LEFT_MOTOR_PIN_1 3
#define BACK_LEFT_MOTOR_PIN_2 8
#define BACK_RIGHT_MOTOR_PIN_1 46
#define BACK_RIGHT_MOTOR_PIN_2 9

// screen pins

#endif

#ifndef __EVENT_CODE__
#define __EVENT_CODE__

// Define event codes for status code
#define STATUS_NOT_GOT -0x01
#define SPIN_EVENT 0x81
#define SET_SPEED_EVENT 0x82

// running mode code
#define MODE_NUM 4
#define DEBUG_MODE 0
#define RECT_MODE 1
#define CYCLE_MODE 2
#define LINE_MODE 3


#endif

#ifndef __CAR_INFO__
#define __CAR_INFO__

// Define constants for car information
#define WHEEL_DIAMETER 65
#define WHEEL_CM_PER_ROUND (PI * WHEEL_DIAMETER) // 65mm

#define FRONT_LEFT_MOTOR_ID 0
#define FRONT_LEFT_WHEEL_PULSES_PER_ROUND 1975.0f
#define FRONT_RIGHT_MOTOR_ID 1
#define FRONT_RIGHT_WHEEL_PULSES_PER_ROUND 1975.0f
#define BACK_LEFT_MOTOR_ID 2
#define BACK_LEFT_WHEEL_PULSES_PER_ROUND 1975.0f
#define BACK_RIGHT_MOTOR_ID 3
#define BACK_RIGHT_WHEEL_PULSES_PER_ROUND 1970.0f

#endif
