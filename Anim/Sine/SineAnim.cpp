#include "SineAnim.h"

#include "math8.h"

void SineAnim::_init() {
}

void SineAnim::_update() {
  // phaseSpd += touchbarManager.getSpd().x * 0.5;
  // phaseSpd = constrain(phaseSpd, 0, 10);
  // hueOffset += touchbarManager.getSpd().z * 10;
  // hueScale += touchbarManager.getRotationSpd() * 10;

  phase += phaseSpd * cube->getDt();
  while (phase > 2 * PI) phase -= 2 * PI;

  for (uint8_t x = 0; x < CUBEWIDTH; x++) {
    cubeOS.renderInterrupt();
    // convert cube x to floating point coordinate between x_min and x_max
    float xprime = mapf(x, 0, CUBEWIDTH - 1, x_min, x_max);
    for (uint8_t z = 0; z < CUBEDEPTH; z++) {
      // convert cube z to floating point coordinate between z_min and z_max
      float zprime = mapf(z, 0, CUBEDEPTH - 1, z_min, z_max);
      // determine y floating point coordinate
      float yprime = sinf(phase + sqrtf(xprime * xprime + zprime * zprime));
      // convert floating point y back to cube y
      float y = mapf(yprime, -1, 1, 0, CUBEHEIGHT - 1);
      // display voxel on the cube
      // Color c = Color((hue16 >> 8) + y * 10, &RainbowGradientPalette[0]);
      int fy = floor(y) - 1;
      int cy = ceil(y) + 1;
      for (int _y = fy; _y <= cy; _y++) {
        float bri = 1 - max(abs(y - _y) * 0.5, 0);
        Color col = Color(hueOffset + y * hueScale, 100, 100 * bri, HSB);
        cube->setPixel(x, _y, z, col);
      }
    }
  }
}