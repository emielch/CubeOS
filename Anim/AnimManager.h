#pragma once

#include <Arduino.h>

#include "Anim.h"

#define MAX_ANIMS 6

class AnimManager {
 public:
  void init();
  void update();
  void registerAnim(Anim* anim);
  void shiftAnim(int step);
  void setAnim(int id);
  void userInput(Axis axis, double val);
  void enable();
  void disable();
  bool getEnabled() { return enabled; };
  void togglePaused() { paused = !paused; };

  int getCurrAnimID() { return currAnimID; }

 private:
  Anim* allAnims[MAX_ANIMS];
  int animAm;
  byte currAnimID;
  byte savedAnimID;
  bool enabled;
  bool paused;

  void updateBri();
  double savedBri = -1;
};

extern AnimManager animManager;