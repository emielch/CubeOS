#pragma once

#include <Arduino.h>

class SerialStreamManager {
 public:
  void init();
  void update();
  unsigned long getSinceNewFrame() { return sinceNewFrame; }
  byte getCubeID();
  void setCubeID(byte ID);

 private:
  elapsedMillis sinceNewFrame = 999999;
  void sendInfo();
};

extern SerialStreamManager serialStreamManager;