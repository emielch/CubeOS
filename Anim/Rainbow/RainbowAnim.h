#pragma once

#include <Arduino.h>

#include "../Anim.h"

class RainbowAnim : public Anim {
 private:
  void _init();
  void _update();
  const char* getName() { return "Rainbow"; }

  int rainbowColors[180];
  float currColorId = 0;
  elapsedMillis sinceUpdate = -9999;
};
