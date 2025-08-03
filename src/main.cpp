// standard libraries
#include <ctime>
#include <utility>

// ESP32S3 libraries
#include <Arduino.h>
#include <Esp32PcntEncoder.h>

// custom libraries
#include "Pin.h"
#include "motor.h"
#include "measurement.h"
#include "task.h"


Imu imu{}; // Create an instance of the Imu class

Motor motor{90, imu}; // Create an instance of the Motor class with a PWM pin and IMU instance


EventRegister reg{}; // Create an instance of the Register class


SemaphoreHandle_t sem = xSemaphoreCreateBinary(); // Create a binary semaphore
ExecuteParameter execParam(reg, sem, imu); // Create an ExecuteParameter instance
EventAddParameter eventAddParam(reg, sem, motor); // Create an EventAddParameter

void ExecuteThread(void* pvParameters)
{
  ExecuteParameter* param = static_cast<ExecuteParameter*>(pvParameters);
  EventRegister& reg = param->reg;
  SemaphoreHandle_t& sem = param->sem;

  while (true) {
    CtrlEvent *event = nullptr;;
        if (xQueueReceive(reg.handler, &event, portMAX_DELAY) == pdTRUE)
        {
          event->execute(); // 执行事件
          xSemaphoreGive(sem); // 释放信号量
          delete event; // 删除事件对象以释放内存
        } else {
          Serial.println("Failed to receive event from queue.");
        }
      delay(10);
  }
}

void EventAddThread(void* pvParameters)

{
  EventAddParameter* param = static_cast<EventAddParameter*>(pvParameters);
  EventRegister& handler = param->handler;
  SemaphoreHandle_t& sem = param->sem;
  Motor& m = param->motor;



  while (true) {
      
      rectMode(m, handler, sem);
      // Implement the logic to create and register an event


      delay(10);
  }
}



void setup()
{
    Serial.begin(115200); // 初始化串口通信，设置通信速率为115200
    imu.init(); // Initialize the IMU
    motor.setup();
    Uls::init();

    Serial.println("Launching Event Execute Thread.");
    xTaskCreatePinnedToCore(
        ExecuteThread, // Function to be executed
        "ExecuteThread", // Name of the task
        4096, // Stack size
        &execParam, // Parameter to pass to the task
        1, // Task priority
        NULL, // Task handle
        1 // Core to run the task on (1 for core 1)
    );
    Serial.println("Launching Event Addition Thread.");
    xTaskCreatePinnedToCore(
        EventAddThread, // Function to be executed
        "EventAddThread", // Name of the task
        4096, // Stack size
        &eventAddParam, // Parameter to pass to the task
        1,
        NULL,
        0 // Core to run the task on (1 for core 1)
        );


}

void loop(){
  Serial.printf("[DEBUG!] Current Angle: %.2f, ...\n", imu.getAngle('z'));
  delay(100);
}


