#include "AnimManager.h"

#include "Orbs/OrbsAnim.h"
#include "Rainbow/RainbowAnim.h"
#include "Sine/SineAnim.h"
#include "Specto/SpectoAnim.h"

RainbowAnim rainbow;
SineAnim sine;
OrbsAnim orbs;
SpectoAnim specto;

void AnimManager::init() {
  sine.init();
  orbs.init();
  rainbow.init();
  specto.init();
}

void AnimManager::update() {
  allAnims[currAnimID]->update();
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

void AnimManager::changeAnim(int step) {
  currAnimID = (currAnimID + animAm + step) % animAm;
  Serial.printf("%i: %s\r\n", currAnimID, allAnims[currAnimID]->getName());
}

AnimManager animManager;