#include <Arduino.h>
#include <BLE/BLE.h>

BLE bleServer;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE Server...");

  bleServer.begin();
}

void loop() {
  if (bleServer.deviceConnected) {
    // Do something when the device is connected
    Serial.println("Device connected");
  } else {
    // Do something when the device is disconnected
    Serial.println("Device disconnected");
  }

  delay(1000); // Delay for 1 second
}