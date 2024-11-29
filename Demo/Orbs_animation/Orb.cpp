#include "Orb.h"

#include "CubeOS\Demo\DemoManager.h"
#include "CubeOS\Driver\CubeDriver.h"

extern CubeDriver* cube;

void Orb::init(float _size, float _spd, float _hue) {
  reset(-1, -1, -1);

  _spd *= 1000;
  spd.x = random(-_spd, _spd) / 1000.;
  spd.y = random(-_spd, _spd) / 1000.;
  spd.z = random(-_spd, _spd) / 1000.;

  size = _size / 2.;
  hue = _hue;
}

void Orb::move(float dt) {
  if (dt > 0.1) dt = 0.1;
  hue += 5 * dt;
  if (hue >= 360) hue -= 360;
  c.setHSB(hue, 100, 100);

  Vector3 dtSpd = spd;
  dtSpd.mult(dt);
  pos.add(dtSpd);

  // /// check for reset
  // if (pos.x > CUBEWIDTH + size) {
  //   reset(-size, -1, -1);
  // } else if (pos.x < -size) {
  //   reset(CUBEWIDTH + size, -1, -1);
  // } else if (pos.y > CUBEHEIGHT + size) {
  //   reset(-1, -size, -1);
  // } else if (pos.y < -size) {
  //   reset(-1, CUBEHEIGHT + size, -1);
  // } else if (pos.z > CUBEDEPTH + size) {
  //   reset(-1, -1, -size);
  // } else if (pos.z < -size) {
  //   reset(-1, -1, CUBEDEPTH + size);
  // }

  float bouncePow = 10;
  if (pos.x > CUBEWIDTH) {
    spd.x -= bouncePow * dt;
  } else if (pos.x < 0) {
    spd.x += bouncePow * dt;
  }
  if (pos.y > CUBEHEIGHT) {
    spd.y -= bouncePow * dt;
  } else if (pos.y < 0) {
    spd.y += bouncePow * dt;
  }
  if (pos.z > CUBEDEPTH) {
    spd.z -= bouncePow * dt;
  } else if (pos.z < 0) {
    spd.z += bouncePow * dt;
  }
}

void Orb::reset(float x, float y, float z) {
  if (x == -1) x = random(0, CUBEWIDTH * 1000) / 1000.;
  if (y == -1) y = random(0, CUBEHEIGHT * 1000) / 1000.;
  if (z == -1) z = random(0, CUBEDEPTH * 1000) / 1000.;
  pos = {x, y, z};
}

void Orb::translate(Vector3 spd) {
  pos.add(spd);
}

void Orb::rotate(float r) {
  float xNew = (pos.x - CUBEWIDTH * 0.5) * cos(r) - (pos.z - CUBEDEPTH * 0.5) * sin(r);
  float zNew = (pos.x - CUBEWIDTH * 0.5) * sin(r) + (pos.z - CUBEDEPTH * 0.5) * cos(r);

  pos.x = xNew + CUBEWIDTH * 0.5;
  pos.z = zNew + CUBEDEPTH * 0.5;
}

void Orb::scale(float s) {
  s += 1;
  pos.x = (pos.x - CUBEWIDTH * 0.5) * s + CUBEWIDTH * 0.5;
  pos.z = (pos.z - CUBEDEPTH * 0.5) * s + CUBEDEPTH * 0.5;
  size *= s;
  spd.x *= s;
  spd.y *= s;
  spd.z *= s;
}

void Orb::render() {
  int x1 = constrain(pos.x - size, 0, CUBEWIDTH - 1);
  int x2 = constrain(pos.x + size, 0, CUBEWIDTH - 1);
  int y1 = constrain(pos.y - size, 0, CUBEHEIGHT - 1);
  int y2 = constrain(pos.y + size, 0, CUBEHEIGHT - 1);
  int z1 = constrain(pos.z - size, 0, CUBEDEPTH - 1);
  int z2 = constrain(pos.z + size, 0, CUBEDEPTH - 1);

  for (int x = x1; x <= x2; x++) {
    for (int y = y1; y <= y2; y++) {
      for (int z = z1; z <= z2; z++) {
        float Dx = x - pos.x;
        float Dy = y - pos.y;
        float Dz = z - pos.z;
        float dist = sqrt(Dx * Dx + Dy * Dy + Dz * Dz);

        float bri = size - dist;
        bri = bri / size;
        if (bri <= 0) continue;

        Color pixCol = cube->getPixel(x, y, z);
        pixCol.add(c, bri);

        cube->setPixel(x, y, z, pixCol);
      }
    }
  }
}
