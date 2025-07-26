#include"RayDistance.h"
#include<Arduino.h>


namespace Uls {
    void init(){
        pinMode(Ultrasound_TRIG, OUTPUT);
        pinMode(Ultrasound_ECHO, INPUT);
    }

    float getDistance(int delta_time) {

        digitalWrite(Ultrasound_TRIG, HIGH);
        delayMicroseconds(delta_time);
        digitalWrite(Ultrasound_TRIG, LOW);

        double delta_data = pulseIn(Ultrasound_ECHO, HIGH);
        float distance = delta_data * 0.0343 / 2;
        return distance ;// Replace with actual distance measurement code
    }
}