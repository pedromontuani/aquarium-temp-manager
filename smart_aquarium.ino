#include "lib/AmbientTempSensor.cpp"
#include "lib/AquariumManager.cpp"
#include "lib/AquariumSensor.cpp"
#include "lib/PeltierGroup.cpp"
#include "lib/RelayPort.cpp"
#include "lib/ScreenController.cpp"
#include "lib/TemperatureSensor.cpp"
#include "lib/WifiModule.cpp"
#include <Arduino.h>
#include <SoftwareSerial.h>

#define RX_PIN 4
#define TX_PIN 3
#define AQUARIUM_SENSOR_PIN 2
#define AMBIENT_SENSOR_PIN A0

#define PELTIER_01_PIN 5
#define PELTIER_02_PIN 6
#define PELTIER_03_PIN 7
#define PELTIER_04_PIN 8
#define PELTIER_05_PIN 9
#define WATER_PUMP_1_PIN 10
#define WATER_PUMP_2_PIN 11
#define PELTIER_POWER_CONSUMPTION 72

#define SERIAL_COMMUNICATION_SPEED 9600
#define SSID "Pedro"
#define PASSWORD "minhasenha"

#define GOAL_TEMPERATURE 19
#define TOLERANCE 0.3
#define UPDATE_FREQUENCY 5000

#define TEMPERATURE_PRECISION 11

#define INTERVAL = 60000

WifiModule *wifiModule;
TemperatureSensor *aquariumSensor;
AmbientTempSensor *ambientSensor;
AquariumManager *aquariumManager;
ScreenController *screenController;
PeltierGroup *highEnergyPeltierGroup;
PeltierGroup *lowEnergyPeltierGroup;

RelayPort peltierCellsArray_1[4] = {
    RelayPort(PELTIER_01_PIN, PELTIER_POWER_CONSUMPTION),
    RelayPort(PELTIER_02_PIN, PELTIER_POWER_CONSUMPTION),
    RelayPort(PELTIER_03_PIN, PELTIER_POWER_CONSUMPTION),
    RelayPort(WATER_PUMP_1_PIN, 0.5)};

RelayPort peltierCellsArray_2[3] = {
    RelayPort(PELTIER_04_PIN, PELTIER_POWER_CONSUMPTION),
    RelayPort(PELTIER_05_PIN, PELTIER_POWER_CONSUMPTION),
    RelayPort(WATER_PUMP_2_PIN, 0.5)};

void setup() {
    Serial.begin(115200);
    wifiModule = new WifiModule(RX_PIN, TX_PIN, SERIAL_COMMUNICATION_SPEED,
                                F(SSID), F(PASSWORD));

    highEnergyPeltierGroup =
        new PeltierGroup(peltierCellsArray_1, 4);
    lowEnergyPeltierGroup =
        new PeltierGroup(peltierCellsArray_2, 3);

    aquariumSensor = new AquariumSensor(AQUARIUM_SENSOR_PIN);
    ambientSensor = new AmbientTempSensor(AMBIENT_SENSOR_PIN);

    aquariumManager = new AquariumManager(
        highEnergyPeltierGroup, lowEnergyPeltierGroup, aquariumSensor,
        ambientSensor, GOAL_TEMPERATURE, TOLERANCE);

    screenController = new ScreenController(aquariumSensor, ambientSensor,
                                            highEnergyPeltierGroup,
                                            lowEnergyPeltierGroup);
}

void loop() {

    aquariumManager->update();
    screenController->update();
    wifiModule->sendReport(highEnergyPeltierGroup, lowEnergyPeltierGroup,
                           aquariumSensor, ambientSensor);

    delay(10000);
}
