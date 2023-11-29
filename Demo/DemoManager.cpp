#include "DemoManager.h"

#include <EEPROM.h>

#include "CubeOS\Driver\CubeDriver.h"
#include "CubeOS\SerialStreamManager.h"
#include "Orbs_animation\OrbsManager.h"
#include "Rainbow_animation\RainbowManager.h"
#include "Sine_animation\SineManager.h"

#define STREAM_BLACKOUT_DELAY 500
#define DEMO_DELAY 3000

extern CubeDriver* cube;

void exciteRandomizer() {
  uint32_t randomSeedVar = 0;
  EEPROM.get(0, randomSeedVar);
  randomSeedVar++;
  EEPROM.put(0, randomSeedVar);
  randomSeed(randomSeedVar);
}

void DemoManager::init(void (*_renderInterrupt)()) {
  exciteRandomizer();
  renderInterrupt = _renderInterrupt;
  if (renderInterrupt == nullptr) renderInterrupt = emptyFunct;
  orbsManager.init(renderInterrupt);
  sineManager.init(renderInterrupt);
  rainbowManager.init(renderInterrupt, brightness);
  currAnim = Rainbow;
  enableDemo();
}

void DemoManager::update() {
  if (paused) return;
  if (serialStreamManager.getSinceNewFrame() < STREAM_BLACKOUT_DELAY) {
    if (demoRunning) stopDemo();
    return;  // if a streaming frame has been received recently, we are still in streaming mode and we shouldn't interfere with the LEDs
  }

  if (serialStreamManager.getSinceNewFrame() > DEMO_DELAY) {
    if (!demoRunning && demoEnabled) {
      startDemo();
    }
    if (demoRunning) {
      if (currAnim == Orbs)
        orbsManager.update();
      else if (currAnim == Rainbow)
        rainbowManager.update();
      else if (currAnim == Sine)
        sineManager.update();
    }
  }

  cube->update();
}

void DemoManager::switchAnim(DemoAnim d) {
  currAnim = d;
}

void DemoManager::adjBri(int v) {
  // if (currAnim == Rainbow) v *= 2;
  brightness = constrain(brightness + v, 0, 100);
  Serial.println(brightness);
  rainbowManager.init(renderInterrupt, constrain(brightness, 0, 100));
}

void DemoManager::incBri() {
  demoManager.adjBri(1);
}
void DemoManager::decBri() {
  demoManager.adjBri(-1);
}

void DemoManager::nextDemo() {
  if (demoManager.currAnim + 1 >= DemoAm)
    demoManager.currAnim = (DemoAnim)0;
  else
    demoManager.currAnim = (DemoAnim)(demoManager.currAnim + 1);
}

void DemoManager::prevDemo() {
  if (demoManager.currAnim - 1 < 0)
    demoManager.currAnim = (DemoAnim)(DemoAm - 1);
  else
    demoManager.currAnim = (DemoAnim)(demoManager.currAnim - 1);
}

void DemoManager::enableDemo() {
  demoEnabled = true;
}
void DemoManager::disableDemo() {
  demoEnabled = false;
  stopDemo();
}
void DemoManager::startDemo() {
  demoRunning = true;
  orbsManager.init(renderInterrupt);
}
void DemoManager::stopDemo() {
  demoRunning = false;
}

DemoManager demoManager;