#pragma once

#include <OctoWS2811.h>

#include "CubeDriver.h"

class CubeDriver_OK16 : public CubeDriver {
 public:
  CubeDriver_OK16() : CubeDriver(WIDTH, HEIGHT, DEPTH){};
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

  static const byte WIDTH = 16;
  static const byte HEIGHT = 16;
  static const byte DEPTH = 16;

  static const int LEDS_PER_CHANNEL = 128;
  static const int numPins = 32;
  int displayMemory[LEDS_PER_CHANNEL * numPins * 3 / 4];  // * 3 for three bytes per LED, / 4 for 4 bytes in an int
  int drawingMemory[LEDS_PER_CHANNEL * numPins * 3 / 4];
  OctoWS2811 *leds;

  uint32_t bufsize;
  int posLUT[WIDTH][HEIGHT][DEPTH];
};