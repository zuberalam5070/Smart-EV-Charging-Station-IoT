#include "state.h"

float voltage = 0.0;
float current = 0.0;
float power = 0.0;
float temperature = 0.0;
String bay_status = "FREE";

unsigned long sessionStartMs = 0;
int lastHourOfDay = 0;
float predictedArrivalProb = 0.0;
int predictedDurationMin = 0;

// पुराने वेरिएबल्स के नीचे ये लाइनें जोड़ें:
String loadDecision = "Allow";
int throttleLevel = 100;
bool overloadActive = false;
float overloadCurrentA = 16.0;
float maxStationLoadW = 3000.0;
float predictionThreshold = 0.5;
int peakTariffStartHr = 18;
int peakTariffEndHr = 21;
int DUTY_CYCLE_WINDOW_MS = 2000;
bool manualOverrideActive = false;