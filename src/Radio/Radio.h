#ifndef RADIO_H
#define RADIO_H

#include <Arduino.h>

#define radioSerial Serial3

class Radio
{
    public:
        Radio();
        void init();
        void tx(String data);
};

#endif
