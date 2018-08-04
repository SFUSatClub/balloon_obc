#include <Arduino.h>
#include "HTU.h"

HTU::HTU()
{
    humidity = 0;
    temp = 0;
    sensor = new Weather;
}

void HTU::init()
{
    Serial.begin(57600);   // open serial over USB at 9600 baud
    sensor->begin();
}

void HTU::getWeather()
{
    // Measure Relative Humidity from the HTU21D or Si7021
    humidity = sensor->getRH();

    // Measure Temperature from the HTU21D or Si7021
    temp = sensor->getTemp();
}

void HTU::printInfo()
{
    Serial.print("Temp:");
    Serial.print(temp);
    Serial.print("C, ");

    Serial.print("Humidity:");
    Serial.print(humidity);
    Serial.println("%");
}
