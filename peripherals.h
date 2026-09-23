#ifndef PERIPHERALS_H
#define PERIPHERALS_H


#include <Arduino.h>
#include <DHT.h>
#include "config.h"
#include "state.h"


// --- Pin Definitions ---
#define DHTPIN 15
#define DHTTYPE DHT22

#define PLUGIN_PIN 32     // Bay Plugin Switch / Button
#define PLUGOUT_PIN 33    // Bay Plugout Switch / Button

#define RELAY_PIN 23      // Relay Control Pin

#define LED_GREEN 18       // Status LEDs
#define LED_YELLOW 19
#define LED_RED 21

#define CURRENT_PIN 34    // Potentiometer 1 (Analog Input)
#define VOLTAGE_PIN 35    // Potentiometer 2 (Analog Input)


extern DHT dht;

void initPeripherals();
void sampleSensors();
void plug_status();
void updateLEDStatus();
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);
float recentAvgCurrent();
#endif
