#ifndef OTA_H
#define OTA_H

#include <Arduino.h>
#include <ArduinoOTA.h>

class OTA {
    public:
        OTA();
        void begin();
        void handle();
        void end();
        void setHostname(const char* hostname);
        void setPassword(const char* password);
        void setPort(int port);
        void setCertificate(const char* certificate);
        void setPrivateKey(const char* privateKey);
    private:
        const char* _hostname;
        const char* _password;
        int _port;
        const char* _certificate;
        const char* _privateKey;
};

#endif