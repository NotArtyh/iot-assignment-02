#ifndef __MAIN_HANGAR_TASK__
#define __MAIN_HANGAR_TASK__

#include "kernel/Task.h"
#include "devices/PresenceSensor.h"
#include "devices/ProximitySensor.h"
#include "devices/DisplayLcd.h"
#include "devices/Led.h"
#include "devices/HangarDoor.h"
#include "model/Context.h"
#include <Arduino.h>

class MainHangarTask : public Task
{

public:
  MainHangarTask(PresenceSensor *pPresenceSensor, ProximitySensor *pProximitySensor, DisplayLcd *pDisplay, Led *staticLed, HangarDoor *pHangarDoor, Context *pContext);
  void tick();

private:
  void setState(int state);
  long elapsedTimeInState();
  void log(const String &msg);

  bool checkAndSetJustEntered();

  enum
  {
    IDLE_INSIDE,
    TAKING_OFF,
    OUTSIDE,
    LANDING
  } state;
  long stateTimestamp;
  bool justEntered;

  PresenceSensor *pPresenceSensor;
  ProximitySensor *pProximitySensor;
  DisplayLcd *pDisplay;
  Led *pStaticLed;
  HangarDoor *pHangarDoor;
  Context *pContext;

  int currentPos;
  bool toBeStopped;
};

#endif