#include "SerialStreamManager.h"

#include <EEPROM.h>

#include "Audio\AudioManager.h"
#include "Demo\DemoManager.h"
#include "Driver\CubeDriver.h"

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

void SerialStreamManager::decreaseCubeID() {
  serialStreamManager.setCubeID(constrain(serialStreamManager.getCubeID() - 1, 0, 10));
}

void SerialStreamManager::increaseCubeID() {
  serialStreamManager.setCubeID(constrain(serialStreamManager.getCubeID() + 1, 0, 10));
}

void SerialStreamManager::sendInfo() {
  Serial.printf("CUBE,%i,%i,%i,%i\r\n", getCubeID(), cube->width, cube->height, cube->depth);
}

void SerialStreamManager::update() {
  while (Serial.available()) {
    readSerial();
  }
}

void SerialStreamManager::readSerial() {
  int startChar = Serial.read();

  ///// IMAGE FRAME /////
  if (startChar == '%') {
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
    cube->update(false);

    ///// AUDIO BUFFER /////
  } else if (startChar == '$') {
    elapsedMillis sinceWait = 0;
    while (Serial.available() < AUDIO_BLOCK_SAMPLES * 2) {
      if (sinceWait > 10) {
        Serial.println("not received the expected amount of audio samples");
        Serial.clear();
        return;
      }
    }

    int16_t* buf = audioManager.getBuffer();
    if (buf == NULL) {
      for (int i = 0; i < AUDIO_BLOCK_SAMPLES * 2; i++)
        Serial.read();
      Serial.println("Skipped block");
    } else {
      Serial.readBytes((char*)buf, AUDIO_BLOCK_SAMPLES * 2);
      audioManager.playBuffer();
    }

    ///// BRIGHTNESS /////
  } else if (startChar == 'b') {
    elapsedMillis sinceWait = 0;
    while (Serial.available() < 5) {
      if (sinceWait > 10) {
        Serial.println("not received the expected amount bri chars");
        Serial.clear();
        return;
      }
    }
    float bri = Serial.readString(5).toFloat();
    cube->setBrightness(bri);

    ///// DEVICE INFO /////
  } else if (startChar == '?') {
    // when the video application asks, give it all our info
    // for easy and automatic configuration
    sendInfo();
  }
#ifdef SERIALCONTROL
  else if (startChar == 'f') {
    Serial.printf("FPS: %.2f\r\n", cube->getFPS());
  } else if (startChar == 'p') {
    demoManager.togglePaused();
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
  } else if (startChar == 'c') {
    demoManager.switchAnim(Specto);
  } else if (startChar == '=') {
    demoManager.incBri();
  } else if (startChar == '-') {
    demoManager.decBri();
  } else if (startChar == '[') {
    decreaseCubeID();
  } else if (startChar == ']') {
    increaseCubeID();
  } else if (startChar == '1') {
    Serial.println(cube->setDitherBits(cube->getDitherBits() - 1));
  } else if (startChar == '2') {
    Serial.println(cube->setDitherBits(cube->getDitherBits() + 1));
  }
#endif
  else if (startChar >= 0) {
    // discard unknown characters
  }
}

SerialStreamManager serialStreamManager;