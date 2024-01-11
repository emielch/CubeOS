#if CUBE16

#include "CubeDriver_OK16.h"

void CubeDriver_OK16::init() {
  bufsize = LEDS_PER_CHANNEL * numPins * 3;
  const int config = WS2811_GRB | WS2811_800kHz;
#if ESP_AUDIO
  byte pinList[numPins] = {33, 32, 34, 31, 35, 30, 36, 29, 37, 25, 38, 26, 39, 27, 40, 28, 41, 10, 13, 9, 14, 24, 15, 6, 16, 5, 17, 4, 18, 3, 19, 2};
#else
  byte pinList[numPins] = {33, 32, 34, 31, 35, 30, 36, 29, 37, 25, 38, 26, 39, 27, 40, 28, 41, 10, 13, 9, 14, 8, 15, 6, 16, 5, 17, 4, 18, 3, 19, 2};
#endif
#if DITHER
  leds = new OctoWS2811_Dither(LEDS_PER_CHANNEL, displayMemory, writingMemory, drawingMemory, config, 2, numPins, pinList);
#else
  leds = new OctoWS2811(LEDS_PER_CHANNEL, displayMemory, drawingMemory, config, numPins, pinList);
#endif
  leds->begin();

  for (int z = 0; z < depth; z++) {
    for (int x = 0; x < width; x++) {
      for (int y = 0; y < height; y++) {
        int id = z * LEDS_PER_CHANNEL * 2;

        if (x < width / 2) {
          id += x * height;
          id += (x % 2) ? (height - 1 - y) : y;
        } else {
          id += (width - 1 - x + width / 2) * height;
          id += (x % 2) ? y : (height - 1 - y);
        }

        posLUT[x][y][z] = id;
      }
    }
  }
}

byte CubeDriver_OK16::setDitherBits(byte ditBits) {
#if DITHER
  return leds->setDitherBits(ditBits);
#endif
  return 0;
}

byte CubeDriver_OK16::getDitherBits() {
#if DITHER
  return leds->getDitherBits();
#endif
  return 0;
}

bool CubeDriver_OK16::setPixel(int id, byte r, byte g, byte b, bool checkDiff) {
  if (id == -1) return false;
  if (checkDiff) {
    int oldC = leds->getPixel(id);
    int newC = leds->color(r, g, b);
    leds->setPixel(id, newC);
    return newC != oldC;
  }
  leds->setPixel(id, r, g, b);
  return false;
}

bool CubeDriver_OK16::setPixel(int id, int c, bool checkDiff) {
  if (id == -1) return false;
  if (checkDiff) {
    int oldC = leds->getPixel(id);
    leds->setPixel(id, c);
    return c != oldC;
  }
  leds->setPixel(id, c);
  return false;
}

Color CubeDriver_OK16::getPixel(int id) {
  if (id == -1) return Color(0, 0, 0, RGB_MODE);

  uint32_t conn = leds->getPixel(id);  // retrieve the color that has already been saved
  byte b = conn & 255;                 // unpack the color
  byte g = conn >> 8 & 255;
  byte r = conn >> 16 & 255;
  Color c(r, g, b, RGB_MODE);
  return c;
}

bool CubeDriver_OK16::busy() {
  return leds->busy();
}

void CubeDriver_OK16::show() {
  leds->show();
}

void CubeDriver_OK16::resetLEDs() {
  memset(drawingMemory, 0, bufsize);
}

int CubeDriver_OK16::getPixelLedId(byte x, byte y, byte z) {
  if (x >= width || y >= height || z >= depth) return -1;
  return posLUT[x][y][z];
}

#endif