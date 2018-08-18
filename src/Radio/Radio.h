#ifndef RADIO_H
#define RADIO_H

#include <Arduino.h>

#define tncSerial Serial
#define radioSerial Serial3

class Radio
{
    public:
        Radio();
        void init();
};

#endif
