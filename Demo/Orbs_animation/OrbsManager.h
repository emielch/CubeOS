#pragma once

#include <Arduino.h>

#include "CubeOS\Driver.h"
#include "Orb.h"

class OrbsManager {
 public:
  void init(void (*_renderInterrupt)());
  void update();

 private:
  void touchInput();
  const static int orbAm = CUBEWIDTH;
  Orb orbs[orbAm];

  void (*renderInterrupt)();
};

extern OrbsManager orbsManager;
