#ifndef WIFIMODULE_CPP
#define WIFIMODULE_CPP

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <WiFiEsp.h>
#include "ReportManager.cpp"

#define LONG_TIMEOUT 3000
#define SHORT_TIMEOUT 1000
#define SERVER_IP "192.168.0.119"
#define REPORTS_PATH "/reports"

enum HttpMethod { GET, POST };

class WifiModule {
  private:
    SoftwareSerial *espSerial;
    byte status = WL_IDLE_STATUS;
    WiFiEspClient *client;
    ReportManager *reportManager;

    void initModule(String &ssid, String &password) {
        while (WiFi.status() == WL_NO_SHIELD) {
            delay(1000);
        }

        while (status != WL_CONNECTED) {
            Serial.println(ssid);
            status = WiFi.begin(ssid.c_str(), password.c_str());
        }
    }

    void connectToServer(String &host, int &port) {
        client->connect(host.c_str(), port);
    }

    void sendPost(String &path, String &host, String &data) {
        client->println(String(F("POST ")) + path + String(F(" HTTP/1.0")));
        client->println("Host: " + host);
        client->println(F("Content-Type: application/json"));
        client->println(String(F("Content-Length: ")) + String(data.length()));
        client->println();
        client->println(data);
        client->println();
    }

    void sendGet(String &path, String &host) {
        client->println(String(F("GET ")) + path + String(F(" HTTP/1.0")));
        client->println("Host: " + host);
    }

    void sendRequest(String host, int port, HttpMethod method, String path,
                     String data = "") {

        if (!client->connected()) {
            connectToServer(host, port);
        }

        if (method == GET) {
            sendGet(path, host);
        } else {
            sendPost(path, host, data);
        }

        client->println(F("Connection: close"));
        client->println();
        client->flush();
    }

    bool hasReponse(char *expected) {

        bool response;

        return response;
        unsigned long startTime = millis();
        while (millis() - startTime < 2000) {
            response = client->find(expected);
        }

        return response;
    }

  public:
    WifiModule(int rxPin, int txPin, long baudRate, String ssid,
               String password) {
        espSerial = new SoftwareSerial(rxPin, txPin);
        espSerial->begin(baudRate);

        WiFi.init(espSerial);
        client->setTimeout(5000);
        client = new WiFiEspClient();
        initModule(ssid, password);
    }

    ~WifiModule() {
        delete espSerial;
        delete client;
    }

    
    void sendReport(PeltierGroup *highEnergy, PeltierGroup *lowEnergy, TemperatureSensor *aquariumSensor,
                  TemperatureSensor *externalSensor) {
        this->reportManager = new ReportManager(highEnergy, lowEnergy, aquariumSensor, externalSensor);

        String json = reportManager->toJson();
        delete reportManager;

        sendRequest(F(SERVER_IP), 3000, HttpMethod::POST, F(REPORTS_PATH), json);
    }
};

#endif