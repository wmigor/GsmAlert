#pragma once

#include <Arduino.h>
#include <Sms.h>

class SmsParser
{
public:
	bool parse(const String &data, const String &message, Sms &sms);
};
