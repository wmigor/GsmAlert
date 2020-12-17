#pragma once

#include <IMotionDetector.h>

class MotionDetectorFake : public IMotionDetector
{
public:
	inline MotionDetectorFake() : motion(false), started(false) {}
	inline void begin() { started = true; }
	inline bool hasMotion() { return motion; }

public:
	bool motion;
	bool started;
};
