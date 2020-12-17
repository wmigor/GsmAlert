#pragma once

#include <ITime.h>

class TimeFake : public ITime
{
public:
	inline TimeFake() : milliseconds(0) { }
	inline void delay(unsigned long time) { milliseconds += time; }
	inline unsigned long millis() const { return milliseconds; }
private:
	unsigned long milliseconds;
};
