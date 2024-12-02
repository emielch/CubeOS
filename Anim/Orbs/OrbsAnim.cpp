#include "OrbsAnim.h"

void OrbsAnim::_init() {
  for (int i = 0; i < orbAm; i++) {
    orbs[i].init(random(80 + CUBEWIDTH * 20, 400 + CUBEWIDTH * 50) / 100., random(100, 500) / 100., i * 137.508);
  }
}

void OrbsAnim::_update(bool active) {
  if (!active) return;

  for (int i = 0; i < orbAm; i++) {
    cubeOS.renderInterrupt();
    orbs[i].move(cube->getDt());
  }
}

void OrbsAnim::_render() {
  for (int i = 0; i < orbAm; i++) {
    orbs[i].render();
  }
}

void OrbsAnim::userInput(Axis axis, double val) {
  if (axis == X)
    for (int i = 0; i < orbAm; i++) {
      orbs[i].translate(Vector3(val, 0, 0));
    }
  else if (axis == Y)
    for (int i = 0; i < orbAm; i++) {
      orbs[i].rotate(val);
    }
  else if (axis == Z)
    for (int i = 0; i < orbAm; i++) {
      orbs[i].scale(val);
    }
};
