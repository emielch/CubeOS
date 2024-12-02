#pragma once

#include <Arduino.h>

class SerialStreamManager {
 public:
  void init();
  void update();

 private:
  void readSerial();
  unsigned long unknownCount = 0;
  elapsedMillis sinceUnknownChar = 999999;
};

extern SerialStreamManager serialStreamManager;