#pragma once

#include <Arduino.h>

#include "../Anim.h"
#include "Orb.h"

class OrbsAnim : public Anim {
 private:
  void _init();
  void _update();
  const char* getName() { return "Orbs"; }

  void touchInput();
  const static int orbAm = CUBEWIDTH;
  Orb orbs[orbAm];
};
