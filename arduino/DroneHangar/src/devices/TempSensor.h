#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H

#include <Arduino.h>

class TempSensor
{
private:
    int pin;

public:
    TempSensor(int pin);
    float getTemperature();
};

#endif