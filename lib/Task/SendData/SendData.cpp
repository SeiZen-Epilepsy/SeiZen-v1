#include "SendData.h"

// Constructor
SendData::SendData(BLE* ble, Dummy* sensor) 
    : bleServer(ble)
    , dummySensor(sensor)
    , taskHandle(NULL)
    , running(false)
    , sendInterval(1000) // Default to 1 second interval
{
}

// Destructor
SendData::~SendData() {
    stopTask();
}

// Start the FreeRTOS task
bool SendData::startTask(uint32_t stackSize, UBaseType_t priority) {
    if (running) {
        return true; // Task already running
    }
    
    // Create the task
    BaseType_t result = xTaskCreate(
        taskFunction,       // Task function
        "SendDataTask",     // Task name
        stackSize,          // Stack size (words)
        this,               // Parameter to pass
        priority,           // Task priority
        &taskHandle         // Task handle
    );
    
    if (result != pdPASS) {
        Serial.println("Failed to create SendData task");
        return false;
    }
    
    running = true;
    Serial.println("SendData task started");
    return true;
}

// Stop the FreeRTOS task
void SendData::stopTask() {
    if (!running || taskHandle == NULL) {
        return; // Task not running
    }
    
    vTaskDelete(taskHandle);
    taskHandle = NULL;
    running = false;
    Serial.println("SendData task stopped");
}

// Check if task is running
bool SendData::isRunning() const {
    return running;
}

// Static task function that runs on FreeRTOS
void SendData::taskFunction(void* pvParameters) {
    // Get the SendData instance
    SendData* sendData = static_cast<SendData*>(pvParameters);
    
    // Check if pointers are valid
    if (!sendData || !sendData->bleServer || !sendData->dummySensor) {
        Serial.println("Invalid pointers in SendData task");
        vTaskDelete(NULL);
        return;
    }
    
    // Task loop
    for (;;) {
        // Check BLE connection status
        if (sendData->bleServer->deviceConnected) {
            Serial.println("Device connected - Sending data");
            
            // Generate and send data if it's time to update
            if (sendData->dummySensor->shouldUpdate()) {
                sendData->dummySensor->generateRandomValue();
                String randomValue = sendData->dummySensor->getValue();
                
                // Send data over BLE
                sendData->bleServer->setValue(randomValue.c_str());
                
                Serial.print("Sent random value via BLE: ");
                Serial.println(randomValue);
            }
        } else {
            Serial.println("Device disconnected - Waiting for connection");
        }
        
        // Delay for the specified interval using FreeRTOS delay
        vTaskDelay(sendData->sendInterval / portTICK_PERIOD_MS);
    }
    
    // Should never reach here, but just in case
    vTaskDelete(NULL);
}
