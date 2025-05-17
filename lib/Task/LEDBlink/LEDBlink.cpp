#include "LEDBlink.h"

// Constructor
LEDBlink::LEDBlink(BLE* ble, uint8_t pin) 
    : bleServer(ble)
    , ledPin(pin)
    , taskHandle(NULL)
    , running(false)
    , blinkInterval(500) // Default to 500ms blink interval
{
    // Initialize the LED pin as output
    pinMode(ledPin, OUTPUT);
}

// Destructor
LEDBlink::~LEDBlink() {
    stopTask();
}

// Start the FreeRTOS task
bool LEDBlink::startTask(uint32_t stackSize, UBaseType_t priority) {
    if (running) {
        return true; // Task already running
    }
    
    // Create the task
    BaseType_t result = xTaskCreate(
        taskFunction,       // Task function
        "LEDBlinkTask",     // Task name
        stackSize,          // Stack size (words)
        this,               // Parameter to pass
        priority,           // Task priority
        &taskHandle         // Task handle
    );
    
    if (result != pdPASS) {
        Serial.println("Failed to create LEDBlink task");
        return false;
    }
    
    running = true;
    Serial.println("LEDBlink task started");
    return true;
}

// Stop the FreeRTOS task
void LEDBlink::stopTask() {
    if (!running || taskHandle == NULL) {
        return; // Task not running
    }
    
    vTaskDelete(taskHandle);
    taskHandle = NULL;
    running = false;
    Serial.println("LEDBlink task stopped");
}

// Check if task is running
bool LEDBlink::isRunning() const {
    return running;
}

// Static task function that runs on FreeRTOS
void LEDBlink::taskFunction(void* pvParameters) {
    // Get the LEDBlink instance
    LEDBlink* ledBlink = static_cast<LEDBlink*>(pvParameters);
    
    // Check if pointers are valid
    if (!ledBlink || !ledBlink->bleServer) {
        Serial.println("Invalid pointers in LEDBlink task");
        vTaskDelete(NULL);
        return;
    }
    
    // Task loop
    for (;;) {
        if (ledBlink->bleServer->deviceConnected) {
            // Connected - LED stays on
            digitalWrite(ledBlink->ledPin, HIGH);
            
            // Small delay to prevent watchdog issues
            vTaskDelay(100 / portTICK_PERIOD_MS);
        } else {
            // Disconnected - LED blinks
            digitalWrite(ledBlink->ledPin, HIGH);
            vTaskDelay(ledBlink->blinkInterval / portTICK_PERIOD_MS);
            digitalWrite(ledBlink->ledPin, LOW);
            vTaskDelay(ledBlink->blinkInterval / portTICK_PERIOD_MS);
        }
    }
    
    // Should never reach here, but just in case
    vTaskDelete(NULL);
}
