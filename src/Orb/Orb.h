#pragma once

#include "CubeDriver.h"

class Orb {
 public:
  Orb();
  void init(float _size, float _spd, float _hue);
  void move(float dt);
  void render();

 private:
  float xPos, yPos, zPos, size, xSpd, ySpd, zSpd;
  Color c;
  float hue;
};
