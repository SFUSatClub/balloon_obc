//Testing new SD card module branch

#include <SoftwareSerial.h>
#include <Wire.h>
#include <inttypes.h>
#include "src/Computing/GPS.h"
#include "src/Computing/HTU.h"
#include "src/Computing/TempSensor.h"

#include <SD.h>
#include <SPI.h>
File myFile;
int pinCS = 53;

//#include <SD.h>
//#include <SPI.h>


//int CS_PIN = 53;
//File file;

GPS gps;
HTU htu;
TempSensor lm75;

void setup() {
  
  Serial.begin(115200);

  gps.init();
  gps.useInterrupt(true);
  delay(1000);
  gps.getVersion();
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



 // Create/Open file 
  myFile = SD.open("test.txt", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.println("Writing to file...");
    // Write to file
    myFile.println(lm75.tempValue());
    myFile.close(); // close the file
    Serial.println("Done.");
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening test.txt");
  }
  
  // Reading the file
  Serial.print("NOW READING FILE -----");
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("Read:");
    // Reading the whole file
    while (myFile.available()) {
      Serial.write(myFile.read());
   }
    myFile.close();
  }
  else {
    Serial.println("error opening test.txt");
  }
  Serial.print("DONE READING FILE -----");


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
