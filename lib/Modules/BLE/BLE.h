#ifndef BLE_H
#define BLE_H

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

class BLE {
public:
    BLE();
    void begin();
    void setValue(const std::string &value);
    bool deviceConnected;

private:
    BLEServer *pServer;
    BLECharacteristic *pCharacteristic;
};

class MyServerCallbacks : public BLEServerCallbacks {
public:
    MyServerCallbacks(BLE* server);
    void onConnect(BLEServer* pServer);
    void onDisconnect(BLEServer* pServer);

private:
    BLE* bleServer;
};

class MySecurityCallbacks : public BLESecurityCallbacks {
public:
    uint32_t onPassKeyRequest();
    void onAuthenticationComplete(esp_ble_auth_cmpl_t cmpl);
};

#endif
