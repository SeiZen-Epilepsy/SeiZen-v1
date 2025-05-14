#include <BLE/BLE.h>

#define SERVICE_UUID        "12345678-1234-1234-1234-123456789abc"
#define CHARACTERISTIC_UUID "87654321-4321-4321-4321-abcdefabcdef"


BLE::BLE() {
    deviceConnected = false;
    pServer = nullptr;
    pCharacteristic = nullptr;
}

void BLE::begin() {
    BLEDevice::init("ESP32 BLE");
    
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

    BLESecurity *pSecurity = new BLESecurity();
    pSecurity->setStaticPIN(123456);
    pSecurity->setAuthenticationMode(ESP_LE_AUTH_BOND);
    pSecurity->setCapability(ESP_IO_CAP_OUT);

    esp_ble_auth_req_t auth_req = ESP_LE_AUTH_REQ_SC_MITM_BOND;
    esp_ble_io_cap_t iocap = ESP_IO_CAP_OUT;
    uint8_t key_size = 16;
    uint8_t init_key = ESP_BLE_ENC_KEY_MASK | ESP_BLE_ID_KEY_MASK;
    uint8_t rsp_key = ESP_BLE_ENC_KEY_MASK | ESP_BLE_ID_KEY_MASK;
    uint32_t passkey = 123456;

    esp_ble_gap_set_security_param(ESP_BLE_SM_AUTHEN_REQ_MODE, &auth_req, sizeof(auth_req));
    esp_ble_gap_set_security_param(ESP_BLE_SM_IOCAP_MODE, &iocap, sizeof(iocap));
    esp_ble_gap_set_security_param(ESP_BLE_SM_SET_INIT_KEY, &init_key, sizeof(init_key));
    esp_ble_gap_set_security_param(ESP_BLE_SM_SET_RSP_KEY, &rsp_key, sizeof(rsp_key));
    esp_ble_gap_set_security_param(ESP_BLE_SM_PASSKEY, &passkey, sizeof(passkey));

    Serial.println("ESP32 BLE Bonding Enabled...");
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

MySecurity::MySecurity(BLE* server) {
    bleServer = server;
}

uint32_t MySecurity::onPassKeyRequest() {
    Serial.println("Passkey Requested!");
    return 123456; // Set a fixed passkey
}

void MySecurity::onAuthenticationComplete(bool success) {
    if (success) {
        Serial.println("Authentication Successful!");
    } else {
        Serial.println("Authentication Failed!");
    }
}