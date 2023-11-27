#ifndef SCREEN_CONTROLLER
#define SCREEN_CONTROLLER

#include "../config.h"
#include "PeltierGroup.cpp"
#include "TemperatureSensor.cpp"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

class ScreenController {
  private:
    TemperatureSensor *aquariumSensor;
    TemperatureSensor *ambientSensor;
    PeltierGroup *highEnergy;
    PeltierGroup *lowEnergy;
    Adafruit_SSD1306 *oled;

    void init() {
        oled->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
        oled->clearDisplay();
        oled->ssd1306_command(SSD1306_SETCONTRAST);
        oled->ssd1306_command(SCREEN_CONTRAST);

        oled->setTextSize(1);
        oled->setTextColor(SSD1306_WHITE);
        oled->cp437(true);
    };

  public:
    ScreenController(TemperatureSensor *aquariumSensor,
                     TemperatureSensor *ambientSensor, PeltierGroup *highEnergy,
                     PeltierGroup *lowEnergy) {
        this->aquariumSensor = aquariumSensor;
        this->ambientSensor = ambientSensor;
        this->highEnergy = highEnergy;
        this->lowEnergy = lowEnergy;
        this->oled = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire,
                                          OLED_RESET);

        init();
    };

    ~ScreenController() { delete oled; }

    void update() {
        oled->clearDisplay();
        oled->setCursor(0, 0);

        oled->print(String("Aq. Temp.: ") +
                    String(aquariumSensor->getTemperature()));
        oled->println(" C");

        oled->println();
        oled->print(String("Ext. Temp.: ") +
                    String(ambientSensor->getTemperature()));
        oled->println(" C");

        oled->println();
        oled->println(String("H.E. Cooler: ") +
                      String((highEnergy->isActive() ? "ON" : "OFF")));
        oled->println();
        oled->println(String("L.E. Cooler: ") +
                      String((lowEnergy->isActive() ? "ON" : "OFF")));

        oled->display();
    }
};

#endif