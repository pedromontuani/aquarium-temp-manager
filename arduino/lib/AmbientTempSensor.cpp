#include "TemperatureSensor.cpp"
#include <dht11.h>

class AmbientTempSensor : public TemperatureSensor {
    private:
        dht11 *dht;
    
    public:
        AmbientTempSensor(byte pin) : TemperatureSensor(pin) {
            this->pin = pin;
        };

        ~AmbientTempSensor() {
            delete dht;
        };

        void read() {
            dht = new dht11();
            dht->read(pin);
            this->temperature = dht->temperature;
            delete dht;
        }
    
        float getTemperature() {
            return this->temperature;
        };

        int getHumidity() {
            dht->read(pin);
            return dht->humidity;
        };
};