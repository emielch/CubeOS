#include "TimeManager.h"

#include "../Demo/DemoManager.h"
#include "TimeUtils.h"

elapsedMillis sinceAlarmCheck = 0;

void TimeManager::update() {
  if (sinceAlarmCheck < 1000) return;
  sinceAlarmCheck = 0;

  int weekday = getWeekDay(now());
  if (!dayOn[weekday]) {  // if it's set to be off today
    demoManager.disableDemo();
    return;
  }

  unsigned long currT = now() % (60 * 60 * 24);
  if (onTime < offTime) {
    if (currT > onTime && currT < offTime)
      demoManager.enableDemo();
    else
      demoManager.disableDemo();
  } else {
    if (currT > offTime && currT < onTime)
      demoManager.disableDemo();
    else
      demoManager.enableDemo();
  }
}

unsigned long TimeManager::now() {
  return Teensy3Clock.get();
}
void TimeManager::setTime(unsigned long t) {
  Teensy3Clock.set(t);
}

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