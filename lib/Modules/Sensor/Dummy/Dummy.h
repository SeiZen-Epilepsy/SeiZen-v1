#ifndef DUMMY_H
#define DUMMY_H

#include <Arduino.h>

class Dummy {
public:
    Dummy();
    void begin();
    void generateRandomValue();
    String getValue();
    bool shouldUpdate();

private:
    int randomValue;
    unsigned long lastUpdateTime;
    const unsigned long updateInterval = 3000;
};

#endif
