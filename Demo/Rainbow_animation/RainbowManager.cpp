#include "RainbowManager.h"

#include "CubeOS\Driver\CubeDriver.h"
#include "makeColor.h"

extern CubeDriver* cube;

void RainbowManager::init(void (*_renderInterrupt)()) {
  renderInterrupt = _renderInterrupt;
  for (int i = 0; i < 180; i++) {
    int hue = i * 2;
    int saturation = 100;
    int lightness = 50;
    // pre-compute the 180 rainbow colors
    rainbowColors[i] = makeColor(hue, saturation, lightness);
  }
}

void RainbowManager::update() {
  for (byte z = 0; z < cube->depth; z++)
    for (byte y = 0; y < cube->height; y++)
      for (byte x = 0; x < cube->width; x++) {
        int index = ((int)currColorId + x * 10 + y * 5 + z * 3) % 180;
        cube->setPixel(x, y, z, rainbowColors[index]);
      }
  currColorId += cube->getDt() * 30;
  if (currColorId >= 180) currColorId = 0;
}

RainbowManager rainbowManager;