#include "OrbsAnim.h"

void OrbsAnim::_init() {
  for (int i = 0; i < orbAm; i++) {
    orbs[i].init(random(80 + CUBEWIDTH * 20, 400 + CUBEWIDTH * 50) / 100., random(100, 500) / 100., i * 137.508);
  }
}

void OrbsAnim::_update() {
  touchInput();
  for (int i = 0; i < orbAm; i++) {
    cubeOS.renderInterrupt();
    orbs[i].move(cube->getDt());
    orbs[i].render();
  }
}

void OrbsAnim::touchInput() {
  // Vector3 spd = touchbarManager.getSpd();
  // float r = touchbarManager.getRotationSpd();
  // float s = touchbarManager.getScaleSpd();

  // for (int i = 0; i < orbAm; i++) {
  //   orbs[i].translate(spd);
  //   orbs[i].rotate(r);
  //   orbs[i].scale(s);
  // }
}