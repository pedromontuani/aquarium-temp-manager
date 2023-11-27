#ifndef REPORT_MANAGER_CPP
#define REPORT_MANAGER_CPP

#include "AquariumManager.cpp"
#include "ModuleState.cpp"
#include "PeltierGroup.cpp"
#include "TemperatureSensor.cpp"
#include "WifiModule.cpp"
#include <ArduinoJson.h>

#define POOL_SIZE 256

class ReportManager {
  private:
    PeltierGroup *highEnergyPeltierGroup;
    PeltierGroup *lowEnergyPeltierGroup;
    TemperatureSensor *aquariumSensor;
    TemperatureSensor *externalSensor;
    AquariumManager *aquariumManager;

    void clear(DynamicJsonDocument &doc) {
        doc.clear();
        doc.garbageCollect();
    }

  public:
    ReportManager(PeltierGroup *highEnergy, PeltierGroup *lowEnergy,
                  TemperatureSensor *aquariumSensor,
                  TemperatureSensor *externalSensor,
                  AquariumManager *aquariumManager) {
        this->highEnergyPeltierGroup = highEnergy;
        this->lowEnergyPeltierGroup = lowEnergy;
        this->aquariumSensor = aquariumSensor;
        this->externalSensor = externalSensor;
        this->aquariumManager = aquariumManager;
    }

    String toJson() {

        DynamicJsonDocument doc(POOL_SIZE);

        doc["temp"]["aq"] = String(aquariumSensor->getTemperature());
        doc["temp"]["ext"] = String(externalSensor->getTemperature());
        doc["he"]["on"] = String(highEnergyPeltierGroup->isActive());
        doc["he"]["pw"] =
            String(highEnergyPeltierGroup->getCurrentConsumption());
        doc["le"]["on"] = String(highEnergyPeltierGroup->isActive());
        doc["le"]["pw"] =
            String(highEnergyPeltierGroup->getCurrentConsumption());
        doc["md"] = String(this->aquariumManager->getMode());

        String json = "";
        serializeJson(doc, json);
        clear(doc);

        return json;
    }
};

#endif
