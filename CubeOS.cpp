#include "CubeOS.h"

#include "Audio\AudioManager.h"
#include "Demo\DemoManager.h"
#include "Driver.h"
#include "SerialStreamManager.h"

void CubeOS::init() {
  cube->init();
  serialStreamManager.init();
  audioManager.init();
  demoManager.init();
}

void CubeOS::update() {
  serialStreamManager.update();
  audioManager.update();
  demoManager.update();
}

CubeOS cubeOS;