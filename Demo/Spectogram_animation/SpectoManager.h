#pragma once

#include <Arduino.h>

class SpectoManager {
 public:
  void init(void (*_renderInterrupt)());
  void update();

 private:
  void (*renderInterrupt)();
  float peaks[16][16];
  int lastPeaksID = 0;
  elapsedMillis sinceUpdate = 0;
};

extern SpectoManager spectoManager;
