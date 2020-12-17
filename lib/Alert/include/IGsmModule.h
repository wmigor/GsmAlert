#pragma once

#include <Arduino.h>
#include <Sms.h>
#include <vector>

class IGsmModule
{
public:
	virtual void begin() = 0;
	virtual bool sendSms(const String &phone, const String &message) = 0;
	virtual bool deleteSms(uint8_t id) = 0;
	virtual std::vector<Sms> readSms() = 0;
	virtual String sendUssd(const String &ussd) = 0;
	virtual void update() = 0;
};
