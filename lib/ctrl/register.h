#ifndef __RESISTER_H__
#define __RESISTER_H__

#include <Arduino.h>
#include <queue>
#include <utility>
#include <vector>
#include <ctime>

#include "event.h"

class Register
{
public:
    QueueHandle_t handler;

    Register();
    ~Register() = default;
    bool register_event(CtrlEvent* event);
};
#endif // __RESISTER_H__
