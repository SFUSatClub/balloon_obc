#include <Arduino.h>
#include "GPS.h"

bool usingInterrupt = false;
uint32_t timer = millis();

GPS::GPS()
{
    GPS = new Adafruit_GPS(&gpsSerial);
    longitude = 0;
    latitude = 0;
}

void GPS::init()
{
    GPS->begin(9600);

    // Turn on RMC (recommended minimum) and GGA (fix data) including altitude
    GPS->sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
    // Set the update rate
    GPS->sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
    // Request updates on antenna status, comment out to keep quiet
    GPS->sendCommand(PGCMD_ANTENNA);
}

void GPS::useInterrupt(bool v)
{
    if (v)
    {
        // Timer0 is already used for millis() - we'll just interrupt somewhere
        // in the middle and call the "Compare A" function above
        OCR0A = 0xAF;
        TIMSK0 |= _BV(OCIE0A);
        usingInterrupt = true;
    }
    else
    {
        // do not call the interrupt function COMPA anymore
        TIMSK0 &= ~_BV(OCIE0A);
        usingInterrupt = false;
    }
}

void GPS::getVersion()
{
    // Ask for firmware version
    gpsSerial.println(PMTK_Q_RELEASE);
}

char GPS::read()
{
    return GPS->read();
}

void GPS::tick()
{
    if (!usingInterrupt)
    {
        char c = GPS->read();
        if (GPSECHO)
            if (c) Serial.print(c);
    }

    if (GPS->newNMEAreceived())
    {
        if (!GPS->parse(GPS->lastNMEA()))   // this also sets the newNMEAreceived() flag to false
        return;  // we can fail to parse a sentence in which case we should just wait for another
    }

    if (timer > millis()) timer = millis();

    // approximately every 2 seconds or so, print out the current stats
    if (millis() - timer > 2000)
    {
        timer = millis(); // reset the timer

        GPS->longitudeDegrees = longitude;
        GPS->latitudeDegrees = latitude;

        // This will all be removed after we finish debugging with USB logger
        Serial.print("\nTime: ");
        Serial.print(GPS->hour, DEC); Serial.print(':');
        Serial.print(GPS->minute, DEC); Serial.print(':');
        Serial.print(GPS->seconds, DEC); Serial.print('.');
        Serial.println(GPS->milliseconds);
        Serial.print("Date: ");
        Serial.print(GPS->day, DEC); Serial.print('/');
        Serial.print(GPS->month, DEC); Serial.print("/20");
        Serial.println(GPS->year, DEC);
        Serial.print("Fix: "); Serial.print((int)GPS->fix);
        Serial.print(" quality: "); Serial.println((int)GPS->fixquality);
        if (GPS->fix)
        {
            Serial.print("Location: ");
            Serial.print(GPS->latitude, 4); Serial.print(GPS->lat);
            Serial.print(", ");
            Serial.print(GPS->longitude, 4); Serial.println(GPS->lon);
            Serial.print("Location (in degrees, works with Google Maps): ");
            Serial.print(GPS->latitudeDegrees, 4);
            Serial.print(", ");
            Serial.println(GPS->longitudeDegrees, 4);

            Serial.print("Speed (knots): "); Serial.println(GPS->speed);
            Serial.print("Angle: "); Serial.println(GPS->angle);
            Serial.print("Altitude: "); Serial.println(GPS->altitude);
            Serial.print("Satellites: "); Serial.println((int)GPS->satellites);
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
    Serial.print(GPS->latitudeDegrees, 4);
    Serial.print(", ");
    Serial.println(GPS->longitudeDegrees, 4);
}
