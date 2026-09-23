#ifndef STATE_H
#define STATE_H

#include <Arduino.h>

extern float voltage;
extern float current;
extern float power;
extern float temperature;
extern String bay_status;

// Edge AI Variables
#define bayStatus bay_status
extern unsigned long sessionStartMs;
extern int lastHourOfDay;
extern float predictedArrivalProb;
extern float predictionThreshold;
extern int predictedDurationMin;

extern bool manualOverrideActive;

extern int throttleLevel;
extern String loadDecision;
extern bool overloadActive;
extern float overloadCurrentA;
extern float maxStationLoadW;

extern int peakTariffStartHr;
extern int peakTariffEndHr;
extern int DUTY_CYCLE_WINDOW_MS;

#endif // STATE_H