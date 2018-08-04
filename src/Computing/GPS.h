#ifndef GPS_H
#define GPS_H

#include "libraries/Adafruit_GPS/Adafruit_GPS.h"
#define gpsSerial Serial2
#define GPSECHO  false

class GPS
{
    private:
        Adafruit_GPS *GPS;
    public:
        GPS();
        void init();
        void useInterrupt(bool v);
        void getVersion();
        char read();
        void tick();
        void getCoords();
};

#endif
