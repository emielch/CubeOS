#include "SerialStreamManager.h"

#include <EEPROM.h>

#include "Audio/AudioManager.h"
#include "Demo/DemoManager.h"
#include "Driver/CubeDriver.h"
#include "Time/TimeManager.h"

// reboot is the same for all ARM devices
#define CPU_RESTART_ADDR ((uint32_t*)0xE000ED0C)
#define CPU_RESTART_VAL (0x5FA0004)
#define REBOOT (*CPU_RESTART_ADDR = CPU_RESTART_VAL)

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
  Serial.printf("CUBE,%i,%i,%i,%i\r\n", getCubeID(), CUBEWIDTH, CUBEHEIGHT, CUBEDEPTH);
}

void SerialStreamManager::update() {
  while (Serial.available() > 0) {
    readSerial();
  }
  if (unknownCount > 0 && sinceUnknownChar > 100) {
    Serial.printf("Received %i unkown chars\r\n", unknownCount);
    unknownCount = 0;
  }
  if (Serial.available() < 0) {
    Serial.println("Serial.available() negative; REBOOTING");
    delay(500);
    REBOOT;
  }
}

bool SerialStreamManager::waitForData(int bytes, unsigned long time) {
  elapsedMillis sinceWait = 0;
  while (Serial.available() < bytes) {
    if (sinceWait > time) {
      return false;
    }
  }
  return true;
}

void SerialStreamManager::readSerial() {
  int startChar = Serial.read();

  ///// IMAGE FRAME /////
  if (startChar == '%') {
    for (int z = 0; z < CUBEDEPTH; z++)
      for (int y = 0; y < CUBEHEIGHT; y++)
        for (int x = 0; x < CUBEWIDTH; x++) {
          if (!waitForData(3, 100)) {
            Serial.clear();
            Serial.println("not received the expected amount of image samples");
            return;
          }
          cube->setPixel(x, y, z, Serial.read(), Serial.read(), Serial.read());
        }
    sinceNewFrame = 0;
    cube->update(false);
  }
#ifdef USB_MIDI_AUDIO_SERIAL
  ///// AUDIO BUFFER /////
  else if (startChar == '$') {
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
#endif
  ///// BRIGHTNESS /////
  else if (startChar == 'b' || startChar == 'B') {
    elapsedMillis sinceWait = 0;
    while (Serial.available() < 5) {
      if (sinceWait > 10) {
        Serial.println("not received the expected amount bri chars");
        Serial.clear();
        return;
      }
    }
    float bri = Serial.readString(5).toFloat();
    demoManager.setBri(bri, startChar == 'B');

    ///// DEVICE INFO /////
  } else if (startChar == '?') {
    // when the video application asks, give it all our info
    // for easy and automatic configuration
    sendInfo();
  }
#ifdef SERIALCONTROL
  else if (startChar == '!') {
    Serial.println("REBOOTING");
    delay(500);
    REBOOT;
  } else if (startChar == 'f') {
    Serial.printf("FPS: %.2f\r\n", cube->getFPS());
    timeManager.printCurrTime();
  } else if (startChar == 'p') {
    demoManager.togglePaused();
  } else if (startChar == 'd') {
    demoManager.enableDemo();
    timeManager.forceOn();
  } else if (startChar == 'x') {
    demoManager.disableDemo();
    timeManager.forceOff();
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
    Serial.println(cube->setDitherBits(max(cube->getDitherBits() - 1, 0)));
  } else if (startChar == '2') {
    Serial.println(cube->setDitherBits(cube->getDitherBits() + 1));
  } else if (startChar == 'q') {
    REBOOT;
  }
#endif
  else if (startChar >= 0) {
    // count and discard unknown characters
    unknownCount++;
    sinceUnknownChar = 0;
  }
}

SerialStreamManager serialStreamManager;