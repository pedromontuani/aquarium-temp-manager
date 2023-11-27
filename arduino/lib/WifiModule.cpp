#ifndef WIFIMODULE_CPP
#define WIFIMODULE_CPP

#include "../config.h"
#include "AquariumManager.cpp"
#include "ReportManager.cpp"
#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <WiFiClient.h>

enum HttpMethod { GET, POST };

class WifiModule {
  private:
    HTTPClient *http;

    void initModule(String &ssid, String &password) {
        WiFi.mode(WIFI_STA);
        WiFi.disconnect();
        WiFi.setHostname("AquariumManager");
        this->connectToWifi(ssid, password);
    }

    void connectToWifi(String &ssid, String &password) {
        WiFi.begin(ssid.c_str(), password.c_str());
        int tryDelay = 500;
        int numberOfTries = 20;

        // Wait for the WiFi event
        while (true) {
            switch (WiFi.status()) {
            case WL_NO_SSID_AVAIL:
                Serial.println("[WiFi] SSID not found");
                break;
            case WL_CONNECT_FAILED:
                Serial.print("[WiFi] Failed - WiFi not connected! Reason: ");
                return;
                break;
            case WL_CONNECTION_LOST:
                Serial.println("[WiFi] Connection was lost");
                break;
            case WL_SCAN_COMPLETED:
                Serial.println("[WiFi] Scan is completed");
                break;
            case WL_DISCONNECTED:
                Serial.println("[WiFi] WiFi is disconnected");
                break;
            case WL_CONNECTED:
                Serial.println("[WiFi] WiFi is connected!");
                Serial.print("[WiFi] IP address: ");
                Serial.println(WiFi.localIP());
                return;
                break;
            default:
                Serial.print("[WiFi] WiFi Status: ");
                Serial.println(WiFi.status());
                break;
            }
            delay(tryDelay);

            if (numberOfTries <= 0) {
                Serial.print("[WiFi] Failed to connect to WiFi!");
                // Use disconnect function to force stop trying to connect
                WiFi.disconnect();
                return;
            } else {
                numberOfTries--;
            }
        }
    }

    bool sendRequest(String host, int port, HttpMethod method, String path,
                     String &data) {
        if (WiFi.status() == WL_CONNECTED) {
            http = new HTTPClient();
            http->begin(host, port, path);

            http->addHeader("Content-Type", "application/json");
            http->addHeader("Connection", "close");

            int httpResponseCode = 0;

            switch (method) {
            case HttpMethod::GET:
                httpResponseCode = http->GET();
                break;
            case HttpMethod::POST:
                httpResponseCode = http->POST(data);
                break;
            }

            delete http;

            return httpResponseCode == HTTP_CODE_OK;
        }
    }

  public:
    WifiModule(String ssid, String password) { initModule(ssid, password); }

    void sendReport(PeltierGroup *highEnergy, PeltierGroup *lowEnergy,
                    TemperatureSensor *aquariumSensor,
                    TemperatureSensor *externalSensor,
                    AquariumManager *aquariumManager) {

        ReportManager *reportManager =
            new ReportManager(highEnergy, lowEnergy, aquariumSensor,
                              externalSensor, aquariumManager);

        String json = reportManager->toJson();
        delete reportManager;

        sendRequest(SERVER_IP, SERVER_PORT, HttpMethod::POST, REPORTS_PATH,
                    json);
    }
};

#endif