#include "event.h"

void CtrlEvent::execute()
{
    // Default implementation does nothing
    Serial.println("Executing base CtrlEvent, which does nothing.");
}


// ------------------SpinEvent---------------------
SpinEvent::SpinEvent(float angle, int spd, bool clockwise,Motor& motor_instance)
    : angle(angle), speed(spd), clockwise(clockwise), m(motor_instance) {
    // Constructor initializes the SpinEvent with motor ID, speed, and direction
}

void SpinEvent::execute() {

    Serial.println("SpinEvent::execute() called");
    int pwm_value = m.pwm;
    Serial.println("pwm update");
    m.spin_with_angle(angle, speed, clockwise);
    // back to straight mode
    m.SetTotalSpeed(pwm_value); // Set the total speed for all motors

}


// -------------------StraightEvent-------------------

StraightEvent::StraightEvent(int spd, Motor& motor_instance)
    : speed(spd), m(motor_instance) {
    // Constructor initializes the StraightEvent with speed
}

void StraightEvent::execute() {
    // Set the speed for the motors
    m.SetTotalSpeed(speed);
}