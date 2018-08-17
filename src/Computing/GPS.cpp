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

// Reads gps coordinates from the TNC and sets it as the current
// position.
void GPS::tick()
{
    if (timer > millis()) timer = millis();

    // approximately every 2 seconds or so, print out the current stats
    if (millis() - timer > 2000)
    {
        timer = millis(); // reset the timer
        tncSerial.print("POSITION\n");
        delay(50);
        while(tncSerial.available())
        {
            int inChar = Serial.read();
            int temp = 0;
            if (isDigit(inChar) || (char)inChar == '.')
            {
                position += (char)inChar;
            }
            else if ((char)inChar == 'N' || (char)inChar == 'S')
            {
                latitude = position.toFloat();
                temp = latitude;
                latitude = (latitude-100*int(latitude/100))/60.0;
                latitude += int(temp/100);
                if((char)inChar == 'S')
                {
                    latitude = 0 - latitude;
                }
                position = "\0";
            }
            else if ((char)inChar == 'W' || (char)inChar == 'E')
            {
                longitude = position.toFloat();
                temp = longitude;
                longitude = (longitude-100*int(longitude/100))/60.0;
                longitude += int(temp/100);
                if((char)inChar == 'W')
                {
                    longitude = 0 - longitude;
                }
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
