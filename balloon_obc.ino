/**
 * Arduino program to read GPS, temperature, and humidity sensor data,
 *      and broadcast the GPS data to the radio while also storing all
 *      data to an external SD card.
 *
 **
 * Includes
 **************************************************/

#include <SoftwareSerial.h>
#include <Wire.h>
#include <inttypes.h>
#include <SD.h>
#include <SPI.h>

#include "src/Computing/GPS.h"
#include "src/Computing/HTU.h"
#include "src/Computing/TempSensor.h"

/**
 * Defines
 **************************************************/

#define BAUD_ARDUINO 115200
#define BAUD_UNKNOWN 9600 //TODO: what is this the baud rate for

#define OUTPUT_FILENAME "

#define PIN_CS 53

#define DELAY_1S 1000
#define DELAY_3S 3000

// TODO: remove dead code
//#include <SD.h>
//#include <SPI.h>
//int CS_PIN = 53;
//File file;

/**
 * Variable declares
 * //TODO: make static
 **************************************************/

File myFile;
GPS gps;
HTU htu;
TempSensor lm75;

void setup() {

        //Serial.begin(115200); // TODO: dead code
        Serial.begin(BAUD_ARDUINO); // set baud rate

        /**
         * GPS initialization
         * TODO: should probably put all these into its own init
         **************************************************/

        gps.init();
        gps.useInterrupt(true);
        delay(DELAY_1S);
        gps.getVersion();

        /**
         * HTU and Temperature sensor init
         **************************************************/

        htu.init();
        lm75.init();

        //Serial.begin(9600);

        //  initializeSD();
        //  createFile("testing1.txt");
        //  writeToFile("Fucking SD card");
        //  closeFile();
        //  openFile("testing1.txt");
        //  Serial.println(readLine());
        //  Serial.println(readLine());
        //  closeFile();

        Serial.begin(BAUD_UNKNOWN);
        pinMode(PIN_CS, OUTPUT);

        /**
         * SD Card Initialization
         **************************************************/

        if (SD.begin()) {
                Serial.println("SD card is ready to use.");
        } else {
                Serial.println("SD card initialization failed");
                return;
        }

        //  // Create/Open file
        //  myFile = SD.open("test.txt", FILE_WRITE);
        //
        //  // if the file opened okay, write to it:
        //  if (myFile) {
        //    Serial.println("Writing to file...");
        //    // Write to file
        //    myFile.println("Testing text 1, 2 ,3...");
        //    myFile.close(); // close the file
        //    Serial.println("Done.");
        //  }
        //  // if the file didn't open, print an error:
        //  else {
        //    Serial.println("error opening test.txt");
        //  }
        //  // Reading the file
        //  myFile = SD.open("test.txt");
        //  if (myFile) {
        //    Serial.println("Read:");
        //    // Reading the whole file
        //    while (myFile.available()) {
        //      Serial.write(myFile.read());
        //   }
        //    myFile.close();
        //  }
        //  else {
        //    Serial.println("error opening test.txt");
        //  }

}

/**
 * Interrupt is called once a millisecond, looks for any new GPS data, and stores it
 **************************************************/
SIGNAL(TIMER0_COMPA_vect)
{
        char c = gps.read();
        // if you want to debug, this is a good time to do it!

#ifdef UDR0
        if (GPSECHO && c) // TODO: if (c)
                UDR0 = c;

        // writing direct to UDR0 is much much faster than Serial.print
        //      but only one character can be written at a time.
#endif
}



void loop()
{
        /**
         * GPS data
         **************************************************/

        Serial.print("\nGPS: ");

        gps.tick();
        gps.printCoords();
        delay(DELAY_3S);

        /**
         * Temperature and Humidity
         **************************************************/

        Serial.print("\nHumid and Temp: \n");

        htu.getWeather();
        htu.printInfo();
        delay(DELAY_3S);

        Serial.print("\nLM75 Temp: \n");

        lm75.tick();
        delay(DELAY_3S);

        /**
         * Write data to file
         **************************************************/

        // Create/Open file
        myFile = SD.open("test.txt", FILE_WRITE);

        // If the file opened okay, write to it:
        // If the file didn't open, print an error:
        if (myFile) {
                Serial.println("Writing to file...");
                myFile.println(lm75.tempValue()); // Write to file
                myFile.close();                   // Close the file
                Serial.println("Done.");
        }
        else {
                Serial.println("error opening test.txt");
        }

        /**
         * Read file (TODO: TESTING)
         **************************************************/

        Serial.print("NOW READING FILE -----");
        myFile = SD.open("test.txt");

        if (myFile) {

                Serial.println("Read:");

                while (myFile.available()) { // Reading the whole file
                        Serial.write(myFile.read());
                }

                myFile.close();

        } else {

                Serial.println("error opening test.txt");
        }

        Serial.print("DONE READING FILE -----");
}

File createFile()
{

        // Try and append
        File f = SD.open("file.txt", O_RDWR | O_APPEND);
        if (!f) {
                // It failed, so try and make a new file.
                f = SD.open("file.txt", O_RDWR | O_CREAT);
                if (!f) {
                        // It failed too, so give up.
                        Serial.println("Failed to open file.txt");
                }
        }
}

void writeToFile()
{
        // Only write to the file if the file is actually open.
        if (f) {
                f.print(/* your data here */)
                        f.close();
        }
}

//SD Card function Definitions...
//void initializeSD()
//{
//  Serial.println("Initializing SD card...");
//  pinMode(CS_PIN, OUTPUT);
//
//  if (SD.begin())
//  {
//    Serial.println("SD card is ready to use.");
//  } else
//  {
//    Serial.println("SD card initialization failed");
//    return;
//  }
//}
//
//int createFile(char filename[])
//{
//  file = SD.open(filename, FILE_WRITE);
//
//  if (file)
//  {
//    Serial.println("File created successfully.");
//    return 1;
//  } else
//  {
//    Serial.println("Error while creating file.");
//    return 0;
//  }
//}
//
//int writeToFile(char text[])
//{
//  if (file)
//  {
//    file.println(text);
//    Serial.println("Writing to file: ");
//    Serial.println(text);
//    return 1;
//  } else
//  {
//    Serial.println("Couldn't write to file");
//    return 0;
//  }
//}
//
//void closeFile()
//{
//  if (file)
//  {
//    file.close();
//    Serial.println("File closed");
//  }
//}
//
//int openFile(char filename[])
//{
//  file = SD.open(filename);
//  if (file)
//  {
//    Serial.println("File opened with success!");
//    return 1;
//  } else
//  {
//    Serial.println("Error opening file...");
//    return 0;
//  }
//}
//
//String readLine()
//{
//  String received = "";
//  char ch;
//  while (file.available())
//  {
//    ch = file.read();
//    if (ch == '\n')
//    {
//      return String(received);
//    }
//    else
//    {
//      received += ch;
//    }
//  }
//  return "";
//}
