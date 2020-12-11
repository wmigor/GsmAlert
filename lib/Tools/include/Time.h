#pragma once

#include <ITime.h>
#include <Arduino.h>

class Time : public ITime
{
public:
	inline unsigned long millis() { return ::millis(); }
	inline void delay(unsigned long time) { ::delay(time); }
};
