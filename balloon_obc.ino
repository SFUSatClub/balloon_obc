
//ADA GPS PARSING STARTS HERE
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

Adafruit_GPS GPS(&Serial2);

// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences. 
#define GPSECHO  false

// this keeps track of whether we're using the interrupt
// off by default!
boolean usingInterrupt = false;
void useInterrupt(boolean); // Func prototype keeps Arduino 0023 happy

//ADA GPS PARSING ENDS HERE







//HUMIDITY N TEMP STARTS HERE
#include <SparkFunHTU21D.h>
#include "SparkFun_Si7021_Breakout_Library.h"
#include <Wire.h>

float humidity = 0;
float temp = 0;


int power = A3;
int GND = A2;

//Create Instance of HTU21D or SI7021 temp and humidity sensor and MPL3115A2 barrometric sensor
Weather sensor;
//HUMIDITY N TEMP ENDS HERE




//Balloon, LM75 sensor starts here
#define VERSION "1.1"

#include <inttypes.h>
#include <Wire.h>
#include <lm75.h>


TempI2C_LM75 termo = TempI2C_LM75(0x48,TempI2C_LM75::nine_bits);
//Balloon, LM75 sensor ends here


//GLOBAL ENDS HERE--------------------------------------------------


void setup() {
  // put your setup code here, to run once:


//ADA GPS PARSING STARTS HERE
   
  // connect at 115200 so we can read the GPS fast enough and echo without dropping chars
  // also spit it out
  Serial.begin(115200);
  Serial.println("Adafruit GPS library basic test!");

  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);
  
  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time
  
  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz

  // Request updates on antenna status, comment out to keep quiet
  GPS.sendCommand(PGCMD_ANTENNA);

  // the nice thing about this code is you can have a timer0 interrupt go off
  // every 1 millisecond, and read data from the GPS for you. that makes the
  // loop code a heck of a lot easier!
  useInterrupt(true);

  delay(1000);
  // Ask for firmware version
  Serial2.println(PMTK_Q_RELEASE);
//ADA GPS PARSING ENDS HERE


//HUMIDITY N TEMP STARTS HERE
Serial.begin(57600);   // open serial over USB at 9600 baud

    pinMode(power, OUTPUT);
    pinMode(GND, OUTPUT);

    digitalWrite(power, HIGH);
    digitalWrite(GND, LOW);

    //Initialize the I2C sensors and ping them
    sensor.begin();
//HUMIDITY N TEMP ENDS HERE


//Balloon, LM75 sensor starts here
Serial.begin(9600);
    Serial.println("Start");

    Serial.print("Actual temp ");
    Serial.print(termo.getTemp());
    Serial.println(" oC");

    Serial.print("Set resolution to ten bits ");
    termo.setResolution(TempI2C_LM75::ten_bits);
    delay(2000);

    Serial.print("Actual temp ");
    Serial.print(termo.getTemp());
    Serial.println(" oC");

    Serial.print("Set resolution to eleven bits ");
    termo.setResolution(TempI2C_LM75::eleven_bits);
    delay(2000);

    Serial.print("Actual temp ");
    Serial.print(termo.getTemp());
    Serial.println(" oC");

    Serial.print("Set resolution to twelve bits ");
    termo.setResolution(TempI2C_LM75::twelve_bits);
    delay(2000);

    Serial.print("Actual temp ");
    Serial.print(termo.getTemp());
    Serial.println(" oC");

    Serial.print("Set resolution to nine bits ");
    termo.setResolution(TempI2C_LM75::nine_bits);
    delay(2000);

    Serial.print("Actual temp ");
    Serial.print(termo.getTemp());
    Serial.println(" oC");

    Serial.print("Initial termostat range [");

    Serial.print("THyst = ");
    Serial.print(termo.getTHyst());
    Serial.print(" oC  TOS = ");
    Serial.print(termo.getTOS());
    Serial.println(" oC]");

    Serial.print("Set THyst to 25 oC [");
    termo.setTHyst(25);

    Serial.print("THyst = ");
    Serial.print(termo.getTHyst());
    Serial.print(" oC TOS = ");
    Serial.print(termo.getTOS());
    Serial.println(" oC]");

    Serial.print("Set TOS to 30 oC [");
    termo.setTOS(30);

    Serial.print("THyst = ");
    Serial.print(termo.getTHyst());
    Serial.print(" oC TOS = ");
    Serial.print(termo.getTOS());
    Serial.println(" oC]");

    Serial.print("Actual Termostat mode = ");
    Serial.println(termo.getTermostatMode());

    Serial.print("Set to interrumpt mode = ");
    termo.setTermostatMode(TempI2C_LM75::interrupt_mode);
    Serial.println(termo.getTermostatMode());

    Serial.print("Turn to comparation mode = ");
    termo.setTermostatMode(TempI2C_LM75::comparator_mode);
    Serial.println(termo.getTermostatMode());


    Serial.print("Actual Termostat Fault tolerance = ");
    Serial.println(termo.getTermostatFaultTolerance());

    Serial.print("Set Fault tolerance to  four samples = ");
    termo.setTermostatFaultTolerance(TempI2C_LM75::four_samples);
    Serial.println(termo.getTermostatFaultTolerance());

    Serial.print("Turn Fault tolerance to one sample = ");
    termo.setTermostatFaultTolerance(TempI2C_LM75::one_samples);
    Serial.println(termo.getTermostatFaultTolerance());


    Serial.print("Actual OS Polarity = ");
    Serial.println(termo.getOSPolarity());

    Serial.print("Set OS Polarity to active High = ");
    termo.setOSPolarity(TempI2C_LM75::active_high);
    Serial.println(termo.getOSPolarity());

    Serial.print("Turn OS Polarity to active low = ");
    termo.setOSPolarity(TempI2C_LM75::active_low);
    Serial.println(termo.getOSPolarity());
