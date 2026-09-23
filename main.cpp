#include <Arduino.h>
#include "config.h"
#include "state.h"
#include "peripherals.h"
#include "optimization.h"
#include "edge_ai.h"
#include "network.h"      // <-- NAYA: WiFi ke liye network file add ki
#include "telemetry.h"    // <-- NAYA: Cloud publish ke liye uncomment kiya

unsigned long lastPrintTime = 0;
const unsigned long printInterval = 5000; 

void setup() {
  Serial.begin(115200);
  initPeripherals();
  
  // वाईफाई और थिंग्सबोर्ड से कनेक्ट करने के लिए
  connectWiFi();         
  connectMQTT();  
  
  Serial.println("EV Charging Station: System Ready with Edge AI");
}

void loop() {
  // 1. बटन्स की स्थिति लगातार चेक करें (Plug-in / Plug-out)
  plug_status();

  // 2. रिले और LED इंडिकेटर्स अपडेट करें
  updateLEDStatus();

  // 3. हर 5 सेकंड में सेंसर्स पढ़ें, AI रन करें और डेटा क्लाउड पर भेजें
  unsigned long now = millis();
  if (now - lastPrintTime >= printInterval) {
    lastPrintTime = now;
    
    sampleSensors();       // पहले सेंसर्स से करंट, वोल्टेज आदि पढ़ें
    
    // Day 14: AI मॉडल रन करें (यह Probability और Duration सेट करेगा)
    runEdgeAIInference();      
    
    runOptimization();

    // Day 14: क्लाउड पर भेजें 
    publishTelemetry();    // <-- NAYA: Ab dashboard par data jana shuru ho jayega
  }
  
  mqtt.loop();  // Ye cloud commands ko continuously listen karega
}