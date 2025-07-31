#include "event.h"

void CtrlEvent::execute()
{
    // 默认实现
    Serial.println("Executing base CtrlEvent, which does nothing.");
}


// ------------------SpinEvent---------------------
SpinEvent::SpinEvent(float angle, int spd, bool clockwise,Motor& motor_instance)
    : angle(angle), speed(spd), clockwise(clockwise), m(motor_instance) {
}

void SpinEvent::execute() {

    Serial.println("SpinEvent::execute() called");
    int pwm_value = m.pwm;
    Serial.println("pwm update");
    m.setTotalSpeed(0);
    // 在每个转向时重置角度积分，减少误差
    delay(1000);
    m.imu.mpu.calcOffsets(true,true);
    delay(1000);
    m.spinWithAngle(angle, speed, clockwise);
    m.setTotalSpeed(pwm_value); // Set the total speed for all motors

}


// -------------------StraightEvent-------------------

StraightEvent::StraightEvent(int spd, Motor& motor_instance)
    : speed(spd), m(motor_instance) {
}

void StraightEvent::execute() {
    m.setTotalSpeed(speed);
}