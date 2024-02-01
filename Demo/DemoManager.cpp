#include "DemoManager.h"

#include <EEPROM.h>

#include "CubeOS\Driver\CubeDriver.h"
#include "CubeOS\SerialStreamManager.h"
#include "Orbs_animation\OrbsManager.h"
#include "Rainbow_animation\RainbowManager.h"
#include "Sine_animation\SineManager.h"
#include "Spectogram_animation\SpectoManager.h"

#define STREAM_BLACKOUT_DELAY 1500
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
#if DITHER
  demoBri = 50;
  streamBri = 50;
#else
  demoBri = 15;
  streamBri = 15;
#endif
  exciteRandomizer();
  renderInterrupt = _renderInterrupt;
  if (renderInterrupt == nullptr) renderInterrupt = emptyFunct;
  orbsManager.init(renderInterrupt);
  sineManager.init(renderInterrupt);
  rainbowManager.init(renderInterrupt);
  currAnim = Orbs;
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
      else if (currAnim == Specto)
        spectoManager.update();
    }
  }

  cube->update();
}

void DemoManager::switchAnim(DemoAnim d) {
  currAnim = d;
}

void DemoManager::adjBri(int v) {
  double* briPntr = demoRunning ? &demoBri : &streamBri;
  *briPntr = constrain(*briPntr + v * 0.5, 0, 400);
  cube->setBrightness(*briPntr);
  Serial.println(*briPntr, 1);
}

void DemoManager::incBri() {
  demoManager.adjBri(1);
}
void DemoManager::decBri() {
  demoManager.adjBri(-1);
}

void DemoManager::setBri(double bri, bool demo) {
  double* briPntr = demo ? &demoBri : &streamBri;
  *briPntr = constrain(bri, 0, 400);
  if (demo == demoRunning) cube->setBrightness(*briPntr);
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
  cube->setBrightness(demoBri);
}
void DemoManager::stopDemo() {
  demoRunning = false;
  cube->setBrightness(streamBri);
}

DemoManager demoManager;