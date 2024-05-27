#pragma once

#include <Arduino.h>

#ifdef USB_MIDI_AUDIO_SERIAL
#include "Audio\AudioManager.h"
#endif
#include "Demo\DemoManager.h"
#include "Driver.h"
#include "SerialStreamManager.h"

class CubeOS {
 public:
  void init();
  void update();

 private:
};

extern CubeOS cubeOS;