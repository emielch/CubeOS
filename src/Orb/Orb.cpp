#include "Orb.h"

extern CubeDriver* cube;

Orb::Orb() {
  xSpd = 0;
  ySpd = 0;
  zSpd = 0;
}

void Orb::init(float _size, float _spd, float _hue) {
  xPos = random(1, cube->width - 1);
  yPos = random(1, cube->height - 1);
  zPos = random(1, cube->depth - 1);

  _spd *= 1000;
  xSpd = random(-_spd, _spd) / 1000.;
  ySpd = random(-_spd, _spd) / 1000.;
  zSpd = random(-_spd, _spd) / 1000.;

  Serial.println(xSpd);
  Serial.println(ySpd);
  Serial.println(zSpd);
  Serial.println();

  // if (abs(xSpd) < 1) xSpd = 1;
  // if (abs(ySpd) < 1) ySpd = 1;
  // if (abs(zSpd) < 1) zSpd = 1;

  size = _size;
  hue = _hue;
}

float bouncePow = 10;

void Orb::move(float dt) {
  hue += 5 * dt;
  if (hue >= 360) hue -= 360;
  c.setHSB(hue, 100, 30);

  xPos += xSpd * dt;
  yPos += ySpd * dt;
  zPos += zSpd * dt;

  if (xPos > cube->width) {
    xSpd -= bouncePow * dt;
  } else if (xPos < 0) {
    xSpd += bouncePow * dt;
  }

  if (yPos > cube->height) {
    ySpd -= bouncePow * dt;
  } else if (yPos < 0) {
    ySpd += bouncePow * dt;
  }

  if (zPos > cube->depth) {
    zSpd -= bouncePow * dt;
  } else if (zPos < 0) {
    zSpd += bouncePow * dt;
  }
}

void Orb::render() {
  int x1 = constrain(xPos - size / 2, 0, cube->width - 1);
  int x2 = constrain(xPos + size / 2, 0, cube->width - 1);
  int y1 = constrain(yPos - size / 2, 0, cube->height - 1);
  int y2 = constrain(yPos + size / 2, 0, cube->height - 1);
  int z1 = constrain(zPos - size / 2, 0, cube->depth - 1);
  int z2 = constrain(zPos + size / 2, 0, cube->depth - 1);

  for (int x = x1; x <= x2; x++) {
    for (int y = y1; y <= y2; y++) {
      for (int z = z1; z <= z2; z++) {
        float Dx = x - xPos;
        float Dy = y - yPos;
        float Dz = z - zPos;
        float dist = sqrt(Dx * Dx + Dy * Dy + Dz * Dz);

        float bri = (size / 2) - dist;
        bri = bri / (size / 2);
        if (bri < 0) bri = 0;

        Color pixCol = cube->getPixel(x, y, z);
        pixCol.add(c, bri);

        cube->setPixel(x, y, z, pixCol);
      }
    }
  }
}
