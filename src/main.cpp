#include <Arduino.h>
#include <EEPROM.h>

#include "CubeDriver_8x8x8.h"
#include "Orb/Orb.h"

CubeDriver* cube;

const int orbAm = 8;
Orb orbs[orbAm];

elapsedMillis sincePrint = 0;
unsigned long randomSeedVar = 0;

void setup() {
  cube = new CubeDriver_8x8x8();
  cube->init();

  EEPROM.get(0, randomSeedVar);
  randomSeedVar++;
  EEPROM.put(0, randomSeedVar);
  randomSeed(randomSeedVar);
  for (int i = 0; i < orbAm; i++) {
    orbs[i].init(random(300, 850) / 100., random(50, 150) / 100., i * 137.508);
  }
}

void loop() {
  for (int i = 0; i < orbAm; i++) {
    orbs[i].move(cube->getDt());
    orbs[i].render();
  }
  cube->update();


  // for (int y = 0; y < cube->height; y++) {
  //   for (int x = 0; x < cube->width; x++) {
  //     for (int z = 0; z < cube->depth; z++) {
  //       cube->setPixel(x,y,z,0,0,20);
  //     }
  //   }
  //   cube->update();
  //   delay(500);
  // }

  // for (int i = 0; i < cube->totPixels(); i++) {
  //   cube->setPixel((int)i, (byte)0, (byte)0, (byte)20);
  //   cube->update();
  //   delay(5);
  // }

  if (sincePrint > 1000) {
    Serial.print("FPS: ");
    Serial.println(cube->getFPS());
    sincePrint -= 1000;
  }
}