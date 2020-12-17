#pragma once

#include <IGsmModule.h>
#include <IMotionDetector.h>
#include <ITime.h>


class GsmAlert
{
public:
    GsmAlert(IMotionDetector &motionDetector, IGsmModule &gsmModule, ITime &time, const String &phone);
    void begin();
    void update();
	inline bool isEnabled() const { return enabled; }
	void setEnabled(bool value);
	inline void setReadSmsPeriod(unsigned long value) { readSmsPeriod = value; }
private:
    IMotionDetector *motionDetector;
    IGsmModule *gsmModule;
	ITime *time;
	String phone;
	bool hasMotion;
	bool enabled;
	unsigned long lastSmsUpdate;
	unsigned long readSmsPeriod;

	void detectMotion();
	void handleMotion();
	void handleSms(const Sms &sms);
};
