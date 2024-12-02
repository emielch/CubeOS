#pragma once

#include <Arduino.h>

#include "../Anim.h"
#include "Orb.h"

class OrbsAnim : public Anim {
 private:
  void _init();
  void _update(bool active);
  void _render();
  const char* getName() { return "Orbs"; }
  void userInput(Axis axis, double val);

  const static int orbAm = CUBEWIDTH;
  Orb orbs[orbAm];
};
