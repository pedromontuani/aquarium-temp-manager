#ifndef SCREEN_CONTROLLER
#define SCREEN_CONTROLLER

#include "PeltierGroup.cpp"
#include "TemperatureSensor.cpp"

#include <Arduino.h>
#include <oled.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

class ScreenController {
  private:
    TemperatureSensor *aquariumSensor;
    TemperatureSensor *ambientSensor;
    PeltierGroup *highEnergy;
    PeltierGroup *lowEnergy;
    OLED *oled;

    void init() {
        oled->begin();
        oled->clear();
    };

  public:
    ScreenController(TemperatureSensor *aquariumSensor,
                     TemperatureSensor *ambientSensor,
                     PeltierGroup highEnergy[], PeltierGroup lowEnergy[]) {
        this->aquariumSensor = aquariumSensor;
        this->ambientSensor = ambientSensor;
        this->highEnergy = highEnergy;
        this->lowEnergy = lowEnergy;
        this->oled =
            new OLED(A4, A5, NO_RESET_PIN, 0x3D, SCREEN_WIDTH, SCREEN_HEIGHT);

        init();
    };

    ~ScreenController() { delete oled; }

    void update() {
        oled->clear();

        oled->println(String(String(F("Aq. Temp.: ")) +
                             String(aquariumSensor->getTemperature())));

        oled->println(String(String(F("Ext. Temp.: ")) +
                             String(ambientSensor->getTemperature())));

        oled->println(String(String(F("H.E. Cooler: ")) +
                             String(highEnergy->isActive())));

        oled->println(
            String(String(F("L.E. Cooler: ")) + String(lowEnergy->isActive())));
    }
};

#endif