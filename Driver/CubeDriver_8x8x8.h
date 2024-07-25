#if CUBE8
#pragma once

#include "CubeDriver.h"

#if DITHER
#include <OctoWS2811_dither.h>
#else
#include <OctoWS2811.h>
#endif

#define CUBEWIDTH 8
#define CUBEHEIGHT 8
#define CUBEDEPTH 8

class CubeDriver_8x8x8 : public CubeDriver {
 public:
  CubeDriver_8x8x8() : CubeDriver(CUBEWIDTH, CUBEHEIGHT, CUBEDEPTH){};
  byte setDitherBits(byte ditBits);
  byte getDitherBits();
#if DITHER
  void setBrightness(double bri) { leds->ditherLUTCalc(bri, 2); };
#endif
  void init();

  using CubeDriver::setPixel;
  void setPixel(int id, byte r, byte g, byte b);
  void setPixel(int id, int c);
  Color getPixel(int id);

  bool busy();

 private:
  void show();
  void resetLEDs();
  int getPixelLedId(byte x, byte y, byte z);

  static const int LEDS_PER_CHANNEL = 64;
  int displayMemory[LEDS_PER_CHANNEL * 6];
  int drawingMemory[LEDS_PER_CHANNEL * 6];
#if DITHER
  int writingMemory[LEDS_PER_CHANNEL * 6];
  OctoWS2811_Dither *leds;
#else
  OctoWS2811 *leds;
#endif

  uint32_t bufsize;
  int posLUT[CUBEWIDTH][CUBEHEIGHT][CUBEDEPTH];
};

#endif