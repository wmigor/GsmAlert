#pragma once

#include <Arduino.h>

class IGsmModule
{
public:
	virtual void begin() = 0;
	virtual void sendSms(const String &phone, const String &message) = 0;
private:

};
