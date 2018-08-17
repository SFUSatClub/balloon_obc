/* TNC commands can be found here:
 * http://www.argentdata.com/support/OpenTrackerUSB_manual.pdf
 * RS-UV3 commands here:
 * https://www.hobbypcb.com/files/download/2-rs-uv3/4-rs-uv3-user-manual
 */

#include "Radio.h"

Radio::Radio()
{}

void Radio::init()
{
    // Initialize all of the RS-UV3's and TNC's parameters
    tncSerial.print("\n\n\n");
    delay(500);
    radioSerial.println("FS144390");
    radioSerial.println("VX1");

    tncSerial.print("MYCALL VA7KSX\n");
    delay(50);
    tncSerial.print("POSITION GPS\n");
    delay(50);
    tncSerial.print("ALTITUDE ON\n");
    delay(50);
    tncSerial.print("TXDELAY 150\n");
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
    tncSerial.print("BEACON\n");
    delay(1500);
    // Clear incoming buffers
    while(tncSerial.available())
    {
        tncSerial.read();
    }
}
