#include <GsmAlert.h>

GsmAlert::GsmAlert(IMotionDetector &motionDetector, IGsmModule &gsmModule, ITime &time, const String &phone)
{
    this->motionDetector = &motionDetector;
    this->gsmModule = &gsmModule;
	this->time = &time;
	this->phone = phone;
	enabled = false;
	hasMotion = false;
	readSmsPeriod = 20000;
}

void GsmAlert::begin()
{
    motionDetector->begin();
	gsmModule->begin();
	lastSmsUpdate = time->millis();

	hasMotion = motionDetector->hasMotion();
}

void GsmAlert::update()
{
	detectMotion();
	gsmModule->update();

	if (time->millis() - lastSmsUpdate >= readSmsPeriod)
	{
		lastSmsUpdate = time->millis();

		auto messages = gsmModule->readSms();
		for (auto sms : messages)
		{
			if (sms.phone == phone)
				handleSms(sms);
			else
				Serial.println("Unknown phone! Skip it!");

			gsmModule->deleteSms(sms.id);
		}
	}
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
	time->delay(10000);
}

void GsmAlert::handleSms(const Sms &sms)
{
	if (sms.message.equalsIgnoreCase("info"))
	{
		String ansver = "Status: ";
		ansver += isEnabled() ? "ON" : "OFF";
		ansver += "\nCommands: info, on, off";
		gsmModule->sendSms(sms.phone, ansver);
	}
	else if (sms.message.equalsIgnoreCase("on"))
		setEnabled(true);
	else if (sms.message.equalsIgnoreCase("off"))
		setEnabled(false);
}