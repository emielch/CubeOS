#include "TimeManager.h"

#include "../Anim/AnimManager.h"
#include "TimeUtils.h"

elapsedMillis sinceAlarmCheck = 0;

void TimeManager::update() {
  if (sinceAlarmCheck < 1000) return;
  sinceAlarmCheck = 0;

  int weekday = getWeekDay(now());
  if (!dayOn[weekday]) {  // if it's set to be off today
    animManager.disable();
    return;
  }

  unsigned long currT = now() % (60 * 60 * 24);
  if (onTime < offTime)
    setOnOff(currT > onTime && currT < offTime);
  else
    setOnOff(!(currT > offTime && currT < onTime));
}

void TimeManager::setOnOff(bool val) {
  if (val && animManager.getEnabled()) {
    forcingOn = false;
  } else if (val && !animManager.getEnabled() && !forcingOff) {
    animManager.enable();
  } else if (!val && !animManager.getEnabled()) {
    forcingOff = false;
  } else if (!val && animManager.getEnabled() && !forcingOn) {
    animManager.disable();
  }
}

unsigned long TimeManager::now() {
  return Teensy3Clock.get();
}
void TimeManager::setTime(unsigned long t) {
  Teensy3Clock.set(t);
}
void TimeManager::setOnTime(byte h, byte m, byte s) {
  onTime = convertTime(h, m, s);
}
void TimeManager::setOffTime(byte h, byte m, byte s) {
  offTime = convertTime(h, m, s);
};

void TimeManager::setOnDay(int day, bool on) {
  if (day < 0 || day > 6) return;
  dayOn[day] = on;
}

void TimeManager::printCurrTime() {
  Serial.print("Curr: \t");
  printTime(now());
  Serial.print("Weekday: \t");
  Serial.println(getWeekDay(now()));
  Serial.print("ON: \t");
  printTime(onTime);
  Serial.print("OFF: \t");
  printTime(offTime);
  Serial.println();
}

TimeManager timeManager;