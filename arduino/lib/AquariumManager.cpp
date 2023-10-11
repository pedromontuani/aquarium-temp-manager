#include "PeltierGroup.cpp"
#include "RelayPort.cpp"
#include "TemperatureSensor.cpp"
#include <Arduino.h>

class AquariumManager {
  private:
    PeltierGroup *highEnergyPeltierGroup;
    PeltierGroup *lowEnergyPeltierGroup;

    TemperatureSensor *aquariumSensor;
    TemperatureSensor *externalSensor;

    float currentAquariumTemp;
    float currentExternalTemp;
    float goalTemperature;
    float tolerance;

    void handleTemperature() {
        if (currentExternalTemp <= goalTemperature &&
            currentAquariumTemp <= (goalTemperature)) {
            turnOffComponents();
            return;
        }

        if (currentAquariumTemp >= (goalTemperature + tolerance)) {
            turnOnAllGroups();
            return;
        }

        if (currentAquariumTemp >= (goalTemperature - tolerance) &&
            currentAquariumTemp <= goalTemperature) {
            turnOnLowOnly();
            return;
        }

        if (currentAquariumTemp > goalTemperature) {
            turnOnHighOnly();
            return;
        }

        if (currentAquariumTemp <= (goalTemperature - tolerance)) {
            turnOffComponents();
            return;
        }
    }

    void turnOffComponents() {
        highEnergyPeltierGroup->turnOff();
        lowEnergyPeltierGroup->turnOff();
    }

    void turnOnAllGroups() {
        highEnergyPeltierGroup->turnOn();
        lowEnergyPeltierGroup->turnOn();
    }

    void turnOnHighOnly() {
        highEnergyPeltierGroup->turnOn();
        lowEnergyPeltierGroup->turnOff();
    }

    void turnOnLowOnly() {
        highEnergyPeltierGroup->turnOff();
        lowEnergyPeltierGroup->turnOn();
    }

  public:
    AquariumManager(PeltierGroup *highEnergy, PeltierGroup *lowEnergy,
                    TemperatureSensor *aquariumSensor,
                    TemperatureSensor *externalSensor, float goalTemperature,
                    float tolerance) {
        this->highEnergyPeltierGroup = highEnergy;
        this->lowEnergyPeltierGroup = lowEnergy;
        this->aquariumSensor = aquariumSensor;
        this->externalSensor = externalSensor;
        this->goalTemperature = goalTemperature;
        this->tolerance = tolerance;
    };

    void update() {
        currentAquariumTemp = aquariumSensor->getTemperature();
        currentExternalTemp = externalSensor->getTemperature();

        handleTemperature();
    }

    void setGoalTemperature(float goalTemperature) {
        // TODO: implement change of goal temperature
        this->goalTemperature = goalTemperature;
    }
};