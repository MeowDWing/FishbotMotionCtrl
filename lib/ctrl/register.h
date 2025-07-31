#ifndef __RESISTER_H__
#define __RESISTER_H__

#include <Arduino.h>
#include "event.h"

class Register
{
public:
    QueueHandle_t handler;

    Register();
    ~Register() = default;
    bool registerEvent(CtrlEvent* event);
};
#endif // __RESISTER_H__
