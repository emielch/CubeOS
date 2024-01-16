#pragma once

#include <Arduino.h>

enum DemoAnim {
  Orbs,
  Rainbow,
  Sine,
  Specto,
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
  static void incBri();
  static void decBri();
  static void nextDemo();
  static void prevDemo();
  void togglePaused() { paused = !paused; }
  bool getDemoRunning() { return demoRunning; }

 private:
#if DITHER
  double brightness = 50;
#else
  double brightness = 15;
#endif
  DemoAnim currAnim;
  void startDemo();
  void stopDemo();
  bool demoRunning, demoEnabled;
  bool paused = false;
  void (*renderInterrupt)();
  static void emptyFunct() {}
};

extern DemoManager demoManager;
