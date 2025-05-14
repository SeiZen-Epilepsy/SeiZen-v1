#ifndef OLED_H
#define OLED_H

#include <Arduino.h>

class OLED {
    public:
        OLED();
        void begin();
        void clear();
        void display();
        void printTest();
    private:
    // no private
};

#endif