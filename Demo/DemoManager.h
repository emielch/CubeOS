#pragma once

#include <Arduino.h>

enum DemoAnim {
  Orbs,
  Rainbow,
  Sine,
  DemoAm
};

class DemoManager {
 public:
  void init(void (*_renderInterrupt)() = nullptr);
  void update();
  void enableDemo();
  void disableDemo();
  void switchAnim(DemoAnim d);
  void adjBri(int v);
  float getBri() { return brightness; }
  static void nextDemo();
  static void prevDemo();
  void togglePaused() { paused = !paused; }
  bool getDemoRunning() { return demoRunning; }

 private:
  float brightness = 35;
  DemoAnim currAnim;
  void startDemo();
  void stopDemo();
  bool demoRunning, demoEnabled;
  bool paused = false;
  void (*renderInterrupt)();
  static void emptyFunct() {}
};

extern DemoManager demoManager;
