#ifndef RADIO_H
#define RADIO_H

#include <Arduino.h>

class Radio
{
    private:
        int theSerialPort;
    public:
        Radio(int serialPort);
        void init();
};

#endif
