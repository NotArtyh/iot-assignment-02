#include "Context.h"

Context::Context()
{
  takingOff = false;
  landing = false;
  alarm = false;
}

// --- SETTERS ---

void Context::setIdleInside()
{
  takingOff = false;
  landing = false;
}

void Context::setTakingOff()
{
  takingOff = true;
  landing = false;
}

void Context::setOutside()
{
  takingOff = false;
  landing = false;
}

void Context::setLanding()
{
  takingOff = false;
  landing = true;
}

void Context::setAlarm()
{
  alarm = true;
}

void Context::clearAlarm()
{
  alarm = false;
}

// --- GETTERS ---

bool Context::isTakingOff()
{
  return takingOff;
}

bool Context::isLanding()
{
  return landing;
}

bool Context::isAlarming()
{
  return alarm;
}