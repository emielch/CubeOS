#pragma once

#include <Arduino.h>

#include "../Color/Color.h"

class CubeDriver {
 public:
  CubeDriver(byte w, byte h, byte d) : width(w), height(h), depth(d){};
  virtual byte setDitherBits(byte ditBits) { return 0; }
  virtual byte getDitherBits() { return 0; }
  virtual void init() = 0;
  void update(bool reset = true);

  bool setPixel(byte x, byte y, byte z, byte r, byte g, byte b, bool checkDiff = false);
  bool setPixel(byte x, byte y, byte z, Color c, bool checkDiff = false);
  bool setPixel(byte x, byte y, byte z, int c, bool checkDiff = false);
  bool setPixel(int id, Color c, bool checkDiff = false);

  virtual bool setPixel(int id, byte r, byte g, byte b, bool checkDiff = false) = 0;
  virtual bool setPixel(int id, int c, bool checkDiff = false) = 0;

  Color getPixel(byte x, byte y, byte z);
  virtual Color getPixel(int id) = 0;

  const byte width;
  const byte height;
  const byte depth;

  float getDt() { return dt; }

  virtual bool busy() = 0;
  float getFPS();
  unsigned long getSinceUpdate() { return sinceDtCalc; }
  int totPixels() { return width * height * depth; }

 private:
  virtual void show() = 0;
  virtual void resetLEDs() = 0;
  virtual int getPixelLedId(byte x, byte y, byte z) = 0;

  float dt = 0;
  void calcDt();

  elapsedMicros sinceDtCalc = 0;  // variable to keep track of the loops per second
};