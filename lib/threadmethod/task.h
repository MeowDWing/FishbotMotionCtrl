#ifndef __TASK_H__
#define __TASK_H__

#include <Arduino.h>
#include "motor.h"
#include "register.h"
#include "Pin.h"


class ExecuteParameter
{
public:
    Register& reg;
    SemaphoreHandle_t& sem;
    Imu& imu;

    ExecuteParameter(Register& r, SemaphoreHandle_t& s, Imu& i);
};

class EventAddParameter
{
public:
    Register& handler;
    SemaphoreHandle_t& sem;
    Motor& motor;

    EventAddParameter(Register& h, SemaphoreHandle_t& s, Motor& m);
};

#endif