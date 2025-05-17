#include "BLE.h"

#define SERVICE_UUID        "12345678-1234-1234-1234-123456789abc"
#define CHARACTERISTIC_UUID "87654321-4321-4321-4321-abcdefabcdef"
#define DEVICE_NAME         "SeiZen-v1"

BLE::BLE() {
    deviceConnected = false;
    pServer = nullptr;
    pCharacteristic = nullptr;
}

void BLE::begin() {
    BLEDevice::init(DEVICE_NAME);
    
    pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks(this));

    BLEService *pService = pServer->createService(SERVICE_UUID);
    pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ |
        BLECharacteristic::PROPERTY_WRITE
    );

    pCharacteristic->setValue("Hello from ESP32!");
    pService->start();

    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->start();

    // Enable BLE security
    BLESecurity *pSecurity = new BLESecurity();
    pSecurity->setAuthenticationMode(ESP_LE_AUTH_REQ_SC_MITM_BOND);
    pSecurity->setCapability(ESP_IO_CAP_NONE);
    pSecurity->setInitEncryptionKey(ESP_BLE_ENC_KEY_MASK | ESP_BLE_ID_KEY_MASK);
}

void BLE::setValue(const std::string &value) {
    if (pCharacteristic) {
        pCharacteristic->setValue(value);
    }
}

MyServerCallbacks::MyServerCallbacks(BLE* server) {
    bleServer = server;
}

void MyServerCallbacks::onConnect(BLEServer* pServer) {
    bleServer->deviceConnected = true;
}

void MyServerCallbacks::onDisconnect(BLEServer* pServer) {
    bleServer->deviceConnected = false;
    pServer->getAdvertising()->start();
}

uint32_t MySecurityCallbacks::onPassKeyRequest() {
    return 123456; // Set a passkey
}

void MySecurityCallbacks::onAuthenticationComplete(esp_ble_auth_cmpl_t cmpl) {
    if (cmpl.success) {
        Serial.println("Authentication Success");
    } else {
        Serial.println("Authentication Failed");
    }
}
