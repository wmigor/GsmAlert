#pragma once

#include <IGsmModule.h>
#include <IMotionDetector.h>


class GsmAlert
{
public:
    GsmAlert(IMotionDetector *motionDetector, IGsmModule *gsmModule, const String &phone);
    void begin();
    void update();
private:
    IMotionDetector *motionDetector;
    IGsmModule *gsmModule;
	String phone;
	bool hasMotion;

	void detectMotion();
};
