#pragma once

#include <Arduino.h>

#include "CubeOS\CubeOS.h"

class Anim {
 public:
  void init();
  void update();

  virtual const char* getName() = 0;

 private:
  virtual void _init() = 0;
  virtual void _update() = 0;
};
