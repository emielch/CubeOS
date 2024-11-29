#pragma once

#include <Arduino.h>

#include "Driver/CubeDriver.h"

class CubeOS {
 public:
  void init();
  void update();
  void renderInterrupt() {};

  void startStream();
  void stopStream();

  void enableAnim();
  void disableAnim();
  bool getAnimEnabled() { return animEnabled; }

  void setBri(double bri, bool stream = false);
  void adjBri(double v);

 private:
  double animBri, streamBri;
  bool streaming, animEnabled;
};

extern CubeOS cubeOS;
extern CubeDriver* cube;