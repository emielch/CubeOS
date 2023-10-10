#include "SerialStreamManager.h"

#include <EEPROM.h>

#include "Driver\CubeDriver.h"
#include "Demo\DemoManager.h"

extern CubeDriver* cube;

void SerialStreamManager::init() {
  Serial.setTimeout(50);
}

byte SerialStreamManager::getCubeID() {
  byte cubeID = 0;
  EEPROM.get(64, cubeID);
  return cubeID;
}

void SerialStreamManager::setCubeID(byte ID) {
  EEPROM.put(64, ID);
  sendInfo();
}

void SerialStreamManager::sendInfo() {
  Serial.printf("CUBE,%i,%i,%i,%i\r\n", getCubeID(), cube->width, cube->height, cube->depth);
}

void SerialStreamManager::update() {
  int startChar = Serial.read();

  if (startChar == '%') {
    // receive a frame
    for (int z = 0; z < cube->depth; z++)
      for (int y = 0; y < cube->height; y++)
        for (int x = 0; x < cube->width; x++) {
          elapsedMillis sinceWait = 0;
          while (Serial.available() < 3) {
            if (sinceWait > 1000) {
              return;
            }
          }
          cube->setPixel(x, y, z, Serial.read(), Serial.read(), Serial.read());
        }
    sinceNewFrame = 0;
    cube->update();

  } else if (startChar == '?') {
    // when the video application asks, give it all our info
    // for easy and automatic configuration
    sendInfo();
  } else if (startChar == 'd') {
    demoManager.enableDemo();
  } else if (startChar == 'x') {
    demoManager.disableDemo();
  } else if (startChar == 'r') {
    demoManager.switchAnim(Rainbow);
  } else if (startChar == 'o') {
    demoManager.switchAnim(Orbs);
  } else if (startChar == 's') {
    demoManager.switchAnim(Sine);
  } else if (startChar == '=') {
    demoManager.adjBri(1);
  } else if (startChar == '-') {
    demoManager.adjBri(-1);
  } else if (startChar == '[') {
    setCubeID(getCubeID() - 1);
  } else if (startChar == ']') {
    setCubeID(getCubeID() + 1);
  } else if (startChar >= 0) {
    // discard unknown characters
  }
}

SerialStreamManager serialStreamManager;