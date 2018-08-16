#include <SoftwareSerial.h>
#include <Wire.h>
#include <inttypes.h>
#include "src/Computing/GPS.h"
#include "src/Computing/HTU.h"
#include "src/Computing/TempSensor.h"
#include "src/Radio/Radio.h"

GPS gps;
HTU htu;
TempSensor lm75;
Radio radio;

String coords;

void setup() {
  
  Serial.begin(115200);

  gps.init();
  gps.useInterrupt(true);
  delay(1000);
  gps.getVersion();
  htu.init();
  lm75.init();
  coords = "\0";
}

// Interrupt is called once a millisecond, looks for any new GPS data, and stores it
SIGNAL(TIMER0_COMPA_vect) {
  char c = gps.read();
  // if you want to debug, this is a good time to do it!
  #ifdef UDR0
    if (GPSECHO)
      if (c) UDR0 = c;  
      // writing direct to UDR0 is much much faster than Serial.print 
      // but only one character can be written at a time. 
  #endif
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

  coords = (String)gps.getLatitude() + " ";
  coords = coords + (String)gps.getLongitude();
  radio.tx(coords);
  delay(8000);
}
