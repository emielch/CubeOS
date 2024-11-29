#if CUBE25

#include <ShiftWS2811.h>

#include "CubeDriver.h"

static const int numPins = 8;
static const int LEDS_PER_CHANNEL = 125;
static int frontMemory[LEDS_PER_CHANNEL * numPins * 16 * 3 / 4];  // *16 for 16 pins on a shiftregister
static int backMemory[LEDS_PER_CHANNEL * numPins * 16 * 3 / 4];
static int drawMemory[LEDS_PER_CHANNEL * numPins * 16 * 3 / 4];

static ShiftWS2811 *leds;

static uint32_t bufsize;
static int posLUT[CUBEWIDTH][CUBEHEIGHT][CUBEDEPTH];

void CubeDriver::init() {
  bufsize = LEDS_PER_CHANNEL * numPins * 16 * 3;
  const int config = WS2811_GRB | WS2811_800kHz;
  byte pinList[numPins] = {6, 7, 8, 9, 34, 35, 36, 37};
  leds = new ShiftWS2811(LEDS_PER_CHANNEL, frontMemory, backMemory, drawMemory, config, numPins, pinList);
  leds->begin();

  for (int z = 0; z < CUBEDEPTH; z++) {
    for (int x = 0; x < CUBEWIDTH; x++) {
      for (int y = 0; y < CUBEHEIGHT; y++) {
        int id = y;
        id += 15000 - z * 625;  // 24*25*25 - z*25*25;
        id += 600 - x * 25;     // 25*24 - x*25;

        posLUT[x][y][z] = id;
      }
    }
  }
}

byte CubeDriver::setDitherBits(byte ditBits) {
  return leds->setDitherBits(ditBits);
}

byte CubeDriver::getDitherBits() {
  return leds->getDitherBits();
}

void CubeDriver::setBrightness(double bri) {
  leds->setBrightness(bri);
};

void CubeDriver::setPixel(int id, byte r, byte g, byte b) {
  if (id == -1) return;
  leds->setPixel(id, r, g, b);
}

void CubeDriver::setPixel(int id, int c) {
  if (id == -1) return;
  leds->setPixel(id, c);
}

Color CubeDriver::getPixel(int id) {
  if (id == -1) return Color(0, 0, 0, RGB);

  uint32_t conn = leds->getPixel(id);  // retrieve the color that has already been saved
  byte b = conn & 255;                 // unpack the color
  byte g = conn >> 8 & 255;
  byte r = conn >> 16 & 255;
  Color c(r, g, b, RGB);
  return c;
}

bool CubeDriver::busy() {
  return leds->busy();
}

void CubeDriver::show() {
  leds->show();
}

void CubeDriver::resetLEDs() {
  memset(drawMemory, 0, bufsize);
}

int CubeDriver::getPixelLedId(byte x, byte y, byte z) {
  if (x >= CUBEWIDTH || y >= CUBEHEIGHT || z >= CUBEDEPTH) return -1;
  return posLUT[x][y][z];
}

#endif