#ifndef LED_BLINK_H
#define LED_BLINK_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <BLE/BLE.h>

class LEDBlink {
public:
    LEDBlink(BLE* ble, uint8_t ledPin);
    ~LEDBlink();
    
    // Task management methods
    bool startTask(uint32_t stackSize = 1024, UBaseType_t priority = 1);
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
    uint8_t ledPin;
    
    // Task parameters
    uint32_t blinkInterval;  // milliseconds
};

#endif // LED_BLINK_H
