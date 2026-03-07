#include "MainHangarTask.h"
#include <Arduino.h>
#include "config.h"
#include "kernel/Logger.h"

#define T1 3000
#define BWD_ME 1000
#define START_TIME 100
#define RESET_TIME 500

MainHangarTask::MainHangarTask(PresenceSensor *pPresenceSensor, ProximitySensor *pProximitySensor,
                               DisplayLcd *pDisplay, Led *pStaticLed, HangarDoor *pHangarDoor, Context *pContext)
{
    this->pPresenceSensor = pPresenceSensor;
    this->pProximitySensor = pProximitySensor;
    this->pDisplay = pDisplay;
    this->pStaticLed = pStaticLed;
    this->pHangarDoor = pHangarDoor;
    this->pContext = pContext;
    setState(IDLE_INSIDE);
}

void MainHangarTask::tick()
{
    switch (state)
    {
    case IDLE_INSIDE:
    {
        if (this->checkAndSetJustEntered())
        {
            Logger.log(F("[MHT] IDLE_INSIDE"));
            if (pHangarDoor->isOpen())
            {
                pHangarDoor->close();
                Logger.log(F("[MHT] DOOR CLOSED"));
            }
            pStaticLed->switchOn();
            Logger.log(F("[LED] ON"));
            pDisplay->showMessage("DRONE INSIDE");
            Logger.log(F("[LCD] DRONE INSIDE"));
        }

        break;
    }
    case TAKING_OFF:
    {
        if (this->checkAndSetJustEntered())
        {
            Logger.log(F("[MHT] TAKING_OFF"));
            if (!pHangarDoor->isOpen())
            {
                pHangarDoor->open();
                Logger.log(F("[MHT] DOOR OPENED"));
            }
            pDisplay->showMessage("TAKING OFF");
            Logger.log(F("[LCD] TAKING OFF"));
        }

        break;
    }
        /* case SWEEPING_BWD:
        {
            if (this->checkAndSetJustEntered())
            {
                Logger.log(F("[SWT] SWEEPING_BWD"));
            }

            long dt = elapsedTimeInState();
            currentPos = (((float)dt) / BWD_TIME) * 180;
            pMotor->setPosition(currentPos);

            if (pButton->isPressed())
            {
                Logger.log(F("[SWT] STOPPED!"));
                pContext->setStopped();
                toBeStopped = true;
            }

            if (dt > BWD_TIME)
            {
                if (!toBeStopped)
                {
                    setState(SWEEPING_FWD);
                }
                else
                {
                    setState(RESETTING);
                }
            }
            break;
        }
        case STARTING:
        {
            if (this->checkAndSetJustEntered())
            {
                Logger.log(F("[SWT] STARTING"));
            }
            if (elapsedTimeInState() > START_TIME)
            {
                pContext->setStarted();
                pMotor->on();
                currentPos = 0;
                toBeStopped = false;
                setState(SWEEPING_FWD);
            }
            break;
        }
        case RESETTING:
        {
            if (this->checkAndSetJustEntered())
            {
                Logger.log(F("[SWT] RESETTING"));
            }
            pMotor->setPosition(0);
            if (elapsedTimeInState() > RESET_TIME)
            {
                pMotor->off();
                setState(IDLE);
            }
        } */
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
