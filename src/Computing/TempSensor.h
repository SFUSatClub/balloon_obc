#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H

#include "libraries/lm75/lm75.h"

class TempSensor
{
    private:
        TempI2C_LM75 *termo;
    public:
        TempSensor();
        void init();
        void tick();
        String tempValue();
};

#endif
