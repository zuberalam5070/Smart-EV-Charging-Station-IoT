#include <Arduino.h>
#include <ArduinoJson.h>
#include "telemetry.h"
#include "network.h"
#include "state.h"
#include "config.h"

void publishTelemetry() {
  if (!mqtt.connected()) return;

  JsonDocument doc;
  
  doc["bayId"] = BAY_ID;
  doc["voltage"] = round(voltage * 10) / 10.0;
  doc["current"] = round(current * 10) / 10.0;
  doc["power"] = round(power * 10) / 10.0;  

  // === यहाँ totalpower की key ऐड कर दी गई है ===
  // (चूँकि इस कोड में अभी सिर्फ इसी Bay की 'power' है, इसलिए totalpower में भी यही वैल्यू जाएगी।
  // इससे ThingsBoard पर आपका Radial Gauge काम करने लगेगा!)
  doc["totalpower"] = round(power * 10) / 10.0;
  // ============================================

  if (isnan(temperature)) {
    doc["temperature"] = 25.0;
  } else {
    doc["temperature"] = round(temperature * 10) / 10.0;
  }

  doc["bayStatus"] = bayStatus;
  doc["load_decision"] = loadDecision;
  doc["throttle_level"] = throttleLevel;
  doc["overload_active"] = overloadActive;
  doc["arrival_probability"] = predictedArrivalProb; 
  doc["predicted_duration"] = predictedDurationMin;

  char buffer[350];
  serializeJson(doc, buffer);

  mqtt.publish("v1/devices/me/telemetry", buffer);
  Serial.print("[MQTT >>] ");
  Serial.println(buffer);
}