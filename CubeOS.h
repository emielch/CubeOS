#pragma once

#include <Arduino.h>

#include "Driver/CubeDriver.h"

class CubeOS {
 public:
  void init();
  void update();
  void renderInterrupt() {};

  void setBri(double v);
  void adjBri(double v);

 private:
  double bri;
};

extern CubeOS cubeOS;
extern CubeDriver* cube;