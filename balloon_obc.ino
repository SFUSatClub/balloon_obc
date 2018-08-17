#include <SoftwareSerial.h>
#include <Wire.h>
#include <inttypes.h>
#include "src/Computing/GPS.h"
#include "src/Computing/HTU.h"
#include "src/Computing/TempSensor.h"

GPS gps;
HTU htu;
TempSensor lm75;

void setup() {
  
  Serial.begin(115200);

  gps.init();
  delay(1000);
  htu.init();
  lm75.init();
}

void loop() {

  Serial.print("\nGPS: ");

  gps.tick();
  delay(3000);
  gps.printCoords();
  
  Serial.print("\nHumid and Temp: \n");
  
  htu.getWeather();
  htu.printInfo();
  delay(3000);

  Serial.print("\nLM75 Temp: \n");
 
  lm75.tick();
  delay(3000);
}
