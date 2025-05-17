#include <Arduino.h>
#include <BLE/BLE.h>
#include <Sensor/Dummy/Dummy.h>

#define led 2

BLE BleServer;
Dummy DummySensor;

void setup() {
    Serial.begin(115200);
    Serial.println("Starting BLE Server...");

    BleServer.begin();
    DummySensor.begin();

    pinMode(led, OUTPUT);
}

void loop() {
    if (BleServer.deviceConnected) {
        Serial.println("Device connected");
        digitalWrite(led, HIGH);
        
        if (DummySensor.shouldUpdate()) {
            DummySensor.generateRandomValue();
            String randomValue = DummySensor.getValue();
            
            BleServer.setValue(randomValue.c_str());
            
            Serial.print("Sent random value via BLE: ");
            Serial.println(randomValue);
        }
    } else {
        Serial.println("Device disconnected");
        digitalWrite(led, HIGH);
        delay(500);
        digitalWrite(led, LOW);
    }

    delay(1000);
}