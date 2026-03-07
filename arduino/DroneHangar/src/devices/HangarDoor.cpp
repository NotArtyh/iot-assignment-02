#include "HangarDoor.h"

HangarDoor::HangarDoor(int pin)
{
    _pin = pin;
    _isOpen = false;
    // Il motore non viene "attaccato" subito per risparmiare corrente
}

void HangarDoor::setAngle(int angle)
{
    if (angle > 180)
    {
        angle = 180;
    }
    else if (angle < 0)
    {
        angle = 0;
    }

    // updated values: min is 544, max 2400 (see ServoTimer2 doc)
    float coeff = (2400.0 - 544.0) / 180.0;
    motor.write(544 + angle * coeff);
}

void HangarDoor::open()
{
    if (!_isOpen)
    {
        motor.attach(_pin); // Accendi il motore
        setAngle(90);       // 90 gradi per aprire
        _isOpen = true;
    }
}

void HangarDoor::close()
{
    if (_isOpen)
    {
        setAngle(0); // 0 gradi per chiudere

        // Nota: se il motore si "stacca" prima di arrivare a 0 gradi,
        // potresti dover aggiungere un piccolo delay(500) prima di motor.detach();
        motor.detach(); // Spegni il motore per risparmiare corrente
        _isOpen = false;
    }
}

bool HangarDoor::isOpen()
{
    return _isOpen;
}