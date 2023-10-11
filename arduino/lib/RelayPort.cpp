#include "ModuleState.cpp"
#include <Arduino.h>

#ifndef RELAY_PORT
#define RELAY_PORT

class RelayPort : public ModuleState {
  private:
    byte pin;

  public:
    RelayPort(byte pin, float powerConsumption)
        : ModuleState(powerConsumption, false) {
        this->pin = pin;
        pinMode(pin, OUTPUT);
        this->off();
    };

    void on() {
        digitalWrite(pin, LOW);
        this->setActive(true);
    };

    void off() {
        digitalWrite(pin, HIGH);
        this->setActive(false);
    }
};

#endif