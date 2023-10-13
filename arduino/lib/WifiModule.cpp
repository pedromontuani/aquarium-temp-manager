#ifndef WIFIMODULE_CPP
#define WIFIMODULE_CPP

#include "../config.h"
#include "EepromManager.cpp"
#include "ReportManager.cpp"
#include <Arduino.h>
#include <SoftwareSerial.h>

enum HttpMethod { GET, POST };

class WifiModule {
  private:
    SoftwareSerial *espSerial;
    ReportManager *reportManager;

    void initModule(String &ssid, String &password, String &macAddress) {
        sendCommand("AT", SHORT_TIMEOUT);
        sendCommand(F("AT+RST"), MAX_TIMEOUT);
        delay(MAX_TIMEOUT);

        if (!EepromManager::isEspConfigured()) {
            connectToWifi(ssid, password, macAddress);
            EepromManager::setEspConfigured();
        }

        sendCommand(F("AT+CIFSR"), SHORT_TIMEOUT);
        sendCommand(F("AT+CIPMUX=1"), SHORT_TIMEOUT);
    }

    void connectToWifi(String &ssid, String &password, String &macAddress) {
        sendCommand(F("AT+CWMODE_DEF=1"), SHORT_TIMEOUT);
        sendCommand("AT+CWJAP_DEF=\"" + ssid + "\",\"" + password + "\",\"" +
                        macAddress + "\"",
                    MAX_TIMEOUT);
        sendCommand(F("AT+CWAUTOCONN=1"), SHORT_TIMEOUT);
    }

    void connectToServer(String &host, int &port) {
        sendCommand("AT+CIPSTART=0,\"TCP\",\"" + host + "\"," + port,
                    SHORT_TIMEOUT);
    }

    String sendPost(String &path, String &host, int &port, String &json) {
        String data = "";
        data += "POST " + path + F(" HTTP/1.0\r\n");
        data = data + F("Content-Type: application/json") + "\r\n";
        data +=
            String(F("Content-Length: ")) + String(json.length()) + "\r\n\r\n";
        data += json + "\r\n\r\n";

        return data;
    }

    void sendGet(String &path, String &host) {
        // TODO: implement
    }

    void sendRequest(String host, int port, HttpMethod method, String path,
                     String &data) {

        connectToServer(host, port);
        String request;
        if (method == GET) {
            sendGet(path, host);
        } else {
            request = sendPost(path, host, port, data);
        }

        request = request + F("Connection: close") + "\r\n";

        sendCommand(String(F("AT+CIPSEND=0,")) + String(request.length()),
                    SHORT_TIMEOUT);
        sendCommand(request, MAX_TIMEOUT);
    }

    bool hasReponse(char *expected) {
        // TODO : implement
    }

    void readRes(int timeout = LONG_TIMEOUT) {}

    void sendCommand(String cmd, int timeout = LONG_TIMEOUT,
                     bool debug = DEBUG_MODE) {
        espSerial->print(cmd + "\r\n");

        long int time = millis();
        while ((time + timeout) > millis()) {
            while (espSerial->available()) {
                char c = espSerial->read();
                if (debug) {
                    Serial.print(c);
                }
            }
        }
        if (debug) {
            Serial.println();
        }
    };

  public:
    WifiModule(int rxPin, int txPin, long baudRate, String ssid,
               String password, String macAddress) {
        espSerial = new SoftwareSerial(rxPin, txPin);
        espSerial->begin(baudRate);

        initModule(ssid, password, macAddress);
    }

    ~WifiModule() { delete espSerial; }

    void sendReport(PeltierGroup *highEnergy, PeltierGroup *lowEnergy,
                    TemperatureSensor *aquariumSensor,
                    TemperatureSensor *externalSensor) {
        this->reportManager = new ReportManager(highEnergy, lowEnergy,
                                                aquariumSensor, externalSensor);

        String json = reportManager->toJson();
        delete reportManager;

        sendRequest(F(SERVER_IP), SERVER_PORT, HttpMethod::POST, F(REPORTS_PATH),
                    json);
    }
};

#endif