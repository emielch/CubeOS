#pragma once

#include <Arduino.h>

class TimeManager {
 public:
  void update();
  void printCurrTime();
  unsigned long now();
  void setTime(unsigned long t);
  void setOnTime(long t) { onTime = t; }
  void setOffTime(long t) { offTime = t; };
  void setOnDay(int day, bool on);
  void forceOn() { forcingOn = true; };
  void forceOff() { forcingOff = true; };

 private:
  unsigned long onTime = 0;
  unsigned long offTime = 0;
  bool dayOn[7] = {true, true, true, true, true, true, true};
  bool forcingOn = false;
  bool forcingOff = false;
  void setOnOff(bool val);
};

extern TimeManager timeManager;
