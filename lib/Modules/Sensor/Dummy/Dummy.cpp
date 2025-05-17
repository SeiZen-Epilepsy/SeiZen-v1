#include "Dummy.h"

Dummy::Dummy() {
    randomValue = 0;
    lastUpdateTime = 0;
}

void Dummy::begin() {
    randomSeed(analogRead(0));
    lastUpdateTime = millis();
}

void Dummy::generateRandomValue() {
    randomValue = random(1001);
    lastUpdateTime = millis();
}

String Dummy::getValue() {
    return String(randomValue);
}

bool Dummy::shouldUpdate() {
    return (millis() - lastUpdateTime >= updateInterval);
}
