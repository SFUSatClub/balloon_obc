#ifndef GPS_H
#define GPS_H

#include <inttypes.h>

class GPS
{
    private:
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
