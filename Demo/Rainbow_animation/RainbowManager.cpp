#include "RainbowManager.h"

#include "CubeOS\Driver\CubeDriver.h"
#include "makeColor.h"

extern CubeDriver* cube;

void RainbowManager::init(void (*_renderInterrupt)(), float bri) {
  renderInterrupt = _renderInterrupt;
  brighntess = bri;
  for (int i = 0; i < 180; i++) {
    int hue = i * 2;
    int saturation = 100;
    int lightness = bri / 2;
    // pre-compute the 180 rainbow colors
    rainbowColors[i] = makeColor(hue, saturation, lightness);
  }
}

void RainbowManager::update() {
  // if (sinceUpdate < 20) return;
  // sinceUpdate = 0;

  // float briInc = touchbarManager.getSpd().x * 0.5;
  // if (abs(briInc) > 0) {
  //   brighntess += touchbarManager.getSpd().x;
  //   init(renderInterrupt, constrain(brighntess, 0, 100));
  // }

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