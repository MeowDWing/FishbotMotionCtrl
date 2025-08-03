#ifndef __TASK_H__
#define __TASK_H__

#include <vector>

#include <Arduino.h>

#include "motor.h"
#include "measurement.h"
#include "event.h"
#include "Pin.h"

/* 
---------------------线程参数设置----------------------
*/
class ExecuteParameter
{
public:
    QueueHandle_t& queue;
    SemaphoreHandle_t& sem;
    Imu& imu;

    ExecuteParameter(QueueHandle_t& r, SemaphoreHandle_t& s, Imu& i);
};

class EventAddParameter
{
public:
    EventRegister& handler;
    SemaphoreHandle_t& sem;
    Motor& motor;

    EventAddParameter(EventRegister& h, SemaphoreHandle_t& s, Motor& m);
};


/* 
---------------------EventAdd线程处理类----------------------
*/
class EventRegister
{
public:
    QueueHandle_t handler;

    EventRegister();
    ~EventRegister() = default;

    // 事件分发阶段
    void threadModeCheckIn();
    
    bool registerEvent(CtrlEvent* event);


};

void debugMode(void* pvParam);

void rectMode(Motor& motor, EventRegister& handler, SemaphoreHandle_t& sem);

void cycleMode(void* pvParam);


#endif