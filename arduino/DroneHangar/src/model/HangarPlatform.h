#ifndef __HANGAR_PLATFORM__
#define __HANGAR_PLATFORM__

#include "config.h"
#include "devices/Button.h"
#include "devices/Led.h"
#include "devices/ServoMotor.h"
#include "devices/Sonar.h"
#include "devices/Pir.h"
#include "devices/DisplayLcd.h"
#include "devices/TempSensor.h"

class HangarPlatform
{

public:
  HangarPlatform();
  void init();

  Button *getButton();
  Led *getStaticLed();
  Led *getActionLed();
  Led *getAlarmLed();
  ServoMotor *getMotor();
  Sonar *getSonar();
  Pir *getPir();
  DisplayLcd *getLcd();
  ServoMotor *getMotor();
  TempSensor *getTempSensor();

private:
  Button *pButton;
  Led *pStaticLed;
  Led *pActionLed;
  Led *pAlarmLed;
  ServoMotor *pMotor;
  Sonar *pSonar;
  Pir *pPir;
  DisplayLcd *pLcd;
  ServoMotor *pMotor;
  TempSensor *pTempSensor;
};

#endif