#include <Arduino.h>
#include "config.h"

#include "kernel/Scheduler.h"
#include "kernel/Logger.h"
#include "kernel/MsgService.h"

#include "model/HangarPlatform.h"

#include "tasks/MainHangarTask.h"
#include "tasks/BlinkingLedTask.h"
#include "tasks/AlarmTask.h"
#include "tasks/SerialTask.h"

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
  Task *pBlinkingLedTask = new BlinkingLedTask(pHangarPlatform->getActionLed(), pContext);
  pBlinkingLedTask->init(100);
  Task *pAlarmTask = new AlarmTask(pHangarPlatform->getTempSensor(), pHangarPlatform->getButton(), pHangarPlatform->getAlarmLed(), pHangarPlatform->getLcd(), pHangarPlatform->getHangarDoor(), pContext);
  pAlarmTask->init(100);
  Task *pSerialTask = new SerialTask(pContext);
  pSerialTask->init(100);

  sched.addTask(pMainHangarTask);
  sched.addTask(pBlinkingLedTask);
  sched.addTask(pAlarmTask);
  sched.addTask(pSerialTask);
#endif
}

void loop()
{
  sched.schedule();
}