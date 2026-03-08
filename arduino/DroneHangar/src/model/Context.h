#ifndef __CONTEXT__
#define __CONTEXT__

class Context
{

public:
  Context();

  void setIdleInside();
  void setTakingOff();
  void setOutside();
  void setLanding();
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