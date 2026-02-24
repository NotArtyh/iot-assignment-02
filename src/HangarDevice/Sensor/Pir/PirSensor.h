#ifndef __PIR_SENSOR__
#define __PIR_SENSOR__

class PirSensor
{

public:
    virtual bool isDetected() = 0;
};

#endif