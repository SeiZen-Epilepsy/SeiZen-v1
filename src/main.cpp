#include <Arduino.h>
#include <BLE/BLE.h>
#include <Sensor/Dummy/Dummy.h>
#include <SendData/SendData.h>
#include <LEDBlink/LEDBlink.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define LED_PIN 2

// Global objects
BLE bleServer;
Dummy dummySensor;
SendData* sendDataTask;
LEDBlink* ledBlinkTask;

void setup() {
    // Initialize serial communication
    Serial.begin(115200);
    Serial.println("Starting SeiZen-v1 with FreeRTOS...");
    
    // Initialize hardware
    pinMode(LED_PIN, OUTPUT);
    
    // Initialize BLE and sensor
    bleServer.begin();
    dummySensor.begin();
    
    // Create and start the LED blink task
    ledBlinkTask = new LEDBlink(&bleServer, LED_PIN);
    if (!ledBlinkTask->startTask(1024, 1)) {
        Serial.println("Failed to start LEDBlink task!");
    }
    
    // Create and start the send data task
    sendDataTask = new SendData(&bleServer, &dummySensor);
    if (!sendDataTask->startTask(2048, 2)) {
        Serial.println("Failed to start SendData task!");
    }
    
    Serial.println("All tasks started.");
}

void loop() {}
