#ifndef __MOTOR_H__
#define __MOTOR_H__

#include <utility>

#include <Arduino.h>
#include <Esp32McpwmMotor.h>
#include <Esp32PcntEncoder.h>

#include "Pin.h"
#include "imu.h"

class Motor
{
private:
    float _calTargetAngle(float tar_angle, float present_angle);
public:
    int pwm;
    Imu &imu;
    int current_status_code=-1;
    Esp32PcntEncoder encoders[4]; // 创建一个数组用于存储四个编码器
    Esp32McpwmMotor motor;
    Motor() = delete;
    Motor(int init_pwm, Imu& imu_instance);
    ~Motor();

    void setup();

    int getStatus();

    void SetTotalSpeed(int pwm_ratio=70);
    void spin_mode(int pwm_ratio=20, bool clockwise=true);

    void spin_with_angle(float angle, int speed_ratio, bool clockwise = true);

};

float Id2PulsesPerRound(int motor_id);
std::pair<int,int> Id2Encoder(int motor_id);
float getDistance(int motor_id, Esp32PcntEncoder& encoder);
float getSpeed(int motor_id, Esp32PcntEncoder& encoder);


#endif // __MOTOR_H__