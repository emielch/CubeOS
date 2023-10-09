#pragma once

#include <Arduino.h>

enum DemoAnim {
  Orbs,
  Rainbow,
  Sine
};

class DemoManager {
 public:
  void init(void (*_renderInterrupt)());
  void update();
  void enableDemo();
  void disableDemo();
  void switchAnim(DemoAnim d);
  void adjBri(int v);
  float getBri() { return brightness; }

 private:
  float brightness = 50;
  DemoAnim currAnim;
  void startDemo();
  void stopDemo();
  bool demoRunning, demoEnabled;
  void (*renderInterrupt)();
};

extern DemoManager demoManager;
