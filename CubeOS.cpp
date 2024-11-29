#include "CubeOS.h"

void CubeOS::init() {
  cube->init();
  serialStreamManager.init();
#ifdef USB_MIDI_AUDIO_SERIAL
  audioManager.init();
#endif
  demoManager.init();
}

void CubeOS::update() {
  serialStreamManager.update();
#ifdef USB_MIDI_AUDIO_SERIAL
  audioManager.update();
#endif
  demoManager.update();
  timeManager.update();
}

CubeOS cubeOS;
CubeDriver* cube = new CubeDriver();