#pragma once

#include <Arduino.h>


class IPin
{
public:
    virtual int digitalRead() = 0;
    virtual int analogRead() = 0;
    virtual void digitalWrite(uint8_t value) = 0;
    virtual void analogWrite(int value) = 0;
    virtual void setupInput() = 0;
    virtual void setupInputPullUp() = 0;
    virtual void setupOutput() = 0;
};
