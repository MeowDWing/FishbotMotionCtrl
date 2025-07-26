#include "task.h"

ExecuteParameter::ExecuteParameter(Register& r, SemaphoreHandle_t& s)
    : reg(r), sem(s) {
    // Constructor initializes the ExecuteParameter with a Register reference and a SemaphoreHandle
}

EventAddParameter::EventAddParameter(Register& h, SemaphoreHandle_t& s, Motor& m)
    : handler(h), sem(s), motor(m) {
    // Constructor initializes the EventAddParameter with a Register reference, SemaphoreHandle, and Motor reference
}