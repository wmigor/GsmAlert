#pragma once

#include <IPin.h>


class Pin : public IPin
{
public:
	Pin(uint8_t pin);

	inline int digitalRead() { return ::digitalRead(pin); }
	inline int analogRead() { return ::analogRead(pin); }
	inline void digitalWrite(uint8_t value) { ::digitalWrite(pin, value); }
	inline void analogWrite(int value) { ::analogWrite(pin, value); }
	inline void setupInput() { pinMode(pin, INPUT); }
	inline void setupInputPullUp() { pinMode(pin, INPUT_PULLUP); }
	inline void setupOutput() { pinMode(pin, OUTPUT);}
private:
	uint8_t pin;
};
