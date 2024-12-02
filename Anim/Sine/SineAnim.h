#pragma once

#include <Arduino.h>

#include "../Anim.h"

class SineAnim : public Anim {
 private:
  void _init();
  void _update(bool active);
  void _render();
  const char* getName() { return "Sine"; }
  void userInput(Axis axis, double val);

  int rainbowColors[180];

  float x_min = -2;
  float x_max = 2;
  float z_min = -2;
  float z_max = 2;
  float phase = 0.0f;
  float phaseSpd = 1;
  float hueOffset = 30;
  float hueScale = 15;
};
