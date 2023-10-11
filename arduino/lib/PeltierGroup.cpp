#ifndef PELTIERGROUP_H
#define PELTIERGROUP_H

#include "ModuleState.cpp"
#include "RelayPort.cpp"

class PeltierGroup : public ModuleState {
  private:
    RelayPort *group;
    int count = 0;

    void init() {
        for (byte i = 0; i < count; i++) {
            this->powerConsumption += group[i].getPowerConsumption();
        }

        this->turnOff();
    };

  public:
    PeltierGroup(RelayPort *group, int count) : ModuleState(0, false) {
        this->group = group;
        this->count = count;
        init();
    };

    void turnOn() {
        for (byte i = 0; i < count; i++) {
            group[i].on();
        }
        this->setActive(true);
    };

    void turnOff() {
        for (byte i = 0; i < count; i++) {
            group[i].off();
        }
        this->setActive(false);
    };
};

#endif