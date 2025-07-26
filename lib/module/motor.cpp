#include "motor.h"


Motor::Motor(int init_pwm, Imu& i):pwm(init_pwm),imu(i)
{
}

Motor::~Motor()
{
}

void Motor::setup()
{
    encoders[0].init(0, 6, 7); // 初始化第一个编码器，使用GPIO 32和33连接
    encoders[1].init(1, 18, 17); // 初始化第二个编码器，使用GPIO 26和25连接
    encoders[2].init(2, 20, 19); // 初始化第一个编码器，使用GPIO 32和33连接
    encoders[3].init(3, 11, 10); // 初始化第二个编码器，使用GPIO 26和25连接
    motor.attachMotor(0, 5, 4);
    motor.attachMotor(1, 15, 16);
    motor.attachMotor(2, 3, 8);
    motor.attachMotor(3, 46, 9);
    // Initialize motor pins or settings if needed
    Serial.println("Motor setup complete.");
}

void Motor::SetTotalSpeed(int per)
{
    pwm = per;
    // Set the speed for each motor
    motor.updateMotorSpeed(0, per); // Set speed for motor 0
    motor.updateMotorSpeed(1, per); // Set speed for motor 1
    motor.updateMotorSpeed(2, per); // Set speed for motor 2
    motor.updateMotorSpeed(3, per); // Set speed for motor 3

    Serial.println("Total speed set for all motors.");
}

void Motor::spin_mode(int per, bool clockwise)
{
    pwm = per;
    if (clockwise) {
        motor.updateMotorSpeed(0, per); // Set speed for motor 0
        motor.updateMotorSpeed(1, per); // Set speed for motor 1
        motor.updateMotorSpeed(2, -per); // Reverse direction for motor 2
        motor.updateMotorSpeed(3, -per); // Reverse direction for motor 3
    } else {
        motor.updateMotorSpeed(0, -per); // Reverse direction for motor 0
        motor.updateMotorSpeed(1, -per); // Reverse direction for motor 1
        motor.updateMotorSpeed(2, per); // Set speed for motor 2
        motor.updateMotorSpeed(3, per); // Set speed for motor 3
    }
}

void Motor::spin_with_angle(float angle, int speed_per, bool clockwise)
{
    spin_mode(speed_per, clockwise);
    if(!clockwise){
        angle = -angle; // If not clockwise, reverse the angle
    }
    Serial.printf("Spinning with angle: %.2f degrees, speed: %d, clockwise: %d\n", angle, speed_per, clockwise);

    imu.mpu.update(); // Update the IMU data
    float present_angle = imu.getAngle('z'); // Get the current angle from the IMU
    float target_angle = _calTargetAngle(angle, present_angle); // Calculate the target angle

    printf("Current angle: %.2f, Target angle: %.2f\n", imu.getAngle('z'), target_angle);
    while(
        clockwise ? imu.getAngle() < target_angle : imu.getAngle() > target_angle
    ) {
        printf("Current angle: %.2f, Target angle: %.2f\n", imu.getAngle('z'), target_angle);
        // Continuously check the angle until the target angle is reached
        delay(100); // Add a small delay to avoid busy-waiting
        imu.mpu.update(); // Update the IMU data
    }
    spin_mode(0, true); // Stop the motors after reaching the target angle
    // Implement the actual spinning logic here
}

float Motor::_calTargetAngle(float spin_angle, float present_angle)
{
    // Calculate the target angle based on the current angle and the desired target angle
    float target_angle = present_angle + spin_angle;

    // if(target_angle > 180.0f) {
    //     target_angle -= 360.0f; // Normalize to -180 to 180 range
    // } else if(target_angle < -180.0f) {
    //     target_angle += 360.0f; // Normalize to -180 to 180 range
    // }

    return target_angle;
}


float Id2PulsesPerRound(int motor_id)
{
    switch (motor_id)
    {
    case FRONT_LEFT_MOTOR_ID:
        return FRONT_LEFT_WHEEL_PULSES_PER_ROUND;
    case FRONT_RIGHT_MOTOR_ID:
        return FRONT_RIGHT_WHEEL_PULSES_PER_ROUND;
    case BACK_LEFT_MOTOR_ID:
        return BACK_LEFT_WHEEL_PULSES_PER_ROUND;
    case BACK_RIGHT_MOTOR_ID:
        return BACK_RIGHT_WHEEL_PULSES_PER_ROUND;
    default:
        return -1.0f; // Invalid motor ID
    }
}

std::pair<int,int> Id2Encoder(int motor_id)
{
    switch (motor_id)
    {
    case FRONT_LEFT_MOTOR_ID:
        return std::pair<int,int>(FRONT_LEFT_MOTOR_ENCODER_A, FRONT_LEFT_MOTOR_ENCODER_B);
    case FRONT_RIGHT_MOTOR_ID:
        return std::pair<int,int>(FRONT_RIGHT_MOTOR_ENCODER_A, FRONT_RIGHT_MOTOR_ENCODER_B);
    case BACK_LEFT_MOTOR_ID:
        return std::pair<int,int>(BACK_LEFT_MOTOR_ENCODER_A, BACK_LEFT_MOTOR_ENCODER_B);
    case BACK_RIGHT_MOTOR_ID:
        return std::pair<int,int>(BACK_RIGHT_MOTOR_ENCODER_A, BACK_RIGHT_MOTOR_ENCODER_B);
    default:
        return std::pair<int,int>(-1,-1);
    }
}

float getDistance(int motor_id, Esp32PcntEncoder& encoder)
{
    auto p = Id2Encoder(motor_id);
    if (p.first == -1 || p.second == -1) {
        Serial.println("Invalid motor ID");
        return -1.0f; // Return an error value
    }else{
        int encoder_a = p.first;
        int encoder_b = p.second;

        // Assuming the encoder has a method to get speed
        int ticks = encoder.getTicks();
        float distance = (ticks / Id2PulsesPerRound(motor_id)) * WHEEL_CM_PER_ROUND; // Calculate distance traveled
        return distance;
    }

    return -1.0f;
}

float getSpeed(int motor_id, Esp32PcntEncoder& encoder){
    
    // Have not implemented the speed calculation yet
    return -1.0f;
}

