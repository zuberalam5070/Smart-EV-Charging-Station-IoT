#include "peripherals.h"
#include "state.h"

DHT dht(DHTPIN, DHTTYPE);

// Float Mapping function
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void initPeripherals() {
  dht.begin();
  pinMode(PLUGIN_PIN, INPUT_PULLUP);
  pinMode(PLUGOUT_PIN, INPUT_PULLUP);

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_YELLOW, LOW);
}

void plug_status() {
  bool plugin_pressed = (digitalRead(PLUGIN_PIN) == LOW);
  bool plugout_pressed = (digitalRead(PLUGOUT_PIN) == LOW);

  if (plugin_pressed && bay_status == "FREE") {
    bay_status = "CHARGING";
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("\n[BAY 1]: EV Plugged In Detected! CHARGING...");
  }

  if (plugout_pressed && bay_status == "CHARGING") {
    bay_status = "FREE";
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("\n[BAY 1]: EV Plugged Out Detected! FREE.");
  }
}

void updateLEDStatus() {
  if (bay_status == "CHARGING") {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, HIGH);
  } else if (bay_status == "FREE") {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_YELLOW, LOW);
  }
}

void sampleSensors() {
  int raw_current = analogRead(CURRENT_PIN);
  int raw_voltage = analogRead(VOLTAGE_PIN);
  temperature = dht.readTemperature();

  voltage = mapFloat(raw_voltage, 0, 4095, 0, 250);  
  
  if (bay_status != "CHARGING") {
    current = 0.0;
    power = 0.0;
  } else {
    current = mapFloat(raw_current, 0, 4095, 0, 32); 
    power = voltage * current;  // <-- MAIN FIX: पावर यहीं कैलकुलेट होगी
  }

  // --- ओवरलोड अलार्म लॉजिक (Overload Alarm) ---
  if (current > overloadCurrentA) { // overloadCurrentA की वैल्यू 16.0 है
    overloadActive = true;
    digitalWrite(LED_RED, HIGH);    // 16A से ऊपर होने पर लाल LED जलेगी
  } else {
    overloadActive = false;
    digitalWrite(LED_RED, LOW);     // नॉर्मल होने पर LED बुझ जाएगी
  }
}

float recentAvgCurrent() {
  // अगर अभी करंट सेंसर का एवरेज लॉजिक नहीं लिखा है तो डिफॉल्ट वैल्यू:
  return 10.0f; // 10 Amps default/simulated
}