#ifndef GPS_H
#define GPS_H

#include <Arduino.h>
#include <inttypes.h>

class GPS
{
    private:
        String position;
        float longitude;
        float latitude;
        uint8_t hours, minutes, seconds;
        uint16_t milliseconds;
    public:
        GPS();
        void init();
        void tick();
        float getLongitude();
        float getLatitude();
        void printCoords();
};

#endif
