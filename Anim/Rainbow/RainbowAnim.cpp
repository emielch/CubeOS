#include "RainbowAnim.h"

#include "makeColor.h"

extern CubeDriver* cube;

void RainbowAnim::_init() {
  for (int i = 0; i < 180; i++) {
    int hue = i * 2;
    int saturation = 100;
    int lightness = 50;
    // pre-compute the 180 rainbow colors
    rainbowColors[i] = makeColor(hue, saturation, lightness);
  }
}

void RainbowAnim::_update(bool active) {
  if (!active) return;

  currColorId += cube->getDt() * 30;
  if (currColorId >= 180) currColorId = 0;
}

void RainbowAnim::_render() {
  for (byte z = 0; z < CUBEDEPTH; z++) {
    cubeOS.renderInterrupt();
    for (byte y = 0; y < CUBEHEIGHT; y++)
      for (byte x = 0; x < CUBEWIDTH; x++) {
        int index = ((int)currColorId + x * 10 + y * 5 + z * 3) % 180;
        cube->setPixel(x, y, z, rainbowColors[index]);
      }
  }
}