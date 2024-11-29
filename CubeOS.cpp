#include "CubeOS.h"

#include "Anim/AnimManager.h"
#include "SerialStreamManager.h"
#include "Time/TimeManager.h"

#ifdef USB_MIDI_AUDIO_SERIAL
#include "Audio/AudioManager.h"
#endif

#define STREAM_BLACKOUT_DELAY 1500
#define DEMO_DELAY 3000

void CubeOS::init() {
  cube->init();
  serialStreamManager.init();
#ifdef USB_MIDI_AUDIO_SERIAL
  audioManager.init();
#endif
  animManager.init();

#if DITHER
  animBri = 50;
  streamBri = 50;
#else
  animBri = 15;
  streamBri = 15;
#endif
  stopStream();
}

void CubeOS::update() {
  serialStreamManager.update();
#ifdef USB_MIDI_AUDIO_SERIAL
  audioManager.update();
#endif
  timeManager.update();

  if (serialStreamManager.getSinceNewFrame() > STREAM_BLACKOUT_DELAY && streaming) cube->update();  // show black frame when streaming has stopped but anims havent started yet
  if (serialStreamManager.getSinceNewFrame() < STREAM_BLACKOUT_DELAY && !streaming) startStream();
  if (serialStreamManager.getSinceNewFrame() > DEMO_DELAY && streaming) stopStream();

  if (!streaming && !animEnabled) cube->update();  // show black frame if there is nothing to display

  if (animEnabled && !streaming)
    animManager.update();
}

void CubeOS::setBri(double bri, bool stream) {
  double* briPntr = stream ? &streamBri : &animBri;
  *briPntr = constrain(bri, 0, 400);
  if (stream == streaming) cube->setBrightness(*briPntr);
  Serial.println(*briPntr, 1);
}

void CubeOS::adjBri(double v) {
  setBri((streaming ? streamBri : animBri) + v, streaming);
}

void CubeOS::startStream() {
  streaming = true;
  cube->setBrightness(streamBri);
}

void CubeOS::stopStream() {
  streaming = false;
  cube->setBrightness(animBri);
}

void CubeOS::enableAnim() {
  animEnabled = true;
}

void CubeOS::disableAnim() {
  animEnabled = false;
}

CubeOS cubeOS;
CubeDriver* cube = new CubeDriver();