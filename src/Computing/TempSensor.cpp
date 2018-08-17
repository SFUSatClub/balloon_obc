#include <Arduino.h>
#include "TempSensor.h"

TempSensor::TempSensor()
{
        termo = new TempI2C_LM75(0x48,TempI2C_LM75::nine_bits);
}

void TempSensor::init()
{
        Serial.begin(9600);

        /* All this stuff was in the original file but I assume we only need
         * to have one of each setting set. I will leave them in here for now
         * anyways.
         */

        // Set Resolution to 10 bits
        termo->setResolution(TempI2C_LM75::ten_bits);
        delay(2000);

        // Set Resolution to 11 bits
        termo->setResolution(TempI2C_LM75::eleven_bits);
        delay(2000);

        // Set Resolution to 12 bits
        termo->setResolution(TempI2C_LM75::twelve_bits);
        delay(2000);


        // Set Resolution to 9 bits
        termo->setResolution(TempI2C_LM75::nine_bits);
        delay(2000);

        // Set initial thermostat range
        termo->setTHyst(25);
        termo->setTOS(30);

        termo->setTermostatMode(TempI2C_LM75::interrupt_mode);
        termo->setTermostatMode(TempI2C_LM75::comparator_mode);

        // Set fault tolerance to four samples
        termo->setTermostatFaultTolerance(TempI2C_LM75::four_samples);

        // Set fault tolerance to one sample
        termo->setTermostatFaultTolerance(TempI2C_LM75::one_samples);

        // Set OS polarity to active high
        termo->setOSPolarity(TempI2C_LM75::active_high);

        // Set OS polarity to active low
        termo->setOSPolarity(TempI2C_LM75::active_low);
}

void TempSensor::tick()
{
        Serial.print(termo->getTemp());
        Serial.println(" oC");
}

float TempSensor::getTemp()
{
        return termo->getTemp();
}


/* TODO: remove dead code
String TempSensor::tempValue()
{
        String value;
        value = termo->getTemp();
        return value;
}
*/


