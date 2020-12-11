#pragma once


class IMotionDetector
{
public:
	virtual void begin() = 0;
	virtual bool hasMotion() = 0;
};
