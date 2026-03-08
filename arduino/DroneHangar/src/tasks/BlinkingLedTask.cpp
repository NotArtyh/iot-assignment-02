#include "BlinkingLedTask.h"
#include <Arduino.h>
#include "config.h"
#include "kernel/Logger.h"

#define BLINK_HALF_PERIOD 250

BlinkingTask::BlinkingTask(Led *pActionLed, Context *pContext) : pContext(pContext), pActionLed(pActionLed)
{
    this->stateTimestamp = 0;
    setState(IDLE);
}

void BlinkingTask::tick()
{
    // Lampeggia se stiamo decollando o atterrando
    bool shouldBlink = pContext->isTakingOff() || pContext->isLanding();

    switch (state)
    {
    case IDLE:
    {
        if (this->checkAndSetJustEntered())
        {
            pActionLed->switchOff();
            // Logger.log(F("[BT] IDLE"));
        }
        if (shouldBlink)
        {
            setState(BLINK_ON);
        }
        break;
    }
    case BLINK_OFF:
    {
        if (this->checkAndSetJustEntered())
        {
            pActionLed->switchOff();
        }

        if (!shouldBlink)
        {
            setState(IDLE);
        }
        else if (elapsedTimeInState() >= BLINK_HALF_PERIOD)
        {
            setState(BLINK_ON);
        }
        break;
    }
    case BLINK_ON:
    {
        if (this->checkAndSetJustEntered())
        {
            pActionLed->switchOn();
        }
        if (!shouldBlink)
        {
            setState(IDLE);
        }
        else if (elapsedTimeInState() >= BLINK_HALF_PERIOD)
        {
            setState(BLINK_OFF);
        }
        break;
    }
    }
}

void BlinkingTask::setState(BlinkState s)
{
    state = s;
    stateTimestamp = millis();
    justEntered = true;
}

long BlinkingTask::elapsedTimeInState()
{
    return millis() - stateTimestamp;
}

bool BlinkingTask::checkAndSetJustEntered()
{
    bool bak = justEntered;
    if (justEntered)
    {
        justEntered = false;
    }
    return bak;
}