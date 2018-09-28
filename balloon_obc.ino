/*
 *  Arduino Temperature Data Logging
 *
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 */

#include <SD.h>
#include <SPI.h>
#include "SparkFun_Si7021_Breakout_Library.h"
#include <Wire.h>

#include "src/Computing/HTU.h"

#define pinCS 53 // Pin 10 on Arduino Uno

#define DELAY_1S 1000
#define DELAY_3S 3000

//#include <DS3231.h>

File myFile;
//DS3231  rtc(SDA, SCL);

HTU htu;



//float humidity = 0;
//float temp = 0;


//Create Instance of HTU21D or SI7021 temp and humidity sensor and MPL3115A2 barrometric sensor
//Weather sensor;

void setup() {

htu.init();
//************************
  //  Serial.begin(57600);   // open serial over USB at 9600 baud for HTU

   /*
    pinMode(power, OUTPUT);
    pinMode(GND, OUTPUT);

    digitalWrite(power, HIGH);
    digitalWrite(GND, LOW);
    */

    //Initialize the I2C sensors and ping them

  //  sensor.begin(); already in htu.init


    //***********************

  Serial.begin(9600);
  pinMode(pinCS, OUTPUT);

  // SD Card Initialization
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
 // rtc.begin();
}
void loop() {
  /*
  Serial.print(rtc.getTimeStr());
  Serial.print(",");
  Serial.println(int(rtc.getTemp()));
  */
      //getWeather();

  Serial.print(htu.get_HTU_Humidity());
  Serial.print(",");
  Serial.println(htu.get_HTU_Temperature());




  myFile = SD.open("SeptTest2.txt", FILE_WRITE);
  if (myFile) {
    myFile.print(htu.get_HTU_Humidity());
    myFile.print(",");
    myFile.println(htu.get_HTU_Temperature());
    myFile.close(); // close the file
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening test.txt");
  }
  delay(DELAY_3S);
}

//---------------------------------------------------------------


//---------------------------------------------------------------
