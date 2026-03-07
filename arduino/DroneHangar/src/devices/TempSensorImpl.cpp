#include "Arduino.h"
#include "TempSensor.h"

TempSensor::TempSensor(int pin) : pin(pin)
{
    pinMode(pin, INPUT);
}

float TempSensor::getTemperature()
{
    // 1. Legge il valore grezzo (0 - 1023)
    int rawValue = analogRead(pin);

    // 2. Converte in Tensione (assumendo 5V di alimentazione)
    float voltage = rawValue * (5.0 / 1023.0);

    // 3. Converte in Temperatura (°C) - formula per LM35
    float temperatureC = voltage * 100.0;

    return temperatureC;
}