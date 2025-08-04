#include "task.h"
#include "config.hpp"

ExecuteParameter::ExecuteParameter(QueueHandle_t& q, SemaphoreHandle_t& s, Imu& i)
    : queue(q), sem(s), imu(i) {
    // Constructor initializes the ExecuteParameter with a Register reference and a SemaphoreHandle
}

EventAddParameter::EventAddParameter(EventRegister& h, SemaphoreHandle_t& s, Motor& m)
    : handler(h), sem(s), motor(m) {
    // Constructor initializes the EventAddParameter with a Register reference, SemaphoreHandle, and Motor reference
}

EventRegister::EventRegister()
{
    handler = xQueueCreate(10, sizeof(CtrlEvent*)); // Create a queue to hold CtrlEvent pointers
}


bool EventRegister::registerEvent(CtrlEvent* event){
    int real_time = time(nullptr);
    event->event_time = real_time; // Set the event time to the current time

    if (xQueueSend(handler, &event, portMAX_DELAY) != pdTRUE) {
        Serial.println("Failed to register event.");
        return false; // Return false if the event could not be registered
    }

    return true;
}


void rectMode(Motor& motor, EventRegister& handler,SemaphoreHandle_t& sem)
{
    float distance2barrier = Uls::getDistance(); // 获取距离障碍物的距离
    if(distance2barrier < DEFAULT_TURN_DISTANCE) { // If the distance is less than 20 cm
        CtrlEvent* event = nullptr;
        if(distance2barrier<5.0f){
          event = new StraightEvent(0, motor); 
        }else{
          event = new SpinEvent(90.0f, 80, true, motor); // Create a SpinEvent
        } 
          handler.registerEvent(event); // Register the event
          Serial.println("Succ to register SpinEvent");
          xSemaphoreTake(sem, portMAX_DELAY); 
      }
}