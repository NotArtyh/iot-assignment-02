#ifndef __CONTEXT__
#define __CONTEXT__

class Context
{

public:
  Context();

  // MainHangarTask setters
  void setIdleInside();
  void setTakingOff();
  void setOutside();
  void setLanding();

  // TemperatureAlarmTask setters
  void setAlarm();
  void clearAlarm(); // Per il pulsante RESET

  bool isTakingOff();
  bool isLanding();
  bool isAlarming();

private:
  bool takingOff;
  bool landing;
  bool alarm;
};

#endif