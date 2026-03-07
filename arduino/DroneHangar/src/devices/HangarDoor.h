#ifndef __HANGAR_DOOR__
#define __HANGAR_DOOR__

#include "ServoMotor.h"

class HangarDoor
{
public:
    HangarDoor(int pin);

    void open();
    void close();
    bool isOpen();

private:
    bool _isOpen;
    ServoMotor *servo;
};

#endif