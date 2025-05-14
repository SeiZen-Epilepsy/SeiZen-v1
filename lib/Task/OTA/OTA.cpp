#include <OTA/OTA.h>

OTA::OTA() {
    // Constructor
    _hostname = "ESP32";
    const char* passwordEnv = std::getenv("OTA_PASSWORD");
    _password = passwordEnv ? passwordEnv : "";
    _port = 3232;
    _certificate = nullptr;
    _privateKey = nullptr;
}