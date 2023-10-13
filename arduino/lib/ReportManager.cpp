#ifndef REPORT_MANAGER_CPP
#define REPORT_MANAGER_CPP

#include "ModuleState.cpp"
#include "PeltierGroup.cpp"
#include "TemperatureSensor.cpp"
#include "WifiModule.cpp"

class ReportManager {
  private:
    PeltierGroup *highEnergyPeltierGroup;
    PeltierGroup *lowEnergyPeltierGroup;
    TemperatureSensor *aquariumSensor;
    TemperatureSensor *externalSensor;

  public:
    ReportManager(PeltierGroup *highEnergy, PeltierGroup *lowEnergy,
                  TemperatureSensor *aquariumSensor,
                  TemperatureSensor *externalSensor) {
        this->highEnergyPeltierGroup = highEnergy;
        this->lowEnergyPeltierGroup = lowEnergy;
        this->aquariumSensor = aquariumSensor;
        this->externalSensor = externalSensor;
    }

    String toJson() {
        String json =
            "{\"temp\":{\"aq\":" + String(aquariumSensor->getTemperature()) +
            ",\"ext\":" + String(externalSensor->getTemperature()) +
            "},\"he\":{\"on\":" + String(highEnergyPeltierGroup->isActive()) +
            ",\"pw\":" +
            String(highEnergyPeltierGroup->getCurrentConsumption()) +
            "},\"le\":{\"on\":" + String(highEnergyPeltierGroup->isActive()) +
            ",\"pw\":" +
            String(highEnergyPeltierGroup->getCurrentConsumption()) + "}}";

        return json;
    }
};

#endif
