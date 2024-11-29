#include "Anim.h"

#include "AnimManager.h"

void Anim::init() {
  _init();
  animManager.registerAnim(this);
}

void Anim::update() {
  cubeOS.renderInterrupt();
  _update();
}
