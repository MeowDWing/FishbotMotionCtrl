/*

    Imu 用于操作MPU8060 芯片，获取车的状态信息

*/

#ifndef __IMU_H__
#define __IMU_H__

#include "Pin.h"
#include "Wire.h"
#include <MPU6050_light.h>

class Imu {
public:
    MPU6050 mpu;
    byte status;
    Imu();
    void init();

    float getAngle(char axis='z');

    bool dynamicModification();


};



#endif // __IMU_H__