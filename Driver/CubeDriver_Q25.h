#if CUBE25
#pragma once

#include <ShiftWS2811.h>

#include "CubeDriver.h"

#define CUBEWIDTH 25
#define CUBHEIGHT 25
#define CUBDEPTH 25

class CubeDriver_Q25 : public CubeDriver {
 public:
  CubeDriver_Q25() : CubeDriver(CUBEWIDTH, CUBHEIGHT, CUBDEPTH){};
  byte setDitherBits(byte ditBits);
  byte getDitherBits();
#if DITHER
  void setBrightness(double bri) { leds->setBrightness(bri); };
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

  static const int numPins = 8;
  static const int LEDS_PER_CHANNEL = 125;
  int displayMemory[LEDS_PER_CHANNEL * numPins * 16 * 3 / 4];  // *16 for 16 pins on a shiftregister
  int drawingMemory[LEDS_PER_CHANNEL * numPins * 16 * 3 / 4];

  ShiftWS2811 *leds;

  uint32_t bufsize;
  int posLUT[CUBEWIDTH][CUBHEIGHT][CUBDEPTH];
};

#endif