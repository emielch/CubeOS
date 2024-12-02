#pragma once

#include <Arduino.h>

#include "../Anim.h"

class OffAnim : public Anim {
 private:
  void _init();
  void _update(bool active);
  void _render();
  const char* getName() { return "Off"; }
};
