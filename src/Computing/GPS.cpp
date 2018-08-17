#include <Arduino.h>
#include "GPS.h"

GPS::GPS()
{
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

        // This is a stub. Include code to read GPS coordinates from the TNC
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
