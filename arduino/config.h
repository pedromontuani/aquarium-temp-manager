#ifndef CONFIG_H
#define CONFIG_H

// Sensors pins
#define AQUARIUM_SENSOR_PIN 4
#define AMBIENT_SENSOR_PIN 10
#define TEMPERATURE_PRECISION 11

// Relay ports
#define PELTIER_01_PIN 5
#define PELTIER_02_PIN 6
#define PELTIER_03_PIN 7
#define PELTIER_04_PIN 8
#define PELTIER_05_PIN 9

#define PELTIER_POWER_CONSUMPTION 72

// ESP8266 settings
#define RX_PIN 12
#define TX_PIN 13
#define SERIAL_COMMUNICATION_SPEED 9600
#define SSID "YOUR_SSID"
#define PASSWORD "YOUR_PASSWORD"
#define MAC_ADDRESS "YOUR_MAC_ADDRESS" // Recommended. Necessary if you have multiple networks with same SSID (ex.: Mesh networks)
#define RESET_ESP false // Used to clear ESP8266 saved network data
#define MAX_TIMEOUT 15000
#define LONG_TIMEOUT 8000
#define SHORT_TIMEOUT 5000
#define SERVER_IP "SERVER_IP" // Ip that is running the API
#define SERVER_PORT 3000
#define REPORTS_PATH "/reports"
#define DEBUG_MODE false

// Temperature control settings
#define GOAL_TEMPERATURE 19
#define TOLERANCE 0.3
#define UPDATE_FREQUENCY 60000 // 1 minute

// OLED screen settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3C
#define SCREEN_CONSTRAST 128
#define SCREEN_SDA A4
#define SCREEN_SCL A5

#endif