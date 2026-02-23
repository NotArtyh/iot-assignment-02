#include "Arduino.h"
#include "HangarDevice/Actuator/Led/Led.h"
#include "Timer.h"
#include "HangarDevice/Actuator/Button/ButtonImpl.h"
#include "kernel/Scheduler.h"

#define LED_PIN 13
#define BUTTON_PIN 2

Light *led;
Button *button;
Timer timer;

enum
{
  // IMPLEMENTARE
} state;

// QUI SI INIZIALIZZANO SOLO I VARI OGGETTI E LO STATO INIZIALE

Scheduler sched;

void setup()
{

  Serial.begin(9600);
  sched.init(50);

  Task *t0 = new; // task
  Task *t1 = new; // task

  sched.addTask(t0);
  sched.addTask(t1);
}

void loop()
{
  sched.schedule();
}
