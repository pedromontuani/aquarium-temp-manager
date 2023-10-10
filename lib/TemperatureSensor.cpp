#ifndef _TEMPERATURE_SENSOR_
#define _TEMPERATURE_SENSOR_

#include <Arduino.h>

class TemperatureSensor {
  protected:
    byte pin;

  protected:
    TemperatureSensor(byte pin) {};
    
  public:
    virtual float getTemperature() = 0;
};

#endif