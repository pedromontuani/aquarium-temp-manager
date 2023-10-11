#include "TemperatureSensor.cpp"
#include <dht11.h>

class AmbientTempSensor : public TemperatureSensor {
    private:
        dht11 *dht;
    
    public:
        AmbientTempSensor(byte pin) : TemperatureSensor(pin) {
            this->pin = pin;
            dht = new dht11();
        };

        ~AmbientTempSensor() {
            delete dht;
        };
    
        float getTemperature() {
            dht->read(pin);
            return dht->temperature;
        };

        int getHumidity() {
            dht->read(pin);
            return dht->humidity;
        };
};