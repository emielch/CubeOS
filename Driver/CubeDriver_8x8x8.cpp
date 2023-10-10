#include "CubeDriver_8x8x8.h"

void CubeDriver_8x8x8::init() {
  bufsize = LEDS_PER_CHANNEL * 24;
  const int config = WS2811_RGB | WS2811_800kHz;
#if DITHER
  leds = new OctoWS2811_Dither(LEDS_PER_CHANNEL, displayMemory, writingMemory, drawingMemory, config);
#else
  leds = new OctoWS2811(LEDS_PER_CHANNEL, displayMemory, drawingMemory, config);
#endif
  leds->begin();

  for (int z = 0; z < depth; z++) {
    for (int x = 0; x < width; x++) {
      for (int y = 0; y < height; y++) {
        int id = z * LEDS_PER_CHANNEL;
        id += (width - 1) * height - x * height;
        id += x % 2 ? y : height - 1 - y;
        posLUT[x][y][z] = id;
      }
    }
  }
}

void CubeDriver_8x8x8::setPixel(int id, byte r, byte g, byte b) {
  if (id == -1) return;
  leds->setPixel(id, r, g, b);
}

void CubeDriver_8x8x8::setPixel(int id, int c) {
  if (id == -1) return;
  leds->setPixel(id, c);
}

Color CubeDriver_8x8x8::getPixel(int id) {
  if (id == -1) return Color(0, 0, 0, RGB_MODE);

  uint32_t conn = leds->getPixel(id);  // retrieve the color that has already been saved
  byte b = conn & 255;                 // unpack the color
  byte g = conn >> 8 & 255;
  byte r = conn >> 16 & 255;
  Color c(r, g, b, RGB_MODE);
  return c;
}

bool CubeDriver_8x8x8::busy() {
  return leds->busy();
}

void CubeDriver_8x8x8::show() {
  leds->show();
}

void CubeDriver_8x8x8::resetLEDs() {
  memset(drawingMemory, 0, bufsize);
}

int CubeDriver_8x8x8::getPixelLedId(byte x, byte y, byte z) {
  if (x >= width || y >= height || z >= depth) return -1;
  return posLUT[x][y][z];
}