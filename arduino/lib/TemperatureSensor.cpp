#ifndef _TEMPERATURE_SENSOR_
#define _TEMPERATURE_SENSOR_

#include <Arduino.h>

class TemperatureSensor {
  protected:
    byte pin;
    float temperature;

  protected:
    TemperatureSensor(byte pin){
      temperature = 0;
    };

  public:
    virtual void read() = 0;
    virtual float getTemperature() = 0;
};

#endif