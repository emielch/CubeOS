#pragma once

#include <Arduino.h>

#include "../Anim.h"

class SpectoAnim : public Anim {
 private:
  void _init();
  void _update();
  const char* getName() { return "Specto"; }

  float peaks[16][16];
  int lastPeaksID = 0;
  elapsedMillis sinceUpdate = 0;
};