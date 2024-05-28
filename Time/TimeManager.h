#pragma once

#include <Arduino.h>

class TimeManager {
 public:
  void update();
  void printCurrTime();
  unsigned long now();
  void setTime(unsigned long t);
  void setOnTime(long t){onTime = t;}
  void setOffTime(long t){offTime = t;};

 private:
  long onTime = 0;
  long offTime = 0;
};

extern TimeManager timeManager;
