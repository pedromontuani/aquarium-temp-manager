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
        
        oled->print(String(F("Aq. Temp.: ")) +
                      String(aquariumSensor->getTemperature()));
        oled->print((char)133);
        oled->println("C");

        oled->println();
        oled->print(String(F("Ext. Temp.: ")) +
                      String(ambientSensor->getTemperature()));
        oled->print((char)133);
        oled->println("C");
        
        oled->println();
        oled->println(String(F("H.E. Cooler: ")) +
                      String((highEnergy->isActive() ? F("ON") : F("OFF"))));
        oled->println();
        oled->println(String(F("L.E. Cooler: ")) +
                      String((lowEnergy->isActive() ? F("ON") : F("OFF"))));

        oled->display();
    }
};

#endif