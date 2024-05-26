#if CUBE25

#include "CubeDriver_Q25.h"

void CubeDriver_Q25::init() {
  bufsize = LEDS_PER_CHANNEL * numPins * 16 * 3;
  const int config = WS2811_GRB | WS2811_800kHz;
  byte pinList[numPins] = {6, 7, 8, 9, 34, 35, 36, 37};
  leds = new ShiftWS2811(LEDS_PER_CHANNEL, displayMemory, drawingMemory, config, numPins, pinList);
  leds->begin();

  for (int z = 0; z < depth; z++) {
    for (int x = 0; x < width; x++) {
      for (int y = 0; y < height; y++) {
        int id = y;
        id += 15000 - z * 625;  // 24*25*25 - z*25*25;
        id += 600 - x * 25;     // 25*24 - x*25;

        posLUT[x][y][z] = id;
      }
    }
  }
}

byte CubeDriver_Q25::setDitherBits(byte ditBits) {
  return leds->setDitherBits(ditBits);
}

byte CubeDriver_Q25::getDitherBits() {
  return leds->getDitherBits();
}

void CubeDriver_Q25::setPixel(int id, byte r, byte g, byte b) {
  if (id == -1) return;
  leds->setPixel(id, r, g, b);
}

void CubeDriver_Q25::setPixel(int id, int c) {
  if (id == -1) return;
  leds->setPixel(id, c);
}

Color CubeDriver_Q25::getPixel(int id) {
  if (id == -1) return Color(0, 0, 0, RGB_MODE);

  uint32_t conn = leds->getPixel(id);  // retrieve the color that has already been saved
  byte b = conn & 255;                 // unpack the color
  byte g = conn >> 8 & 255;
  byte r = conn >> 16 & 255;
  Color c(r, g, b, RGB_MODE);
  return c;
}

bool CubeDriver_Q25::busy() {
  return leds->busy();
}

void CubeDriver_Q25::show() {
  leds->show();
}

void CubeDriver_Q25::resetLEDs() {
  memset(drawingMemory, 0, bufsize);
}

int CubeDriver_Q25::getPixelLedId(byte x, byte y, byte z) {
  if (x >= width || y >= height || z >= depth) return -1;
  return posLUT[x][y][z];
}

#endif