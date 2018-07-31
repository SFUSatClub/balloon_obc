#include "Radio.h"

Radio::Radio(int serialPort)
{
    theSerialPort = serialPort;
}

void Radio::init()
{
    // Initialize all of the RS-UV3's parameters
    Serial1.println("CLVA7KSX");
}
