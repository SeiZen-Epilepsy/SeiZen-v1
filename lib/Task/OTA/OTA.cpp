#include "OTA.h"

OTA::OTA() {
    // Constructor
    _hostname = "ESP32";
    _password = "123456";
    _port = 3232;
    _certificate = nullptr;
    _privateKey = nullptr;
}
