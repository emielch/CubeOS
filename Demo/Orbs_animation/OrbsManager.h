#pragma once

#include <Arduino.h>

#include "Orb.h"

class OrbsManager {
 public:
  void init(void (*_renderInterrupt)());
  void update();

 private:
  void touchInput();
  const static int orbAm = 15;
  Orb orbs[orbAm];

  void (*renderInterrupt)();
};

extern OrbsManager orbsManager;
