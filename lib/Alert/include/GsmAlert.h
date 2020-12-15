#pragma once

#include <IGsmModule.h>
#include <IMotionDetector.h>


class GsmAlert
{
public:
    GsmAlert(IMotionDetector *motionDetector, IGsmModule *gsmModule, const String &phone);
    void begin();
    void update();
	inline bool isEnabled() const { return enabled; }
	void setEnabled(bool value);
private:
    IMotionDetector *motionDetector;
    IGsmModule *gsmModule;
	String phone;
	bool hasMotion;
	bool enabled;

	void detectMotion();
	void handleMotion();
};
