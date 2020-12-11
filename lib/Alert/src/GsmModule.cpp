#include <GsmModule.h>

GsmModule::GsmModule(Stream *stream, ITime *time, unsigned long timeout)
{
	this->stream = stream;
	this->time = time;
	this->timeout = timeout;
}

void GsmModule::begin()
{
	sendATCommand("AT+CMGF=1;&W", true);
	sendATCommand("AT+CSCS=\"GSM\"", true);
}

void GsmModule::sendSms(const String &phone, const String &message)
{
	sendATCommand("AT+CMGS=\"" + phone + "\"", true);
	sendATCommand(message + "\r\n" + (String) ((char)26), true);
}

String GsmModule::waitResponse()
{
	String response = "";
	auto expireTime = time->millis() + timeout;

	while (!stream->available() && time->millis() < expireTime)
		time->delay(1);
	
	if (stream->available())
		response = stream->readString();
	else
		Serial.println("Timeout...");

	return response;
}

String GsmModule::sendATCommand(const String &cmd, bool waiting)
{
	Serial.println(cmd);
	stream->println(cmd);

	if (waiting)
	{
		auto response = waitResponse();

		if (response.startsWith(cmd))
			response = response.substring(response.indexOf("\r", cmd.length()) + 2);

		Serial.println(response);
		return response;
	}

	return "";
}
