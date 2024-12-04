#include "SerialStreamManager.h"

#include "Anim/AnimManager.h"
#include "Anim/Stream/StreamAnim.h"
#include "CubeOS.h"
#include "Time/TimeManager.h"

// reboot is the same for all ARM devices
#define CPU_RESTART_ADDR ((uint32_t*)0xE000ED0C)
#define CPU_RESTART_VAL (0x5FA0004)
#define REBOOT (*CPU_RESTART_ADDR = CPU_RESTART_VAL)

void SerialStreamManager::init() {
  Serial.setTimeout(50);
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

void SerialStreamManager::readSerial() {
  int startChar = Serial.read();

  ///// IMAGE FRAME /////
  if (startChar == '%')
    StreamAnim::readFrame();

///// AUDIO BUFFER /////
#ifdef USB_MIDI_AUDIO_SERIAL
  else if (startChar == '$')
    StreamAnim::readAudio();
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
    if (startChar == 'B')
      cubeOS.setBri(bri);
    else
      StreamAnim::setBri(bri);
  }

  ///// DEVICE INFO /////
  else if (startChar == '?') {
    // when the video application asks, give it all our info
    // for easy and automatic configuration
    StreamAnim::sendInfo();
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
    animManager.togglePaused();
  } else if (startChar == 'd') {
    animManager.enable();
    timeManager.forceOn();
  } else if (startChar == 'x') {
    animManager.disable();
    timeManager.forceOff();
  } else if (startChar == '0') {
    animManager.shiftAnim(1);
  } else if (startChar == '9') {
    animManager.shiftAnim(-1);
  } else if (startChar == '=') {
    cubeOS.adjBri(1);
  } else if (startChar == '-') {
    cubeOS.adjBri(-1);
  } else if (startChar == '[') {
    StreamAnim::shiftCubeID(-1);
  } else if (startChar == ']') {
    StreamAnim::shiftCubeID(1);
  } else if (startChar == '1') {
    Serial.println(cube->setDitherBits(max(cube->getDitherBits() - 1, 0)));
  } else if (startChar == '2') {
    Serial.println(cube->setDitherBits(cube->getDitherBits() + 1));
  }
#endif
  else if (startChar >= 0) {
    // count and discard unknown characters
    unknownCount++;
    sinceUnknownChar = 0;
  }
}

SerialStreamManager serialStreamManager;