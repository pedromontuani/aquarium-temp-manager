#ifndef MODULESTATE_H
#define MODULESTATE_H

class ModuleState {
  private:
    bool active;

  protected:
    float powerConsumption;

    ModuleState(float powerConsumption, bool isActive = false) {
        this->powerConsumption = powerConsumption;
        setActive(isActive);
    };

    void setConsumption(float powerConsumption) {
        this->powerConsumption = powerConsumption;
    };

  public:
    void setActive(bool isActive) { this->active = isActive; };

    bool isActive() { return active; };

    float getCurrentConsumption() {
        if (isActive()) {
            return powerConsumption;
        }
        return 0;
    };

    float getPowerConsumption() { return powerConsumption; };
};

#endif