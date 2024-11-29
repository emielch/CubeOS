#include "SpectoManager.h"

#include "CubeOS\Audio\AudioManager.h"
#include "CubeOS\Demo\DemoManager.h"
#include "CubeOS\CubeOS.h"

extern CubeDriver* cube;

void SpectoManager::init(void (*_renderInterrupt)()) {
  renderInterrupt = _renderInterrupt;
}

void SpectoManager::update() {
#ifdef USB_MIDI_AUDIO_SERIAL
  if (audioManager.newData)
    for (int i = 0; i < 16; i++) {
      peaks[lastPeaksID][i] = audioManager.peaks[i];
    }

  int peaksID;

  for (uint8_t x = 0; x < CUBEWIDTH; x++) {
    for (uint8_t z = 0; z < CUBEDEPTH; z++) {
      peaksID = (lastPeaksID - z + 16) % 16;
      float level = x > 15 ? 0 : peaks[peaksID][x];
      int height = level * 50 * CUBEHEIGHT;
      for (int y = 0; y <= CUBEHEIGHT; y++) {
        float bri = y < height ? 100 : 0;
        Color col = Color(y * 15 + z * 5, 100 - z * 4 + 20, max(bri - z * 1.5, 0), HSB_MODE);
        cube->setPixel(x, y, z, col);
      }
    }
  }
  if (audioManager.newData) {
    lastPeaksID++;
    if (lastPeaksID > 15) lastPeaksID = 0;
  }
  audioManager.newData = false;
#endif
}

SpectoManager spectoManager;