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

class MySecurity : public BLESecurityCallbacks {
    public:
        MySecurity(BLE* server);
        uint32_t onPassKeyRequest();
        void onAuthenticationComplete(bool success);
    
    private:
        BLE* bleServer;
    };

#endif
