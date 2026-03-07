#include <Arduino.h>
#include "config.h"

#include "kernel/Scheduler.h"
#include "kernel/Logger.h"
#include "kernel/MsgService.h"

#include "model/HangarPlatform.h"

#include "tasks/MainHangarTask.h"
#include "tasks/BlinkingLedTask.h"
#include "tasks/TemperatureAlarmTask.h"

// #define __TESTING_HW__

Scheduler sched;

HangarPlatform *pHangarPlatform;
Context *pContext;

void setup()
{
  MsgService.init();
  sched.init(50);

  Logger.log("Starting Drone Hangar...");

  pHangarPlatform = new HangarPlatform();
  pHangarPlatform->init();

#ifndef __TESTING_HW__
  pContext = new Context();

  Task *pMainHangarTask = new MainHangarTask(pHangarPlatform->getPir(), pHangarPlatform->getSonar(), pHangarPlatform->getLcd(), pHangarPlatform->getStaticLed(), pHangarPlatform->getHangarDoor(), pContext);
  pMainHangarTask->init(50);
  /* Task *pBlinkingLedTask = new BlinkingLedTask(pHangarPlatform->getActionLed(), pContext);
  pBlinkingTask->init(100); */

  sched.addTask(pMainHangarTask);
  // sched.addTask(pBlinkingTask);
#endif
}

void loop()
{
  sched.schedule();
}