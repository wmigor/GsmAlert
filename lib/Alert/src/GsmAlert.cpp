#include <GsmAlert.h>

GsmAlert::GsmAlert(IMotionDetector *motionDetector, IGsmModule *gsmModule, const String &phone)
{
    this->motionDetector = motionDetector;
    this->gsmModule = gsmModule;
	this->phone = phone;
}

void GsmAlert::begin()
{
    motionDetector->begin();
	gsmModule->begin();

	hasMotion = motionDetector->hasMotion();
}

void GsmAlert::update()
{
	detectMotion();
}

void GsmAlert::detectMotion()
{
	auto value = motionDetector->hasMotion();
	auto changed = value != hasMotion;
	hasMotion = value;
	
	if (!changed)
		return;
	
	Serial.println(hasMotion ? "Alarm! Moving detected!!!!" : "No moving");

	if (hasMotion)
	{
		gsmModule->sendSms(phone, "Ograblenie!");
		delay(10000);
	}
}
