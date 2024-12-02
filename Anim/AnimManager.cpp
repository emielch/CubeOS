#include "AnimManager.h"

#include "Off/OffAnim.h"
#include "Orbs/OrbsAnim.h"
#include "Rainbow/RainbowAnim.h"
#include "Sine/SineAnim.h"
#include "Specto/SpectoAnim.h"
#include "Stream/StreamAnim.h"

RainbowAnim rainbow;
SineAnim sine;
OrbsAnim orbs;
SpectoAnim specto;
StreamAnim stream;
OffAnim off;

void AnimManager::init() {
  sine.init();
  orbs.init();
  rainbow.init();
  specto.init();
  stream.init();
  off.init();

  for (int i = 0; i < animAm; i++) {
    allAnims[i]->setId(i);
  }
}

void AnimManager::update() {
  for (int i = 0; i < animAm; i++) {
    allAnims[i]->update(i == currAnimID);
  }
  allAnims[currAnimID]->render();
  cube->update();
}

void AnimManager::registerAnim(Anim* anim) {
  if (animAm >= MAX_ANIMS) {
    while (true) {
      Serial.print("Too many Anims! Halting! ");
      Serial.println(anim->getName());
      delay(1000);
    }
  }
  Serial.print("Registered: ");
  Serial.println(anim->getName());
  allAnims[animAm++] = anim;
}

void AnimManager::shiftAnim(int step) {
  currAnimID = (currAnimID + animAm + step) % animAm;
  Serial.printf("%i: %s\r\n", currAnimID, allAnims[currAnimID]->getName());
}

void AnimManager::setAnim(int id) {
  if (id < 0 || id >= animAm) return;
  currAnimID = id;
  Serial.printf("%i: %s\r\n", currAnimID, allAnims[currAnimID]->getName());
}

void AnimManager::userInput(Axis axis, double val) {
  allAnims[currAnimID]->userInput(axis, val);
};

AnimManager animManager;