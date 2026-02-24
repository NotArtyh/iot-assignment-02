#ifndef __TEMP_SENSOR_IMPL__
#define __TEMP_SENSOR_IMPL__

class TempSensorImpl : public TempSensor
{

public:
    TempSensorImpl(int pin);
    virtual float getTemperature();

private:
    int pin;
};

#endif