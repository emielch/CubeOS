#pragma once

#include <Arduino.h>

#include "Anim.h"

#define MAX_ANIMS 5

class AnimManager {
 public:
  void init();
  void update();
  void registerAnim(Anim* anim);
  void changeAnim(int step);

 private:
  Anim* allAnims[MAX_ANIMS];
  int animAm;
  byte currAnimID = 0;
};

extern AnimManager animManager;