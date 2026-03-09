#include "MainHangarTask.h"
#include <Arduino.h>
#include "kernel/Logger.h"

#define T1 3000
#define T2 4000
#define TAKE_OFF_DISTANCE 100
#define LANDING_DISTANCE 200

MainHangarTask::MainHangarTask(PresenceSensor *pPresenceSensor, ProximitySensor *pProximitySensor,
                               DisplayLcd *pDisplay, Led *pStaticLed, HangarDoor *pHangarDoor, Context *pContext)
{
    this->pPresenceSensor = pPresenceSensor;
    this->pProximitySensor = pProximitySensor;
    this->pDisplay = pDisplay;
    this->pStaticLed = pStaticLed;
    this->pHangarDoor = pHangarDoor;
    this->pContext = pContext;

    this->conditionStartTime = 0;
    setState(IDLE_INSIDE); // initial state
}

void MainHangarTask::tick()
{
    switch (state)
    {
    case IDLE_INSIDE:
        pContext->setIdleInside();
        {
            if (this->checkAndSetJustEntered())
            {
                Logger.log(F("[MHT] IDLE_INSIDE"));
                closeDoorIfOpen();
                pStaticLed->switchOn();
                Logger.log(F("[LED] ON"));
                pDisplay->showMessage("DRONE INSIDE");
            }
            // Transition condition: take-off command received and no prealarm
            if (pContext->isTakeOffCommanded() && (!pContext->isPreAlarming()))
            {
                setState(TAKING_OFF);
            }

            break;
        }
    case TAKING_OFF:
        pContext->setTakingOff();
        {
            if (this->checkAndSetJustEntered())
            {
                Logger.log(F("[MHT] TAKING_OFF"));
                openDoorIfClosed();
                pDisplay->showMessage("TAKING OFF");
                // AZZERA il timer SOLO quando entri in questo stato per la prima volta
                conditionStartTime = 0;
            }

            // Transition condition: drone has taken off
            float currentDistance = pProximitySensor->getDistance();
            pContext->setCurrentDistance(currentDistance);
            if (currentDistance > TAKE_OFF_DISTANCE)
            {
                // Se supera la soglia per la prima volta, fai partire il cronometro
                if (conditionStartTime == 0)
                {
                    conditionStartTime = millis();
                }
                // Se è sopra la soglia e il tempo T1 è trascorso
                else if (millis() - conditionStartTime >= T1)
                {
                    Logger.log(F("[MHT] Drone departed. Moving to OUTSIDE."));
                    setState(OUTSIDE);
                }
            }
            else
            {
                // Se la distanza scende sotto TAKE_OFF_DISTANCE prima dello scadere di T1, azzera tutto
                conditionStartTime = 0;
            }
            break;
        }
    case OUTSIDE:
        pContext->setOutside();
        {
            if (this->checkAndSetJustEntered())
            {
                Logger.log(F("[MHT] OUTSIDE"));
                closeDoorIfOpen();
                pDisplay->showMessage("DRONE OUTSIDE");
            }
            // Transition condition: drone is landingand no alarm

            if (pContext->isLandCommanded() && !pContext->isPreAlarming() && pPresenceSensor->isDetected())
            {
                setState(LANDING);
            }
            break;
        }
    case LANDING:
        pContext->setLanding();
        {
            if (this->checkAndSetJustEntered())
            {
                Logger.log(F("[MHT] LANDING"));
                openDoorIfClosed();
                pDisplay->showMessage("LANDING");
                conditionStartTime = 0;
            }

            // Transition condition: drone has landed
            float currentDistance = pProximitySensor->getDistance();
            pContext->setCurrentDistance(currentDistance);
            if (currentDistance < LANDING_DISTANCE)
            {
                // Se supera la soglia per la prima volta, fai partire il cronometro
                if (conditionStartTime == 0)
                {
                    conditionStartTime = millis();
                }
                else if (millis() - conditionStartTime >= T2)
                {
                    Logger.log(F("[MHT] Drone landed. Moving to IDLE_INSIDE."));
                    setState(IDLE_INSIDE);
                }
            }
            else
            {
                // Se la distanza scende sotto LANDING_DISTANCE prima dello scadere di T2, azzera tutto
                conditionStartTime = 0;
            }
            break;
        }
    }
}

void MainHangarTask::setState(HangarState newState)
{
    state = newState;
    stateTimestamp = millis();
    justEntered = true;
}

long MainHangarTask::elapsedTimeInState()
{
    return millis() - stateTimestamp;
}

bool MainHangarTask::checkAndSetJustEntered()
{
    bool bak = justEntered;
    if (justEntered)
    {
        justEntered = false;
    }
    return bak;
}

// Utility functions to manage the door
void MainHangarTask::closeDoorIfOpen()
{
    if (pHangarDoor->isOpen())
    {
        pHangarDoor->close();
        Logger.log(F("[MHT] DOOR CLOSED"));
    }
}

void MainHangarTask::openDoorIfClosed()
{
    if (!pHangarDoor->isOpen())
    {
        pHangarDoor->open();
        Logger.log(F("[MHT] DOOR OPENED"));
    }
}