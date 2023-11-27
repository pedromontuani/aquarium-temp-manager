#include <EEPROM.h>

#define ESP_SETTINGS_ADDRESS 0

#ifndef _EEPROM_MANAGER_
#define _EEPROM_MANAGER_

class EepromManager {
  private:
    EepromManager() {}

  public:
    static void resetEsp() { EEPROM.update(ESP_SETTINGS_ADDRESS, 0); }

    static void setEspConfigured() {
        EepromManager::write(ESP_SETTINGS_ADDRESS, 1);
    }

    static bool isEspConfigured() {
        return EEPROM.read(ESP_SETTINGS_ADDRESS) == 1;
    }

    static void write(int address, byte value) {
        EEPROM.update(address, value);
    }

    static byte read(int address) { return EEPROM.read(address); }
};

#endif