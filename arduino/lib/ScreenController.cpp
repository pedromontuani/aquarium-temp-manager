#ifndef SCREEN_CONTROLLER
#define SCREEN_CONTROLLER

#include "../config.h"
#include "PeltierGroup.cpp"
#include "TemperatureSensor.cpp"

#include <Arduino.h>
#include <oled.h>

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
        oled->set_contrast(SCREEN_CONSTRAST);
    };

  public:
    ScreenController(TemperatureSensor *aquariumSensor,
                     TemperatureSensor *ambientSensor, PeltierGroup *highEnergy,
                     PeltierGroup *lowEnergy) {
        this->aquariumSensor = aquariumSensor;
        this->ambientSensor = ambientSensor;
        this->highEnergy = highEnergy;
        this->lowEnergy = lowEnergy;
        this->oled = new OLED(SCREEN_SDA, SCREEN_SCL, NO_RESET_PIN,
                              SCREEN_ADDRESS, SCREEN_WIDTH, SCREEN_HEIGHT);

        init();
    };

    ~ScreenController() { delete oled; }

    void update() {
        oled->clear();
        char degree = 0176;
        oled->println(String(F("Aq. Temp.: ")) +
                      String(aquariumSensor->getTemperature()) + degree + "C");
        oled->println();
        oled->println(String(F("Ext. Temp.: ")) +
                      String(ambientSensor->getTemperature()) + degree + "C");
        oled->println();
        oled->println(String(F("H.E. Cooler: ")) +
                      String((highEnergy->isActive() ? "ON" : "OFF")));
        oled->println();
        oled->println(String(F("L.E. Cooler: ")) +
                      String((lowEnergy->isActive() ? "ON" : "OFF")));

        oled->display();
    }
};

#endif