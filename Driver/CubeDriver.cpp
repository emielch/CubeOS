#include "CubeDriver.h"

void CubeDriver::update(bool reset) {
  show();
  if (reset) resetLEDs();
  calcDt();
}

void CubeDriver::setPixel(byte x, byte y, byte z, byte r, byte g, byte b) {
  setPixel(getPixelLedId(x, y, z), r, g, b);
}

void CubeDriver::setPixel(byte x, byte y, byte z, Color c) {
  setPixel(getPixelLedId(x, y, z), c);
}

void CubeDriver::setPixel(byte x, byte y, byte z, int c) {
  setPixel(getPixelLedId(x, y, z), c);
}

void CubeDriver::setPixel(int id, Color c) {
  setPixel(id, c.red(), c.green(), c.blue());
}

Color CubeDriver::getPixel(byte x, byte y, byte z) {
  return getPixel(getPixelLedId(x, y, z));
}

void CubeDriver::calcDt() {
  dt = sinceDtCalc / 1000000.;  // assume one frame per second
  sinceDtCalc = 0;
}
float CubeDriver::getFPS() {
  return 1 / dt;
}