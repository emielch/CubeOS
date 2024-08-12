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
  static void enableDemo();
  static void disableDemo();
  void switchAnim(DemoAnim d);
  void adjBri(int v);
  static void incBri();
  static void decBri();
  void setBri(double bri, bool demo);
  static void nextDemo();
  static void prevDemo();
  void togglePaused() { paused = !paused; }
  bool getDemoRunning() { return demoRunning; }
  bool getDemoEnabled() { return demoEnabled; }

 private:
  double demoBri, streamBri;
  DemoAnim currAnim;
  void startDemo();
  void stopDemo();
  bool demoRunning, demoEnabled;
  bool paused = false;
  void (*renderInterrupt)();
  static void emptyFunct() {}
};

extern DemoManager demoManager;
