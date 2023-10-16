#include "TemperatureSensor.cpp"
#include <DHT.h>

class AmbientTempSensor : public TemperatureSensor {
    private:
        DHT *dht;
        float humidity;
    
    public:
        AmbientTempSensor(byte pin) : TemperatureSensor(pin) {
            this->pin = pin;
            this->humidity = 0;
        };

        ~AmbientTempSensor() {
            delete dht;
        };

        void read() {
            dht = new DHT(pin, DHT22);
            this->temperature = dht->readTemperature();
            this->humidity = dht->readHumidity();
            delete dht;
        }
    
        float getTemperature() {
            return this->temperature;
        };

        int getHumidity() {
            return this->humidity;
        };
};