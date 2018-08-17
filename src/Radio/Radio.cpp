#include "Radio.h"

Radio::Radio()
{}

void Radio::init()
{
    // Initialize all of the RS-UV3's and TNC's parameters
    tncSerial.print("\n\n\n");
    delay(500);
    radioSerial.println("FS144390");
    tncSerial.print("MYCALL VA7KSX\n");
    delay(50);
    tncSerial.print("POSITION GPS\n");
    delay(50);
    tncSerial.print("ALTITUDE ON\n");
    delay(50);

    // Clear incoming buffers
    while(tncSerial.available())
    {
        tncSerial.read();
    }
}

// Transmits APRS packet
void Radio::txPacket()
{
    // Enables Radio's TX, gives time to stabilize, sends beacon, gives time
    // for beacon to finish, then disable's Radio's TX
    // Test these delays for the lowest value needed for reliable transmission
    radioSerial.println("TX1");
    delay(500);
    tncSerial.print("BEACON\n");
    delay(1500);
    radioSerial.println("TX0");
    delay(50);

    // Clear incoming buffers
    while(tncSerial.available())
    {
        tncSerial.read();
    }
}
