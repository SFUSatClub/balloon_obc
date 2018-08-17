#include "GPS.h"
#include "../Radio/Radio.h"

int timer = 0;

GPS::GPS()
{
    position = "\0";
    longitude = 0;
    latitude = 0;
}

void GPS::init()
{

}

void GPS::tick()
{
    if (timer > millis()) timer = millis();

    // approximately every 2 seconds or so, print out the current stats
    if (millis() - timer > 2000)
    {
        timer = millis(); // reset the timer

        // This reads gps coordinates from the TNC and sets it as the current
        // position. This is in DMS format, will later add conversion to DD
        // format (for google maps purposes)
        tncSerial.print("POSITION\n");
        delay(50);
        while(tncSerial.available())
        {
            int inChar = Serial.read();
            if (isDigit(inChar) || (char)inChar == '.')
            {
                position += (char)inChar;
            }
            else if ((char)inChar == 'N')
            {
                latitude = position.toFloat();
                position = "\0";
            }
            else if ((char)inChar == 'W')
            {
                longitude = position.toFloat();
                position = "\0";
            }

        }
    }
}

float GPS::getLongitude()
{
    return longitude;
}
float GPS::getLatitude()
{
    return latitude;
}

void GPS::printCoords()
{
    Serial.print("\nImportant Stuff: \n");
    Serial.print(longitude, 4);
    Serial.print(", ");
    Serial.println(latitude, 4);
}
