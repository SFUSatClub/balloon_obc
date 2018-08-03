#include "Radio.h"

Radio::Radio()
{}

void Radio::init()
{
    // Initialize all of the RS-UV3's parameters
    radioSerial.println("CLVA7KSX");
    radioSerial.println("FS146520");


}

// Transmits unmodulated CW signal (morse code)
void Radio::tx(String data)
{
    // Still deciding whether to send CW or MCW
    radioSerial.println("CW" + data);
    //radioSerial.println("CT" + data);
}
