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

 private:
  long onTime = 0;
  long offTime = 0;
  bool dayOn[7] = {true, true, true, true, true, true, true};
};

extern TimeManager timeManager;
