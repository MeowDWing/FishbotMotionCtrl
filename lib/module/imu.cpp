#include <Arduino.h>

#include "imu.h"


Imu::Imu() : mpu(Wire) {
    // 设置MPU通信模式为无线通信
}

void Imu::init() {
    Wire.begin(I2C_SDA, I2C_SCL); // Initialize I2C with specified SDA and SCL pins
    status = mpu.begin();

    if (status != 0) {
        // 115200 & Serial need initialize in main.cpp -> setup()
        Serial.print("MPU6050 connection failed with status: ");
        Serial.println(status);
    } else {
        Serial.println("MPU6050 initialized successfully.");
    }

    // 初始化状态传感器
    Serial.println("Calculating offsets, please keep the device still...");
    delay(1000); 
    mpu.calcOffsets(true, true); // Calculate offsets for gyro and accelerometer
}

float Imu::getAngle(char axis) {
    if (axis == 'x') {
        return mpu.getAngleX();
    } else if (axis == 'y') {
        return mpu.getAngleY();
    } else if (axis == 'z') {
        return mpu.getAngleZ();
    } else {
        Serial.println("Invalid axis specified. Use 'x', 'y', or 'z'.");
        return 0.0f; 
    }
}

bool Imu::dynamicModification(){
    // mpu修正项
    return false;
}

