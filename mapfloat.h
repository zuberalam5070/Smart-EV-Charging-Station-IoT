#ifndef MAPFLOAT_H
#define MAPFLOAT_H

inline float mapFloat(long x, long inMin, long inMax, float outMin, float outMax) {
  return (x - inMin) * (outMax - outMin) / (float)(inMax - inMin) + outMin;
}

#endif // MAPFLOAT_H