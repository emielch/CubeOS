#pragma once

#include <Arduino.h>

class SerialStreamManager {
 public:
  void init();
  void update();
  unsigned long getSinceNewFrame() { return sinceNewFrame; }
  byte getCubeID();
  void setCubeID(byte ID);
  static void decreaseCubeID();
  static void increaseCubeID();

 private:
  void readSerial();
  elapsedMillis sinceNewFrame = 999999;
  void sendInfo();
  void sendDiff(bool diff);
};

extern SerialStreamManager serialStreamManager;