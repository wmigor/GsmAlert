#pragma once

class ITime
{
public:
	virtual unsigned long millis() = 0;
	virtual void delay(unsigned long time);
};