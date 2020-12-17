#pragma once

class ITime
{
public:
	virtual unsigned long millis() const = 0;
	virtual void delay(unsigned long time);
};