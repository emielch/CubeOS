#if CUBE16
#pragma once

#include "CubeDriver.h"

#if DITHER
#include <OctoWS2811_Dither.h>
#else
#include <OctoWS2811.h>
#endif

#define CUBEWIDTH 16
#define CUBEHEIGHT 16
#define CUBEDEPTH 16

class CubeDriver_OK16 : public CubeDriver {
 public:
  CubeDriver_OK16() : CubeDriver(CUBEWIDTH, CUBEHEIGHT, CUBEDEPTH){};
  byte setDitherBits(byte ditBits);
  byte getDitherBits();
#if DITHER
  void setBrightness(double bri) { leds->ditherLUTCalc(bri); };
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

  static const int LEDS_PER_CHANNEL = 128;
  static const int numPins = 32;
  int displayMemory[LEDS_PER_CHANNEL * numPins * 3 / 4];  // * 3 for three bytes per LED, / 4 for 4 bytes in an int
  int drawingMemory[LEDS_PER_CHANNEL * numPins * 3 / 4];
#if DITHER
  OctoWS2811_Dither *leds;
#else
  OctoWS2811 *leds;
#endif

  uint32_t bufsize;
  int posLUT[CUBEWIDTH][CUBEHEIGHT][CUBEDEPTH];
};

#endif