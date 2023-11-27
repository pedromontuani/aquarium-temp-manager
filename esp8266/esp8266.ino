#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

#define WIFI_SSID "Pedro"
#define WIFI_PASS "minhasenha"
#define SERVER_IP "192.168.0.119"
#define SERVER_PORT 3000
#define REPORTS_PATH "/reports"

void setup() {
    Serial.begin(115200);
    delay(5000);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
}

void sendRequest(String data) {
    WiFiClient client;

    HTTPClient http;
    http.begin(client, "http://" + String(SERVER_IP) + ":" +
                           String(SERVER_PORT) + String(REPORTS_PATH));
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.POST(data);
    String payload = http.getString();
    Serial.println(payload);
    http.end();
}

void loop() {
    String data = "";
    while (Serial.available()) {
        data += Serial.read();
    }

    if (data.size()) {
        sendRequest(data);
    }
}
