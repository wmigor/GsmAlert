#include <GsmModule.h>
#include <SmsParser.h>

GsmModule::GsmModule(Stream &stream, ITime *time, unsigned long timeout) : gsm(stream)
{
	this->time = time;
	this->timeout = timeout;
}

void GsmModule::begin()
{
	if (!gsm.begin())
		Serial.println("Error init gsm");
	gsm.sendAT(GF("+CMGF=1"));
	if (!gsm.waitResponse())
		Serial.println("Error +CMGF=1");
	gsm.sendAT(GF("+CSDH=1"));
	if (!gsm.waitResponse())
		Serial.println("Error +CSDH=1");
}

bool GsmModule::sendSms(const String &phone, const String &message)
{
	return gsm.sendSMS(phone, message);
}

std::vector<Sms> GsmModule::readSms()
{
	std::vector<Sms> result;
	SmsParser parser;

	gsm.sendAT("+CMGL=\"REC UNREAD\"");

	while (true)
	{
		if (!gsm.waitResponse(5000L, GF("+CMGL:")))
			break;

		auto data = gsm.stream.readStringUntil('\n');
		auto message = gsm.stream.readStringUntil('\n');
		Serial.println(data);
		Serial.println(message);
		data.trim();
		message.trim();
		message.replace("\r", "");
		Sms sms;
		if (parser.parse(data, message, sms))
			result.push_back(Sms(sms));
	}

	return result;
}

bool GsmModule::deleteSms(uint8_t id)
{
	gsm.sendAT(GF("+CMGD="), id, GF(","), 0);
	return gsm.waitResponse(5000L) == 1;
}
