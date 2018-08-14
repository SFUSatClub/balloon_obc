
#ifndef SDcard_H
#define SDcard_H

#include "libraries/SD-master/source/SD.h"
#include "libraries/SPI-master/SPI.h"

class SDcard
{
  private:
      int CS_PIN;
      File *file;
  public:
      SDcard();
      void init();
      //void initializeSD();
      int createFile(char filename[]);
      int writeToFile(char text[]);
      void closeFile();
      int openFile(char filename[]);
      String readLine();


};

#endif
