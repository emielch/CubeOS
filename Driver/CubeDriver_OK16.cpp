#if CUBE16

#include "CubeDriver.h"

#if DITHER
#include <OctoWS2811_Dither.h>
#else
#include <OctoWS2811.h>
#endif

static const int LEDS_PER_CHANNEL = 128;
static const int numPins = 32;
static int displayMemory[LEDS_PER_CHANNEL * numPins * 3 / 4];  // * 3 for three bytes per LED, / 4 for 4 bytes in an int
static int drawingMemory[LEDS_PER_CHANNEL * numPins * 3 / 4];
#if DITHER
static OctoWS2811_Dither *leds;
#else
static OctoWS2811 *leds;
#endif

uint32_t bufsize;
int posLUT[CUBEWIDTH][CUBEHEIGHT][CUBEDEPTH];

void CubeDriver::init() {
  bufsize = LEDS_PER_CHANNEL * numPins * 3;
  const int config = WS2811_GRB | WS2811_800kHz;
#if ESP_AUDIO
  byte pinList[numPins] = {33, 32, 34, 31, 35, 30, 36, 29, 37, 25, 38, 26, 39, 27, 40, 28, 41, 10, 13, 9, 14, 24, 15, 6, 16, 5, 17, 4, 18, 3, 19, 2};
#else
  byte pinList[numPins] = {33, 32, 34, 31, 35, 30, 36, 29, 37, 25, 38, 26, 39, 27, 40, 28, 41, 10, 13, 9, 14, 8, 15, 6, 16, 5, 17, 4, 18, 3, 19, 2};
#endif
#if DITHER
  leds = new OctoWS2811_Dither(LEDS_PER_CHANNEL, displayMemory, drawingMemory, config, 2, numPins, pinList, 0.95e-6);
#else
  leds = new OctoWS2811(LEDS_PER_CHANNEL, displayMemory, drawingMemory, config, numPins, pinList);
#endif
  leds->begin();

  for (int z = 0; z < CUBEDEPTH; z++) {
    for (int x = 0; x < CUBEWIDTH; x++) {
      for (int y = 0; y < CUBEHEIGHT; y++) {
        int id = z * LEDS_PER_CHANNEL * 2;

        if (x < CUBEWIDTH / 2) {
          id += x * CUBEHEIGHT;
          id += (x % 2) ? (CUBEHEIGHT - 1 - y) : y;
        } else {
          id += (CUBEWIDTH - 1 - x + CUBEWIDTH / 2) * CUBEHEIGHT;
          id += (x % 2) ? y : (CUBEHEIGHT - 1 - y);
        }

        posLUT[x][y][z] = id;
      }
    }
  }
}

byte CubeDriver::setDitherBits(byte ditBits) {
#if DITHER
  return leds->setDitherBits(ditBits);
#endif
  return 0;
}

byte CubeDriver::getDitherBits() {
#if DITHER
  return leds->getDitherBits();
#endif
  return 0;
}

void CubeDriver::setBrightness(double bri) {
#if DITHER
  leds->ditherLUTCalc(bri);
#else
  brightness = bri * 0.01;
#endif
};

void CubeDriver::setPixel(int id, byte r, byte g, byte b) {
  if (id == -1) return;
#if DITHER
  leds->setPixel(id, r, g, b);
#else
  leds->setPixel(id, r * brightness, g * brightness, b * brightness);
#endif
}

void CubeDriver::setPixel(int id, int c) {
  if (id == -1) return;
#if DITHER
  leds->setPixel(id, c);
#else
  byte b = c & 255;  // unpack the color
  byte g = c >> 8 & 255;
  byte r = c >> 16 & 255;
  leds->setPixel(id, r * brightness, g * brightness, b * brightness);
#endif
}

Color CubeDriver::getPixel(int id) {
  if (id == -1) return Color(0, 0, 0, RGB_MODE);

  uint32_t conn = leds->getPixel(id);  // retrieve the color that has already been saved
  byte b = conn & 255;                 // unpack the color
  byte g = conn >> 8 & 255;
  byte r = conn >> 16 & 255;
#if DITHER
  Color c(r, g, b, RGB_MODE);
#else
  Color c(r / brightness, g / brightness, b / brightness, RGB_MODE);
#endif
  return c;
}

bool CubeDriver::busy() {
  return leds->busy();
}

void CubeDriver::show() {
  leds->show();
}

void CubeDriver::resetLEDs() {
  memset(drawingMemory, 0, bufsize);
}

int CubeDriver::getPixelLedId(byte x, byte y, byte z) {
  if (x >= CUBEWIDTH || y >= CUBEHEIGHT || z >= CUBEDEPTH) return -1;
  return posLUT[x][y][z];
}

#endif