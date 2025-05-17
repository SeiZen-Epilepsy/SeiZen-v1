#ifndef SEND_DATA_H
#define SEND_DATA_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <BLE/BLE.h>
#include <Sensor/Dummy/Dummy.h>

class SendData {
public:
    SendData(BLE* ble, Dummy* sensor);
    ~SendData();
    
    // Task management methods
    bool startTask(uint32_t stackSize = 2048, UBaseType_t priority = 1);
    void stopTask();
    bool isRunning() const;
    
private:
    // Static task function for FreeRTOS
    static void taskFunction(void* pvParameters);
    
    // Task control variables
    TaskHandle_t taskHandle;
    bool running;
    
    // References to required objects
    BLE* bleServer;
    Dummy* dummySensor;
    
    // Task parameters
    uint32_t sendInterval;  // milliseconds
};

#endif // SEND_DATA_H
