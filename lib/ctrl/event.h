#ifndef __EVENT_H__
#define __EVENT_H__

#include <Arduino.h>

#include <ctime>
#include "motor.h"
#include "Pin.h"


class CtrlEvent
{
public:
    int event_code; // Event code to identify the type of event
    time_t event_time; // Time when event need to execute

    CtrlEvent() = default;
    ~CtrlEvent() = default;

    virtual void execute();

};

class SpinEvent : public CtrlEvent
{
public:
    int event_code = SPIN_EVENT; // Spin event code

    int angle; // ID of the motor to spin
    int speed; // Speed of the spin
    bool clockwise; // Direction of the spin
    Motor& m;

    SpinEvent(float angle, int spd, bool clockwise, Motor& motor_instance);

    void execute() override;

};

class StraightEvent : public CtrlEvent
{
public:
    int event_code = SET_SPEED_EVENT;

    int speed; // Speed to set for the motors
    Motor& m;

    StraightEvent(int spd, Motor& motor_instance);
    void execute() override;

};

#endif  