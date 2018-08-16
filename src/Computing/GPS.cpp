#include <Arduino.h>
#include "GPS.h"

bool usingInterrupt = false;
uint32_t timer = millis();

GPS::GPS()
{
    Ada_GPS = new Adafruit_GPS(&gpsSerial);
    longitude = 0;
    latitude = 0;
}

void GPS::init()
{
    Ada_GPS->begin(9600);

    // Turn on RMC (recommended minimum) and GGA (fix data) including altitude
    Ada_GPS->sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
    // Set the update rate
    Ada_GPS->sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);
    // Request updates on antenna status, comment out to keep quiet
    Ada_GPS->sendCommand(PGCMD_ANTENNA);
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
    return Ada_GPS->read();
}

void GPS::tick()
{
    if (!usingInterrupt)
    {
        char c = Ada_GPS->read();
        if (GPSECHO)
            if (c) Serial.print(c);
    }

    if (Ada_GPS->newNMEAreceived())
    {
        if (!Ada_GPS->parse(Ada_GPS->lastNMEA()))   // this also sets the newNMEAreceived() flag to false
        return;  // we can fail to parse a sentence in which case we should just wait for another
    }

    if (timer > millis()) timer = millis();

    // approximately every 2 seconds or so, print out the current stats
    if (millis() - timer > 2000)
    {
        timer = millis(); // reset the timer

        longitude = Ada_GPS->longitudeDegrees;
        latitude = Ada_GPS->latitudeDegrees;

        // This will all be removed after we finish debugging with USB logger
        Serial.print("\nTime: ");
        Serial.print(Ada_GPS->hour, DEC); Serial.print(':');
        Serial.print(Ada_GPS->minute, DEC); Serial.print(':');
        Serial.print(Ada_GPS->seconds, DEC); Serial.print('.');
        Serial.println(Ada_GPS->milliseconds);
        Serial.print("Date: ");
        Serial.print(Ada_GPS->day, DEC); Serial.print('/');
        Serial.print(Ada_GPS->month, DEC); Serial.print("/20");
        Serial.println(Ada_GPS->year, DEC);
        Serial.print("Fix: "); Serial.print((int)Ada_GPS->fix);
        Serial.print(" quality: "); Serial.println((int)Ada_GPS->fixquality);
        if (Ada_GPS->fix)
        {
            Serial.print("Location: ");
            Serial.print(Ada_GPS->latitude, 4); Serial.print(Ada_GPS->lat);
            Serial.print(", ");
            Serial.print(Ada_GPS->longitude, 4); Serial.println(Ada_GPS->lon);
            Serial.print("Location (in degrees, works with Google Maps): ");
            Serial.print(Ada_GPS->latitudeDegrees, 4);
            Serial.print(", ");
            Serial.println(Ada_GPS->longitudeDegrees, 4);

            Serial.print("Speed (knots): "); Serial.println(Ada_GPS->speed);
            Serial.print("Angle: "); Serial.println(Ada_GPS->angle);
            Serial.print("Altitude: "); Serial.println(Ada_GPS->altitude);
            Serial.print("Satellites: "); Serial.println((int)Ada_GPS->satellites);
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
    Serial.print(" ");
    Serial.println(latitude, 4);
}
