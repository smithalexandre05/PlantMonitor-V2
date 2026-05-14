#ifndef SHT40_SENSOR_H
#define SHT40_SENSOR_H

#include <Arduino.h>

struct SHTReading
{
  float SHTTemp;
  float SHTHum;
  bool SHTValid = false;
};

SHTReading readSHT40();
void initSHT40();

#endif