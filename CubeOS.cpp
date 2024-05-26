#include "CubeOS.h"

#ifdef USB_MIDI_AUDIO_SERIAL
#include "Audio\AudioManager.h"
#endif
#include "Demo\DemoManager.h"
#include "Driver.h"
#include "SerialStreamManager.h"

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
}

CubeOS cubeOS;