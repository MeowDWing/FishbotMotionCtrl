// standard libraries
#include <ctime>
#include <utility>

// ESP32S3 libraries
#include <Arduino.h>
#include <Esp32PcntEncoder.h>

// custom libraries
#include "Pin.h"
#include "motor.h"
#include "register.h"
#include "RayDistance.h"
#include "task.h"


Imu imu{}; // Create an instance of the Imu class

Motor motor{0, imu}; // Create an instance of the Motor class with a PWM pin and IMU instance


Register reg{}; // Create an instance of the Register class


SemaphoreHandle_t sem = xSemaphoreCreateBinary(); // Create a binary semaphore
ExecuteParameter execParam(reg, sem); // Create an ExecuteParameter instance
EventAddParameter eventAddParam(reg, sem, motor); // Create an EventAddParameter

void ExecuteThread(void* pvParameters)
{
  ExecuteParameter* param = static_cast<ExecuteParameter*>(pvParameters);
  Register& reg = param->reg;
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
      vTaskDelay(10 / portTICK_PERIOD_MS); // 延时10毫秒
  }
}

void EventAddThread(void* pvParameters)

{
  EventAddParameter* param = static_cast<EventAddParameter*>(pvParameters);
  Register& handler = param->handler;
  SemaphoreHandle_t& sem = param->sem;
  Motor& m = param->motor;
  while (true) {
      float distance2barrier = Uls::getDistance(); // 获取距离障碍物的距离
      Serial.println(distance2barrier);
      // Implement the logic to create and register an event
      if(distance2barrier < 20.0f) { // If the distance is less than 20 cm
          CtrlEvent* event = new SpinEvent(90.0f, 100, true, m); // Create a SpinEvent
          handler.register_event(event); // Register the event
          Serial.println("Succ to register SpinEvent");
          xSemaphoreTake(sem, portMAX_DELAY); 
      }
      

      vTaskDelay(10 / portTICK_PERIOD_MS); 
  }
}



void setup()
{
    Serial.begin(115200); // 初始化串口通信，设置通信速率为115200
    Serial.println("setup is running...");
    imu.init(); // Initialize the IMU
    Serial.println("setup is running...");
    motor.setup();
    Serial.println("setup is running...");
    Uls::init();
    Serial.println("setup is running...");
    
    

    Serial.println("start thread1");
    xTaskCreatePinnedToCore(
        ExecuteThread, // Function to be executed
        "ExecuteThread", // Name of the task
        4096, // Stack size
        &execParam, // Parameter to pass to the task
        1, // Task priority
        NULL, // Task handle
        1 // Core to run the task on (1 for core 1)
    );
    Serial.println("start thread2");
    xTaskCreatePinnedToCore(
        EventAddThread, // Function to be executed
        "EventAddThread", // Name of the task
        2048, // Stack size
        &eventAddParam, // Parameter to pass to the task
        1,
        NULL,
        0 // Core to run the task on (1 for core 1)
        );


}

void loop(){
  
}


