#ifndef CONFIG_H
#define CONFIG_H

#include <pins_arduino.h>

// Sensors pins
#define AQUARIUM_SENSOR_PIN 25
#define AMBIENT_SENSOR_PIN 33
#define TEMPERATURE_PRECISION 11

// Relay ports
#define PELTIER_01_PIN 13
#define PELTIER_02_PIN 12
#define PELTIER_03_PIN 14
#define PELTIER_04_PIN 27
#define PELTIER_05_PIN 26

#define PELTIER_POWER_CONSUMPTION 72

// WiFi settings
#define SERIAL_COMMUNICATION_SPEED 9600
#define WIFI_SSID "Pedro"
#define PASSWORD "minhasenha"
#define RESET_ESP false           // Used to clear ESP8266 saved network data
#define SERVER_IP "192.168.0.119" // Ip that is running the API
#define SERVER_PORT 3000
#define REPORTS_PATH "/reports"
#define DEBUG_MODE false

// Temperature control settings
#define GOAL_TEMPERATURE 19
#define TOLERANCE 0.3
#define UPDATE_FREQUENCY 300000 // 5 minutes

// OLED screen settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3C
#define SCREEN_CONTRAST 128
#define SCREEN_SDA SDA
#define SCREEN_SCL SCL

#endif
