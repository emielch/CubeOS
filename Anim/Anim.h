#pragma once

#include <Arduino.h>

#include "CubeOS\CubeOS.h"

enum Axis {
  X,
  Y,
  Z
};

class Anim {
 public:
  void init();
  void update(bool active);
  void render();

  void setId(int _id) { id = _id; }
  int getId() { return id; }

  virtual const char* getName() = 0;

  virtual void userInput(Axis axis, double val) {};

 private:
  int id;
  virtual void _init() = 0;
  virtual void _update(bool active) = 0;
  virtual void _render() = 0;
};
