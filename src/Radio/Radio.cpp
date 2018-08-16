#include "Radio.h"

Radio::Radio()
{}

void Radio::init()
{
    // Initialize all of the RS-UV3's parameters
    radioSerial.println("CLVA7KSX");
    radioSerial.println("FS146520");
    radioSerial.println("CS25");
}

// Transmits unmodulated CW signal (morse code)
void Radio::tx(String data)
{
    radioSerial.println("CW" + data);
}
