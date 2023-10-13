#include "TemperatureSensor.cpp"
#include <DallasTemperature.h>
#include <OneWire.h>

class AquariumSensor : public TemperatureSensor {
  private:
    OneWire *oneWire;
    DallasTemperature *sensors;
    DeviceAddress *deviceAddress;
    int numberOfDevices;

    void connect() {
        oneWire = new OneWire(pin);
        sensors = new DallasTemperature(oneWire);
        sensors->begin();
        numberOfDevices = sensors->getDeviceCount();
        deviceAddress = new DeviceAddress[numberOfDevices];
        for (int i = 0; i < numberOfDevices; i++) {
            sensors->getAddress(deviceAddress[i], i);
        }
    }

    void disconnect() {
        delete oneWire;
        delete sensors;
        delete[] deviceAddress;
    }

    void setTemperature() {
        sensors->requestTemperatures();
        this->temperature = sensors->getTempCByIndex(0);
    }

  public:
    AquariumSensor(int pin) : TemperatureSensor(pin) { this->pin = pin; }

    void read() {
        connect();
        setTemperature();
        disconnect();
    }

    float getTemperature() {
        return this->temperature;
    }
};