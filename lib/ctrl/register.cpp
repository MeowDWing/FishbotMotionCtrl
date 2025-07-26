#include "register.h"


Register::Register()
{
    handler = xQueueCreate(10, sizeof(CtrlEvent*)); // Create a queue to hold CtrlEvent pointers
}


bool Register::register_event(CtrlEvent* event){
    int real_time = time(nullptr);
    event->event_time = real_time; // Set the event time to the current time


    if (xQueueSend(handler, &event, portMAX_DELAY) != pdTRUE) {
        Serial.println("Failed to register event.");
        return false; // Return false if the event could not be registered
    }

    return true;
}
