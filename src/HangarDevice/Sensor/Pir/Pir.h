#ifndef __PIR__
#define __PIR__

#include "PirSensor.h"

class Pir : public PirSensor
{

public:
    Pir(int pin);
    bool isDetected();
    void calibrate();

    void sync();
    long getLastSyncTime();

protected:
    void updateSyncTime(long time);

private:
    long lastTimeSync;
    int pin;
    bool detected;
};

#endif