#include "OrbsManager.h"

#include "CubeOS\Driver\CubeDriver.h"

extern CubeDriver* cube;

void OrbsManager::init(void (*_renderInterrupt)()) {
  renderInterrupt = _renderInterrupt;
  for (int i = 0; i < orbAm; i++) {
    orbs[i].init(random(400, 1200) / 100., random(100, 300) / 100., i * 137.508);
  }
}

void OrbsManager::update() {
  touchInput();
  for (int i = 0; i < orbAm; i++) {
    renderInterrupt();
    orbs[i].move(cube->getDt());
    orbs[i].render();
  }
}

void OrbsManager::touchInput() {
  // Vector3 spd = touchbarManager.getSpd();
  // float r = touchbarManager.getRotationSpd();
  // float s = touchbarManager.getScaleSpd();

  // for (int i = 0; i < orbAm; i++) {
  //   orbs[i].translate(spd);
  //   orbs[i].rotate(r);
  //   orbs[i].scale(s);
  // }
}

OrbsManager orbsManager;