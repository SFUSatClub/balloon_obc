#ifndef GPS_H
#define GPS_H

#include "libraries/Adafruit_GPS/Adafruit_GPS.h"
#define gpsSerial Serial2
#define GPSECHO false

class GPS
{
    private:
        Adafruit_GPS *Ada_GPS;
        float longitude;
        float latitude;
        uint8_t hours, minutes, seconds;
        uint16_t milliseconds;
    public:
        GPS();
        void init();
        void useInterrupt(bool v);
        void getVersion();
        char read();
        void tick();
        float getLongitude();
        float getLatitude();
        void printCoords();
};

#endif
