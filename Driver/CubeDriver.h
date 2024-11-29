#pragma once

#include <Arduino.h>

#include "../Color/Color.h"

#if CUBE8
#define CUBEWIDTH 8
#define CUBEHEIGHT 8
#define CUBEDEPTH 8
#elif CUBE16
#define CUBEWIDTH 16
#define CUBEHEIGHT 16
#define CUBEDEPTH 16
#elif CUBE25
#define CUBEWIDTH 25
#define CUBEHEIGHT 25
#define CUBEDEPTH 25
#endif

class CubeDriver {
 public:
  byte setDitherBits(byte ditBits);
  byte getDitherBits();
  void setBrightness(double bri);

  void init();
  void update(bool reset = true);

  void setPixel(byte x, byte y, byte z, byte r, byte g, byte b);
  void setPixel(byte x, byte y, byte z, Color c);
  void setPixel(byte x, byte y, byte z, int c);
  void setPixel(int id, Color c);

  void setPixel(int id, byte r, byte g, byte b);
  void setPixel(int id, int c);

  Color getPixel(byte x, byte y, byte z);
  Color getPixel(int id);

  float getDt() { return dt; }

  bool busy();
  float getFPS();
  unsigned long getSinceUpdate() { return sinceDtCalc; }

#if !DITHER
 protected:
  double brightness = 1;
#endif

 private:
  void show();
  void resetLEDs();
  int getPixelLedId(byte x, byte y, byte z);

  float dt = 0;
  void calcDt();

  elapsedMicros sinceDtCalc = 0;  // variable to keep track of the loops per second
};