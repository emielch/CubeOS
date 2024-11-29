#pragma once

#include "Arduino.h"

enum ColorMode {
  RGB,
  HSB
};

// ---- color stuff ----

struct RGBCol {
  byte r;  // 255
  byte g;  // 255
  byte b;  // 255
};

struct HSBCol {
  int h;   // 360
  byte s;  // 100
  byte b;  // 100
};

class Color {
 public:
  Color();
  Color(int v1, byte v2, byte v3, ColorMode mode = RGB);

  void setRGB(byte r, byte g, byte b);
  void setHSB(unsigned int h, byte s, byte b);

  byte red();
  byte green();
  byte blue();
  int hue();
  byte sat();
  byte bri();

  void add(Color toAdd, float fadeFac);
  void add(Color toAdd);
  void addHDR(Color toAdd, float fadeFac);
  void multiply(Color toMult, float fadeFac);
  void multiply(Color toMult);
  void multiply(float multFac);
  void fade(Color toFade, float fadeFac);
  void fade(Color c1, Color c2, float fadeFac);

 private:
  RGBCol RGB_color;
  HSBCol HSB_color;
  bool RGB_updated;
  bool HSB_updated;

  HSBCol RGBtoHSB(RGBCol *color);
  RGBCol HSBtoRGB(HSBCol *color);

  void updateHSB();
  void updateRGB();
};