#include "SpectoManager.h"

#include "CubeOS\Audio\AudioManager.h"
#include "CubeOS\Demo\DemoManager.h"
#include "CubeOS\Driver\CubeDriver.h"

extern CubeDriver* cube;

void SpectoManager::init(void (*_renderInterrupt)()) {
  renderInterrupt = _renderInterrupt;
}

void SpectoManager::update() {
  if (audioManager.newData)
    for (int i = 0; i < 16; i++) {
      peaks[lastPeaksID][i] = audioManager.peaks[i];
    }

  int peaksID;

  for (uint8_t x = 0; x < cube->width; x++) {
    for (uint8_t z = 0; z < cube->depth; z++) {
      peaksID = (lastPeaksID - z + 16) % 16;
      float level = x > 15 ? 0 : peaks[peaksID][x];
      int height = level * 50 * cube->height;
      for (int y = 0; y <= cube->height; y++) {
        float bri = y < height ? 30 : 0;
        Color col = Color(y*15+z*5, 100-z*4+20, max(bri-z*2,0), HSB_MODE);
        cube->setPixel(x, y, z, col);
      }
    }
  }
  if (audioManager.newData) {
    lastPeaksID++;
    if (lastPeaksID > 15) lastPeaksID = 0;
  }
  audioManager.newData = false;
}

SpectoManager spectoManager;