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

  //  AlarmTask setters
  void setPreAlarm();
  void clearPreAlarm();
  void setAlarm();
  void clearAlarm();

  bool isPreAlarming();
  bool isAlarming();
  bool isTakingOff();
  bool isLanding();
  bool isOutside();

private:
  bool preAlarm;
  bool alarm;
  bool takingOff;
  bool landing;
  bool outside;
};

#endif