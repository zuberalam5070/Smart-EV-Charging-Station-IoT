#include <Arduino.h>
#include <ArduinoJson.h>
#include "rpc.h"
#include "network.h"
#include "peripherals.h" // RELAY_PIN ke liye

extern PubSubClient mqtt;

void handleRpc(String requestId, char* payload) {
  JsonDocument doc;
  DeserializationError err = deserializeJson(doc, payload);
  if (err) {
    Serial.println("RPC JSON Parse Error");
    return;
  }

  String method = doc["method"].as<String>();

  // Yahan se hamara Dashboard Switch wala logic shuru hota hai
  if (method == "setRelayState") {
    bool state = doc["params"].as<bool>();
    
    if (state == true) {
      digitalWrite(RELAY_PIN, HIGH);
      Serial.println("RPC Command: Relay ON (Manual Override)");
    } else {
      digitalWrite(RELAY_PIN, LOW);
      Serial.println("RPC Command: Relay OFF (Manual Override)");
    }

    // ThingsBoard ko wapas reply bhejna zaroori hai, warna dashboard switch ghoomta rahega
    String responseTopic = "v1/devices/me/rpc/response/" + requestId;
    mqtt.publish(responseTopic.c_str(), "{\"status\":\"success\"}");
  }
}