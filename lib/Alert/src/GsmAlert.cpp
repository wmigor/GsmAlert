#include <GsmAlert.h>

GsmAlert::GsmAlert(IMotionDetector *motionDetector, IGsmModule *gsmModule, const String &phone)
{
    this->motionDetector = motionDetector;
    this->gsmModule = gsmModule;
	this->phone = phone;
	enabled = false;
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

void GsmAlert::setEnabled(bool value)
{
	enabled = value;
	handleMotion();
}

void GsmAlert::detectMotion()
{
	auto value = motionDetector->hasMotion();
	auto changed = value != hasMotion;
	hasMotion = value;
	
	if (!changed)
		return;
	
	Serial.println(hasMotion ? "Alarm! Moving detected!!!!" : "No moving");

	if (enabled && hasMotion)
		handleMotion();
}

void GsmAlert::handleMotion()
{
	if (!enabled || !hasMotion)
		return;

	gsmModule->sendSms(phone, "Ograblenie!");
	delay(10000);
}
