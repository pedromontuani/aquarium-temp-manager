#include <OneWire.h>  
#include <DallasTemperature.h>
#include "TemperatureSensor.cpp"

class AquariumSensor: public TemperatureSensor {
    private:
        OneWire *oneWire;
        DallasTemperature *sensors;
        DeviceAddress *deviceAddress;
        int numberOfDevices;
    
    public:
        AquariumSensor(int pin) : TemperatureSensor(pin) {
            this->pin = pin;
            oneWire = new OneWire(pin);
            sensors = new DallasTemperature(oneWire);
            sensors->begin();
            numberOfDevices = sensors->getDeviceCount();
            deviceAddress = new DeviceAddress[numberOfDevices];
            for (int i = 0; i < numberOfDevices; i++) {
                sensors->getAddress(deviceAddress[i], i);
            }
        }
    
        ~AquariumSensor() {
            delete oneWire;
            delete sensors;
            delete[] deviceAddress;
        }
    
        float getTemperature() {
            sensors->requestTemperatures();
            return sensors->getTempCByIndex(0);
        }
};