#pragma once

#define DITHER 1

#if DITHER
#include <OctoWS2811_dither.h>
#else
#include <OctoWS2811.h>
#endif

#include "CubeDriver\CubeDriver.h"

class CubeDriver_8x8x8 : public CubeDriver {
 public:
  CubeDriver_8x8x8() : CubeDriver(WIDTH, HEIGHT, DEPTH){};
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

  static const byte WIDTH = 8;
  static const byte HEIGHT = 8;
  static const byte DEPTH = 8;

  static const int LEDS_PER_CHANNEL = 64;
  int displayMemory[LEDS_PER_CHANNEL * 6];

#if DITHER
  COL_RGB drawingMemory[LEDS_PER_CHANNEL * 8];
  COL_RGB writingMemory[LEDS_PER_CHANNEL * 8];
  OctoWS2811_Dither *leds;
#else
  int drawingMemory[LEDS_PER_CHANNEL * 6];
  OctoWS2811 *leds;
#endif

  uint32_t bufsize;
  int posLUT[WIDTH][HEIGHT][DEPTH];
};