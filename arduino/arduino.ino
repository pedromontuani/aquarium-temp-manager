#include "lib/AmbientTempSensor.cpp"
#include "lib/AquariumManager.cpp"
#include "lib/AquariumSensor.cpp"
#include "lib/PeltierGroup.cpp"
#include "lib/RelayPort.cpp"
#include "lib/ScreenController.cpp"
#include "lib/TemperatureSensor.cpp"
#include "lib/WifiModule.cpp"
#include "lib/EepromManager.cpp"
#include <Arduino.h>
#include <SoftwareSerial.h>

#include "config.h"

TemperatureSensor *aquariumSensor;
AmbientTempSensor *ambientSensor;
AquariumManager *aquariumManager;
PeltierGroup *highEnergyPeltierGroup;
PeltierGroup *lowEnergyPeltierGroup;
WifiModule *wifi;

RelayPort peltierCellsArray_1[3] = {
    RelayPort(PELTIER_01_PIN, PELTIER_POWER_CONSUMPTION),
    RelayPort(PELTIER_02_PIN, PELTIER_POWER_CONSUMPTION),
    RelayPort(PELTIER_03_PIN, PELTIER_POWER_CONSUMPTION)};

RelayPort peltierCellsArray_2[2] = {
    RelayPort(PELTIER_04_PIN, PELTIER_POWER_CONSUMPTION),
    RelayPort(PELTIER_05_PIN, PELTIER_POWER_CONSUMPTION)};

ScreenController *screen;

void setup() {
    Serial.begin(115200);

    if(RESET_ESP) {
       EepromManager::resetEsp();
    }

    wifi = new WifiModule(RX_PIN, TX_PIN, SERIAL_COMMUNICATION_SPEED, F(SSID),
                          F(PASSWORD), F(MAC_ADDRESS));

    highEnergyPeltierGroup = new PeltierGroup(peltierCellsArray_1, 3);
    lowEnergyPeltierGroup = new PeltierGroup(peltierCellsArray_2, 2);

    aquariumSensor = new AquariumSensor(AQUARIUM_SENSOR_PIN);
    ambientSensor = new AmbientTempSensor(AMBIENT_SENSOR_PIN);

    aquariumManager = new AquariumManager(
        highEnergyPeltierGroup, lowEnergyPeltierGroup, aquariumSensor,
        aquariumSensor, GOAL_TEMPERATURE, TOLERANCE);

}

void loop() {
    handleSensors();
    aquariumManager->update();
    
    handleScreen();
    handleWifi();

    delay(UPDATE_FREQUENCY);
}

void handleScreen() {
    screen =
        new ScreenController(aquariumSensor, ambientSensor,
                             highEnergyPeltierGroup, lowEnergyPeltierGroup);
    screen->update();
    delete screen;
}

void handleWifi() {
    wifi->sendReport(highEnergyPeltierGroup, lowEnergyPeltierGroup,
                     aquariumSensor, ambientSensor, aquariumManager);
}

void handleSensors() {
    aquariumSensor->read();
    ambientSensor->read();
}