//Balloon, LM75 sensor ends here

  

//VOID SETUP ENDS HERE--------------------------------------------------
}






// Interrupt is called once a millisecond, looks for any new GPS data, and stores it
SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
  // if you want to debug, this is a good time to do it!
#ifdef UDR0
  if (GPSECHO)
    if (c) UDR0 = c;  
    // writing direct to UDR0 is much much faster than Serial.print 
    // but only one character can be written at a time. 
#endif
}

void useInterrupt(boolean v) {
  if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}

uint32_t timer = millis();








//HUMIDITY N TEMP FUNCS STARTS HERE
 void getWeather()
{
  // Measure Relative Humidity from the HTU21D or Si7021
  humidity = sensor.getRH();

  // Measure Temperature from the HTU21D or Si7021
  temp = sensor.getTemp();
  // Temperature is measured every time RH is requested.
  // It is faster, therefore, to read it from previous RH
  // measurement with getTemp() instead with readTemp()
}
//---------------------------------------------------------------
void printInfo()
{
//This function prints the weather data out to the default Serial Port

  Serial.print("Temp:");
  Serial.print(temp);
  Serial.print("C, ");

  Serial.print("Humidity:");
  Serial.print(humidity);
  Serial.println("%");
}
//HUMIDITY N TEMP FUNCS ENDS HERE






void loop() {
  // put your main code here, to run repeatedly:

    Serial.print("\nGPS: ");

//ADA GPS PARSING STARTS HERE
 // in case you are not using the interrupt above, you'll
  // need to 'hand query' the GPS, not suggested :(
  if (! usingInterrupt) {
    // read data from the GPS in the 'main loop'
    char c = GPS.read();
    // if you want to debug, this is a good time to do it!
    if (GPSECHO)
      if (c) Serial.print(c);
  }
  
  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences! 
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    //Serial.println(GPS.lastNMEA());   // this also sets the newNMEAreceived() flag to false
  
    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
      return;  // we can fail to parse a sentence in which case we should just wait for another
  }

  // if millis() or timer wraps around, we'll just reset it
  if (timer > millis())  timer = millis();

  // approximately every 2 seconds or so, print out the current stats
  if (millis() - timer > 2000) { 
    timer = millis(); // reset the timer
    
    Serial.print("\nTime: ");
    Serial.print(GPS.hour, DEC); Serial.print(':');
    Serial.print(GPS.minute, DEC); Serial.print(':');
    Serial.print(GPS.seconds, DEC); Serial.print('.');
    Serial.println(GPS.milliseconds);
    Serial.print("Date: ");
    Serial.print(GPS.day, DEC); Serial.print('/');
    Serial.print(GPS.month, DEC); Serial.print("/20");
    Serial.println(GPS.year, DEC);
    Serial.print("Fix: "); Serial.print((int)GPS.fix);
    Serial.print(" quality: "); Serial.println((int)GPS.fixquality); 
    if (GPS.fix) {
      Serial.print("Location: ");
      Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
      Serial.print(", "); 
      Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
      Serial.print("Location (in degrees, works with Google Maps): ");
      Serial.print(GPS.latitudeDegrees, 4);
      Serial.print(", "); 
      Serial.println(GPS.longitudeDegrees, 4);
      
      Serial.print("Speed (knots): "); Serial.println(GPS.speed);
      Serial.print("Angle: "); Serial.println(GPS.angle);
      Serial.print("Altitude: "); Serial.println(GPS.altitude);
      Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
    }
  }
//ADA GPS PARSING ENDS HERE
delay(3000);


 Serial.print("\nImportant Stuff: \n");

Serial.print(GPS.latitudeDegrees, 4);
      Serial.print(", "); 
      Serial.println(GPS.longitudeDegrees, 4);


      
 Serial.print("\nHumid and Temp: \n");


//HUMIDITY N TEMP STARTS HERE
 getWeather();
    printInfo();
 //   delay(1000);
//HUMIDITY N TEMP ENDS HERE
  delay(3000);

 Serial.print("\nLM75 Temp: \n");

//Balloon, LM75 sensor starts here  
  Serial.print(termo.getTemp());
    Serial.println(" oC");
    //delay(5000);
//Balloon, LM75 sensor ends here
delay(3000);


  
//VOID LOOP ENDS HERE--------------------------------------------------
}

//FUNCTION DEFINITIONS STARTS HERE---------------------------------





//FUNCTION DEFINITIONS ENDS HERE---------------------------------


