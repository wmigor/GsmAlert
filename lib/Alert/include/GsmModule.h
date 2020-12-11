#pragma once

#include <IGsmModule.h>
#include <ITime.h>

class GsmModule : public IGsmModule
{
public:
    GsmModule(Stream *stream, ITime *time, unsigned long timeout = 10000);
	void begin();
	void sendSms(const String &phone, const String &message);
private:
	Stream *stream;
	ITime *time;
	unsigned long timeout;

	String waitResponse();
	String sendATCommand(const String &cmd, bool waiting);
};