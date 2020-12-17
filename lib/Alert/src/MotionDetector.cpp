#include <MotionDetector.h>

MotionDetector::MotionDetector(const std::vector<IPin *> &pins)
{
	this->pins = pins;
}

void MotionDetector::begin()
{
	for (auto pin : pins)
		pin->setupInput();
}

bool MotionDetector::hasMotion()
{
	for (auto pin : pins)
	{
		if (pin->digitalRead() == LOW)
			return false;
	}

	return true;
}