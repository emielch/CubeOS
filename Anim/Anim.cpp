#include "Anim.h"

#include "AnimManager.h"

void Anim::init() {
  _init();
  animManager.registerAnim(this);
}

void Anim::update(bool active) {
  cubeOS.renderInterrupt();
  _update(active);
}

void Anim::render() {
  cubeOS.renderInterrupt();
  _render();
}

double Anim::getBri() {
  return bri;
}