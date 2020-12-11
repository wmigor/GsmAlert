#pragma once

#include <Pin.h>

class PinFake : public IPin
{
public:
    inline PinFake() : digitalValue(0), analogValue(0), input(false), output(false) { }
    inline int digitalRead() { return digitalValue; }
    inline int analogRead() { return analogValue; }
    inline void digitalWrite(uint8_t value) { digitalValue = value; }
    inline void analogWrite(int value) { analogValue = value; }
    inline void setupInput() { input = true; }
    inline void setupInputPullUp() { }
    inline void setupOutput() { output = true; }
public:
    int digitalValue;
    int analogValue;
    bool input;
    bool output;
};
