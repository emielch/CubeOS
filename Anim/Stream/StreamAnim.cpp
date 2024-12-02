#include "StreamAnim.h"

#include <EEPROM.h>

#include "../../Audio/AudioManager.h"
#include "../AnimManager.h"

#define STREAM_BLACKOUT_DELAY 1500
#define DEMO_DELAY 3000

byte frameData[CUBEDEPTH * CUBEHEIGHT * CUBEWIDTH * 3];
bool frameAvailable = false;
elapsedMillis sinceFrame = 999990;

void StreamAnim::_init() {
}

void StreamAnim::_update(bool active) {
  if (frameAvailable) {
    if (!forcedAnim) {
      forcedAnim = true;
      prevAnim = animManager.getCurrAnimID();
      animManager.setAnim(getId());
    }
    frameAvailable = false;
  } else {
    if (sinceFrame > DEMO_DELAY) {
      if (forcedAnim && active) {
        animManager.setAnim(prevAnim);
      }
      forcedAnim = false;
    }
  }
}

void StreamAnim::_render() {
  if (sinceFrame > STREAM_BLACKOUT_DELAY) return;

  uint16_t i = 0;
  for (byte z = 0; z < CUBEDEPTH; z++)
    for (byte y = 0; y < CUBEHEIGHT; y++)
      for (byte x = 0; x < CUBEWIDTH; x++) {
        cube->setPixel(x, y, z, frameData[i], frameData[i + 1], frameData[i + 2]);
        i += 3;
      }
}

bool StreamAnim::waitForData(int bytes, unsigned long time) {
  elapsedMillis sinceWait = 0;
  while (Serial.available() < bytes) {
    if (sinceWait > time) {
      return false;
    }
  }
  return true;
}

void StreamAnim::readFrame() {
  for (int i = 0; i < CUBEDEPTH * CUBEHEIGHT * CUBEWIDTH * 3; i += 3) {
    if (!waitForData(3, 100)) {
      Serial.clear();
      Serial.println("not received the expected amount of image samples");
      frameAvailable = false;
      return;
    }
    frameData[i] = Serial.read();
    frameData[i + 1] = Serial.read();
    frameData[i + 2] = Serial.read();
  }
  frameAvailable = true;
  sinceFrame = 0;
}

void StreamAnim::readAudio() {
  int8_t* buf = (int8_t*)audioManager.getBuffer();

  for (int i = 0; i < AUDIO_BLOCK_SAMPLES * 2; i += 2) {
    if (!waitForData(2, 100)) {
      Serial.clear();
      Serial.println("not received the expected amount of audio samples");
      return;
    }
    if (buf == NULL) {
      Serial.read();
      Serial.read();
    } else {
      buf[i] = Serial.read();
      buf[i + 1] = Serial.read();
    }
  }
  if (buf != NULL)
    audioManager.playBuffer();
  else
    Serial.println("Skipped block");
}

byte StreamAnim::getCubeID() {
  byte cubeID = 0;
  EEPROM.get(64, cubeID);
  return cubeID;
}

void StreamAnim::setCubeID(byte ID) {
  EEPROM.put(64, ID);
  sendInfo();
}

void StreamAnim::shiftCubeID(int val) {
  setCubeID(constrain(getCubeID() + val, 0, 10));
}

void StreamAnim::sendInfo() {
  Serial.printf("CUBE,%i,%i,%i,%i\r\n", getCubeID(), CUBEWIDTH, CUBEHEIGHT, CUBEDEPTH);
}