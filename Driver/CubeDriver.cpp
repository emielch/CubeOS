#include "CubeDriver.h"

void CubeDriver::update(bool reset) {
  show();
  if (reset) resetLEDs();
  calcDt();
}

bool CubeDriver::setPixel(byte x, byte y, byte z, byte r, byte g, byte b, bool checkDiff) {
  return setPixel(getPixelLedId(x, y, z), r, g, b, checkDiff);
}

bool CubeDriver::setPixel(byte x, byte y, byte z, Color c, bool checkDiff) {
  return setPixel(getPixelLedId(x, y, z), c, checkDiff);
}

bool CubeDriver::setPixel(byte x, byte y, byte z, int c, bool checkDiff) {
  return setPixel(getPixelLedId(x, y, z), c, checkDiff);
}

bool CubeDriver::setPixel(int id, Color c, bool checkDiff) {
  return setPixel(id, c.red(), c.green(), c.blue(), checkDiff);
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