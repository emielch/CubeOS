#include "CubeOS.h"

#include "Anim/AnimManager.h"
#include "SerialStreamManager.h"
#include "Time/TimeManager.h"

#ifdef USB_MIDI_AUDIO_SERIAL
#include "Audio/AudioManager.h"
#endif

void CubeOS::init() {
  cube->init();
  serialStreamManager.init();
#ifdef USB_MIDI_AUDIO_SERIAL
  audioManager.init();
#endif
  animManager.init();

#if DITHER
  bri = 50;
#else
  bri = 15;
#endif
  cube->setBrightness(bri);
}

void CubeOS::update() {
  serialStreamManager.update();
#ifdef USB_MIDI_AUDIO_SERIAL
  audioManager.update();
#endif
  timeManager.update();

  animManager.update();
}

void CubeOS::setBri(double v) {
  bri = constrain(v, 0, 400);
  cube->setBrightness(bri);
  Serial.println(bri, 1);
}

void CubeOS::adjBri(double v) {
  setBri(bri + v);
}

CubeOS cubeOS;
CubeDriver* cube = new CubeDriver();