#pragma once

#include <Arduino.h>

template <int SAMPLE_AM>
class RunningAverager {
 public:
  void addSample(double s) {
    values[i] = s;
    if (++i >= SAMPLE_AM) i = 0;
    if (usedVals < SAMPLE_AM - 1) usedVals++;
  }

  int getSampleAm() { return usedVals; }
  int getTotSampleAm() { return SAMPLE_AM; }

  double getAvg() {
    if (usedVals == 0) return 0;

    double avg = 0;
    for (int j = 0; j < usedVals; j++) {
      avg += values[j];
    }
    return avg / usedVals;
  }

  void reset() {
    usedVals = 0;
    i = 0;
  }

  operator double() {
    return getAvg();
  }

 private:
  double values[SAMPLE_AM];
  int i = 0;
  int usedVals = 0;
};