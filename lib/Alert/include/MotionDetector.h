#pragma once

#include <vector>
#include <IPin.h>
#include <IMotionDetector.h>

class MotionDetector : public IMotionDetector
{
public:
	MotionDetector(const std::vector<IPin *> &pins);
	void begin();
	bool hasMotion();
private:
	std::vector<IPin *> pins;
};
