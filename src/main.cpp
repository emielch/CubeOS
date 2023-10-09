#include <Arduino.h>
#include <EEPROM.h>

#include "CubeDriver\CubeDriver_8x8x8.h"
#include "Demo\DemoManager.h"
#include "SerialStreamManager.h"

CubeDriver* cube;

void renderInterrupt() {
}

void exciteRandomizer() {
  uint32_t randomSeedVar = 0;
  EEPROM.get(0, randomSeedVar);
  randomSeedVar++;
  EEPROM.put(0, randomSeedVar);
  randomSeed(randomSeedVar);
}

void setup() {
  exciteRandomizer();

  cube = new CubeDriver_8x8x8();
  cube->init();

  serialStreamManager.init();
  demoManager.init(&renderInterrupt);
}

void loop() {
  serialStreamManager.update();
  demoManager.update();
}