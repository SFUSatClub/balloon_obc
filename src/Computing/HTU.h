#ifndef HTU_H
#define HTU_H

#include "libraries/SparkFunHTU21D/SparkFunHTU21D.h"
#include "libraries/Si7021/SparkFun_Si7021_Breakout_Library.h"

class HTU
{
    private:
        float humidity;
        float temp;
        Weather *sensor;

    public:
        HTU();
        void init();
        void getWeather();
        void printInfo();
        float getTemp();
        float getHumidity();
};

#endif
