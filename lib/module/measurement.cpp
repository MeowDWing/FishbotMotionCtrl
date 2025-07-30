#include"measurement.h"
#include<Arduino.h>


namespace Uls {
    void init(){
        pinMode(Ultrasound_TRIG, OUTPUT);
        pinMode(Ultrasound_ECHO, INPUT);
    }

    float getDistance(int delta_time) {
        /*
            param::
                delta_time - 脉冲时长，默认为10ms脉冲
            
            return::
                单位 cm
        */

        digitalWrite(Ultrasound_TRIG, HIGH);
        delayMicroseconds(delta_time);
        digitalWrite(Ultrasound_TRIG, LOW);

        double delta_data = pulseIn(Ultrasound_ECHO, HIGH);
        float distance = delta_data * 0.0343 / 2;  // 0.0343 cm/s  = 331.3 \sqrt( 1 + T/273.15)  * (1e-6/1e-2) cm/us -- T: 摄氏温度，取20, 精确值约为0.0343214622
        return distance ; 
    }
}