#pragma once

#include <Arduino.h>

#include "../Anim.h"

class StreamAnim : public Anim {
 public:
  static void readFrame();
  static void readAudio();

  static byte getCubeID();
  static void setCubeID(byte ID);
  static void shiftCubeID(int val);
  static void sendInfo();

  static void setBri(double v);

 private:
  void _init();
  void _update(bool active);
  void _render();
  const char* getName() { return "Stream"; }
  void userInput(Axis axis, double val);

  static bool waitForData(int bytes, unsigned long time);
  int prevAnim = 0;
  bool forcedAnim = false;
};
