#include "HangarDoor.h"
#include "ServoMotorImpl.h"

HangarDoor::HangarDoor(ServoMotorImpl *servo)
{
    this->servo = servo;
    _isOpen = false;
    close();
}

void HangarDoor::open()
{
    if (!_isOpen)
    {
        servo->on();            // Accendi il motore (se la tua classe Servo lo richiede)
        servo->setPosition(90); // Es: 90 gradi per aprire
        _isOpen = true;
    }
}

void HangarDoor::close()
{
    if (_isOpen)
    {
        servo->setPosition(0);
        servo->off(); // Spegni il motore per risparmiare corrente
        _isOpen = false;
    }
}

bool HangarDoor::isOpen()
{
    return _isOpen;
}
